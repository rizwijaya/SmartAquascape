#include <DallasTemperature.h>
#include "time.h"
#include <AntaresESP32HTTP.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define PinSuhu 32      //digital
#define PinTDS 34       //analog
#define PinPH 39        //analog
#define PinTurbidity 35 //analog
#define PinLampu 33     //IN1
#define PinKipas 25     //IN2
#define I2C_SDA 22
#define I2C_SCL 26
OneWire oneWire(PinSuhu);

DallasTemperature sensorSuhu(&oneWire);
#define offsettds 0.5
#define VCC 3.3
#define ADCResolution 4096
#define SCOUNT 10          //sum of sample poin for TDS
#define pHLength 10        //sum of sample poin for pH
#define tempLength 10      // sum of sample poin for temp
#define turbidityLength 10 // sum of sample poin for turbidity
#define Offset 0.00
#define turbidityOffset -0.7

const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 7 * 3600;
const int daylightOffset_sec = 0;

int relaytime_hour;
int relaytime_min;

int analogBuffer[SCOUNT];     
int analogBufferTemp[SCOUNT]; 
int analogBufferIndex = 0, copyIndex = 0;
float avgV = 0, TDSValue = 0, tempSet = 25;
int pHArray[pHLength]; 
int pHArrayIndex = 0, tempArrayIndex = 0, turbidityArrayIndex = 0;
int tempArray[tempLength];           
int turbidityArray[turbidityLength]; 

#define samplingInterval 200
#define printInterval 8000

const char *ACCESSKEY = "38727ec4c4a0a1aa:7de4a820d4d6c54c"; // Ganti dengan access key akun Antares anda
const char *WIFISSID = "LAB IOT Dev 5GHz";                   // Ganti dengan SSID WiFi anda
const char *PASSWORD = "labiot2018";                         // Ganti dengan password WiFi anda

const char *projectName = "testingkafin1"; // Ganti dengan application name Antares yang telah dibuat
const char *sendName = "espsend";          // Ganti dengan device Antares yang telah dibuat
const char *subName = "espreceive";

const unsigned long publishdelay = 60000; 
const unsigned long subscribedelay = 15000;
const unsigned long samplingdelay = 100;
const unsigned long dataprocessdelay = 1000;
const unsigned long rtcdelay = 36E5;
const unsigned long lampudelay = 15000;
const unsigned long kipasdelay = 5000;

unsigned long publishtime = publishdelay;     //tunggu sampling sebelum kirim data pertama
unsigned long subscribetime = subscribedelay; //inisiasi dilakukan di setup
unsigned long samplingtime;
unsigned long dataprocesstime = dataprocessdelay; //tunggu sampling sebelum diprocess
unsigned long rtctime = rtcdelay; //inisiasi dilakukan di setup
unsigned long lamputime;
unsigned long kipastime;

float pHValue, voltagePH, voltageTB, turbidityValue, tdsValue, tempValue, tempNow;

AntaresESP32HTTP antares(ACCESSKEY); 
struct tm timeinfo;

//nilai awal default
float pHset = 6.5;
int temperatureset = 25;
int relayontime = 900;
int relayofftime = 1500;
int relayontime_hour = relayontime / 100;
int relayontime_min = relayontime && 100;
int relayofftime_hour = relayofftime / 100;
int relayofftime_min = relayofftime && 100;

void publishdata()
{
    // Tambahkan variabel ke penampungan data sementara
    antares.add("temperature", tempValue);
    antares.add("pH", pHValue);
    antares.add("turbidity", turbidityValue);
    antares.add("tds", tdsValue);

    // Publish data ke database Antares dan juga broker MQTT Antares
    antares.send(projectName, sendName);
}

void subscribedata()
{
    antares.get(projectName, subName);
    // Mendapatkan data individu
    pHset = antares.getFloat("pH");
    temperatureset = antares.getInt("temperature");
    relayontime = antares.getInt("ON");
    relayofftime = antares.getInt("OFF");
    relayontime_hour = relayontime / 100;
    relayontime_min = relayontime && 100;
    relayofftime_hour = relayofftime / 100;
    relayofftime_min = relayofftime && 100;
    Serial.println(pHset);
    Serial.println(temperatureset);
    Serial.println(relayontime);
    Serial.println(relayofftime);
}

void setup()
{
    Wire.begin(I2C_SDA, I2C_SCL);
    Serial.begin(115200); // Buka komunikasi serial dengan baudrate 115200
    lcd.init();
    // Print a message to the LCD.
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Powering on...");
    lcd.setCursor(0, 1);
    lcd.print("Please wait");
    lcd.setCursor(0, 2);
    antares.setDebug(true);                     // Nyalakan debug. Set menjadi "false" jika tidak ingin pesan-pesan tampil di serial monitor
    antares.wifiConnection(WIFISSID, PASSWORD); // Mencoba untuk menyambungkan ke WiFi
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    sensorSuhu.begin();           //setup sensor suhu
    pinMode(PinTurbidity, INPUT); //setup pin turbidity
    pinMode(PinTDS, INPUT);       //setup pin tds
    pinMode(PinLampu, OUTPUT);
    pinMode(PinKipas, OUTPUT);

    //inisialisasi variabel
    Serial.println("getting the bloody time, one moment");
    while (!getLocalTime(&timeinfo))
    {
        Serial.print(".");
        configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
        delay(500);
    }
    subscribedata();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("T");
    lcd.setCursor(0, 1);
    lcd.print("pH");
    lcd.setCursor(7, 0);
    lcd.print("TB");
    lcd.setCursor(7, 1);
    lcd.print("TDS");
}

void loop()
{
    if (millis() - subscribetime > subscribedelay) //get newest parameter
    {
        subscribetime = millis();
        subscribedata();
    }

    if (millis() - publishtime > publishdelay) //publish data
    {
        publishtime = millis();
        publishdata();
    }

    if (millis() - samplingtime > samplingdelay) //sampling
    {
        samplingtime = millis();
        //masukkin index pH
        pHArray[pHArrayIndex++] = analogRead(PinPH);
        if (pHArrayIndex == pHLength)
            pHArrayIndex = 0;
        //masukkin index Temp
        tempArray[tempArrayIndex++] = ambilSuhu();
        if (tempArrayIndex == tempLength)
            tempArrayIndex = 0;
        //masukkin index turbidity
        turbidityArray[turbidityArrayIndex++] = analogRead(PinTurbidity);
        if (turbidityArrayIndex == turbidityLength)
            turbidityArrayIndex = 0;
        //masukkin index  tds
        analogBuffer[analogBufferIndex++] = analogRead(PinTDS);
        if (analogBufferIndex == SCOUNT)
            analogBufferIndex = 0;
    }
    if (millis() - dataprocesstime > dataprocessdelay) //data processing
    {
        dataprocesstime = millis();
        //masukkin index pH
        voltagePH = averagearray(pHArray, pHLength) * VCC / ADCResolution;
        pHValue = 3.5 * voltagePH + Offset;
        //masukkin index Temp
        tempValue = ambilSuhu();
        //masukkin index turbidity
        voltageTB = (averagearray(turbidityArray, turbidityLength) * 1.515 * VCC / ADCResolution) + turbidityOffset;
        turbidityValue = -1120.4 * voltageTB * voltageTB + (5742.3 * voltageTB) - 4352.9;
        //setting for tds
        tdsValue = calculatetds();
        float tdsv = tdsValue / 10;
        Serial.print("temp is ");
        Serial.println(tempValue);
        Serial.print("turbidity is ");
        Serial.print(turbidityValue);
        Serial.print(" voltage is ");
        Serial.println(voltageTB);
        Serial.print("tds is ");
        Serial.println(tdsValue);
        lcddisplay();
    }
    if (millis() - lamputime > lampudelay) //cek lampu
    {
        lamputime = millis();
        if (checkshouldon())
            digitalWrite(PinLampu, LOW);
        else
            digitalWrite(PinLampu, HIGH);
    }
    if (millis() - kipastime > kipasdelay) //cek kipas
    {
        kipastime = millis();
        if (tempValue > temperatureset)
            digitalWrite(PinKipas, LOW);
        else
            digitalWrite(PinKipas, HIGH);
    }
    if (millis() - rtctime > rtcdelay) //sinkronisasi NTP
    {
        rtctime = millis();
        configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    }
}

float calculatetds() //function for calculating tds
{
    for (copyIndex = 0; copyIndex < SCOUNT; copyIndex++)
        analogBufferTemp[copyIndex] = analogBuffer[copyIndex];
    float averageVoltage = getMedianNum(analogBufferTemp, SCOUNT) * (float)VCC / ADCResolution;                                                                                          // read the analog value more stable by the median filtering algorithm, and convert to voltage value
    float compensationCoefficient = 1.0 + 0.02 * (tempValue - 25.0);                                                                                                                     //temperature compensation formula: fFinalResult(25^C) = fFinalResult(current)/(1.0+0.02*(fTP-25.0));
    float compensationVolatge = averageVoltage / compensationCoefficient;                                                                                                                //temperature compensation
    float result = (133.42 * compensationVolatge * compensationVolatge * compensationVolatge - 255.86 * compensationVolatge * compensationVolatge + 857.39 * compensationVolatge) * 0.5; //convert voltage value to tds value
    return result;
}

float ambilSuhu() //function for getting temp
{

    sensorSuhu.requestTemperatures();
    float suhu = sensorSuhu.getTempCByIndex(0);
    return suhu;
}

int getMedianNum(int bArray[], int iFilterLen) //getmedian
{
    int bTab[iFilterLen];
    for (byte i = 0; i < iFilterLen; i++)
        bTab[i] = bArray[i];
    int i, j, bTemp;
    for (j = 0; j < iFilterLen - 1; j++)
    {
        for (i = 0; i < iFilterLen - j - 1; i++)
        {
            if (bTab[i] > bTab[i + 1])
            {
                bTemp = bTab[i];
                bTab[i] = bTab[i + 1];
                bTab[i + 1] = bTemp;
            }
        }
    }
    if ((iFilterLen & 1) > 0)
        bTemp = bTab[(iFilterLen - 1) / 2];
    else
        bTemp = (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;
    return bTemp;
}

double averagearray(int *arr, int number) //averaging stuff
{
    int i;
    int max, min;
    double avg;
    long amount = 0;
    if (number <= 0)
    {
        Serial.println("Error number for the array to avraging!/n");
        return 0;
    }
    if (number < 5)
    { //less than 5, calculated directly statistics
        for (i = 0; i < number; i++)
        {
            amount += arr[i];
        }
        avg = amount / number;
        return avg;
    }
    else
    {
        if (arr[0] < arr[1])
        {
            min = arr[0];
            max = arr[1];
        }
        else
        {
            min = arr[1];
            max = arr[0];
        }
        for (i = 2; i < number; i++)
        {
            if (arr[i] < min)
            {
                amount += min; //arr<min
                min = arr[i];
            }
            else
            {
                if (arr[i] > max)
                {
                    amount += max; //arr>max
                    max = arr[i];
                }
                else
                {
                    amount += arr[i]; //min<=arr<=max
                }
            } //if
        }     //for
        avg = (double)amount / (number - 2);
    } //if
    return avg;
}

bool checkshouldon() //check based on time if it should on
{
    bool checkonhour;
    bool rollover;

    //periksa rollover
    if (relayontime_hour < relayofftime_hour)
        rollover = false; //periksa jam
    else if (relayontime_hour = relayofftime_hour && relayontime_hour < relayofftime_hour)
        rollover = false; //periksa hingga menit
    else
        rollover = true;

    if (!getLocalTime(&timeinfo))
    {
        Serial.println("Failed to obtain time");
        return false;
    }
    Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");

    int timetotal = timeinfo.tm_hour * 100 + timeinfo.tm_min;
    if (rollover)
    {
        if ((timetotal >= relayontime) || (timetotal < relayofftime))
            checkonhour = true;
        else
            checkonhour = false;
    }
    else
    {
        if ((timetotal >= relayontime) && (timetotal < relayofftime))
            checkonhour = true;
        else
            checkonhour = false;
    }

    return checkonhour;
}

void lcddisplay() //print lcd
{
    lcd.setCursor(2, 0);
    lcd.print(tempValue, 1);
    lcd.setCursor(3, 1);
    lcd.print(pHValue, 1);
    lcd.setCursor(10, 0);
    lcd.print(turbidityValue);
    lcd.setCursor(11, 1);
    lcd.print(tdsValue);
}