#include <AntaresESP8266MQTT.h>
#include<LiquidCrystal.h>
#include<Servo.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ACCESSKEY "access:key"
#define WIFISSID "androidr" //wifi ssid
#define PASSWORD "rizwijaya123" //wifi pass
#define projectName "smartAquascape" //Nama project 
#define deviceName "Aquascape-001" //Nama Device

OneWire pinSuhu(2);
DallasTemperature suhu(&pinSuhu);
AntaresESP8266MQTT antares(ACCESSKEY);
Servo servo;
int samples = 10, pinTurb = 1, UsInput = 22, UsOuput = 23, led = 16, buzzer = 11, tallAquascape = 30;
//Pin 3 - 8 LCD
LiquidCrystal lcd(8, 7, 6, 5, 4, 3);
int waktuPengiriman = 10000;
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);

  suhu.begin();//Sensor suhu
  pinMode(pinTurb, INPUT);//Sensor turbidity
  pinMode(UsInput, INPUT);//Sensor Ultrasonic
  pinMode(UsOuput, OUTPUT);//Sensor Ultrasonic
  //koneksi antares
  antares.setDebug(true);
  antares.wifiConnection(WIFISSID, PASSWORD);
  antares.setMqttServer();
  antares.setCallback(subcriber);
}

float getTemp() {
    DS18B20.requestTemperatures();
    return DS18B20.getTempCByIndex(0)
}

float getWaterLevel() {
  digitalWrite(UsOuput, LOW);
  delayMicroseconds(2);
  digitalWrite(UsOuput, HIGH);
  delayMicroseconds(10);
  digitalWrite(UsOuput, LOW);
 
  const unsigned long duration= pulseIn(UsInput, HIGH);
  int distance= duration/29/2;
  if(duration==0){
    Serial.println("Warning: no pulse from sensor");
    return 0;
  } else { 
      return distance-tallAquascape; //distance in cm
  }
}

float getTurbidity() {
  int turbidity = analogRead(A0);
  float voltage = turbidity * (5.0 / 1024.0);
  return voltage;
}
// void printSerial() {
//   Serial.print("Suhu: ");
//   Serial.print(getTemp());
//   Serial.print("\tKejernihan: ");
//   Serial.print(getTurbidity());
//   Serial.print("\tWater Level: ");
//   Serial.println(getWaterLevel());
// }

void viewData() {
  lcd.setCursor(0, 0);
  lcd.print("Suhu: "+ String(getTemp) + "C");
  lcd.setCursor(15, 0);
  lcd.print("Kejernihan: "+ String(getTurbidity));
  lcd.setCursor(0, 1);
  lcd.print("Water Level: "+ String(getWaterLevel));
}

void smartFeeder() {

}

void subcriber(char topic[], byte payload[], unsigned int length) {
  
  antares.get(topic, payload, length);  // Menyimpan topic dan payload ke penampungan data sementara

  //Serial.println("New Message!");
  //Serial.println("Topic: " + antares.getTopic());     // Print topic
  //Serial.println("Payload: " + antares.getPayload()); // Print payload
  if(antares.getInt("header") == 2) { //header 2 controlling device
    int status = antares.getInt("status");
    if(status == 1) {
      //Nyalakan servo atau feeder
    } else if(status == 2) {
      //Matikan servo atau feeder
    }
  } else if(antares.getInt("header") == 3) { //header 3 trigger by time
    //Setting Template for trigger by time
  } else if(antares.getInt("header") == 4) { //header 4 trigger time sending data
    waktuPengiriman = antares.getInt("WaktuPengiriman"); 
  } // antares.get(projectName, deviceName);
    // antares.get(projectName, subName);
    // Mendapatkan data individu=;
    // relayontime = antares.getInt("ON");
    // relayofftime = antares.getInt("OFF");
    // relayontime_hour = relayontime / 100;
    // relayontime_min = relayontime && 100;
    // relayofftime_hour = relayofftime / 100;
    // relayofftime_min = relayofftime && 100;
    // Serial.println(relayontime);
    // Serial.println(relayofftime);
}

void sendingData() {
  for(int i = 0; i < waktuPengiriman; i++) {
    antares.add("Header", 1); //Header 1 data monitoring
    antares.add("suhu", getTemp());
    antares.add("Water Level", getWaterLevel());
    antares.add("Turbidity", getTurbidity());
    antares.publish(projectName, deviceName);
  }
}

void loop() {
  antares.checkMqttConnection(); // ngecek koneksi
  viewData();
  //tentukan nilai variabel awal waktu dengan 10menit diatas. 
  //inisialisasi waktu sekarang - 10menit (inisialisasi awal 10menit diatas terus reinisialisasi lagi setelah dapat data dari antares mengenai time pengiriman)
  //get waktu sekarang, inisialisasi diawal atas

  //cek jika waktu sekarang sama dengan waktu -10 menit lalu + waktu 10menit
  //jalankan sendingDataSensor
  //Inisialisasi waktu sekarang yang digunakan sebagai waktu -10 menit yang lalu
  sendingData();
  subcriber();
}
