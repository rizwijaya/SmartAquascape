#include <AntaresESP32MQTT.h>
#include <AntaresESP32HTTP.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>

#define ACCESSKEY "9fb52249c593c66d:b719370dce7d93b9"       // Ganti dengan access key akun Antares anda
#define WIFISSID "Playmedia"         // Ganti dengan SSID WiFi anda
#define PASSWORD "12345678"     // Ganti dengan password WiFi anda

#define applicationName "smartAquascape"   // Ganti dengan application name Antares yang telah dibuat
#define deviceName "Aquascape-001"     // Ganti dengan device Antares yang telah dibuat
#define deviceControl "Aquascape-Control"
#define TimeMonitoring "TimeMonitoring"
#define Feeder "Aquascape-Feeder"
#define manFeeder "Manual-Feeder"
#define auFeeder "Auto-Feeder"

AntaresESP32MQTT antares(ACCESSKEY);    // Buat objek antares MQTT
AntaresESP32HTTP antaresAPI(ACCESSKEY);    // Buat objek antares API

String data;
struct tm timeinfo;
struct timeval tv;
char buf[64], timeLogic[64];
unsigned long TM_Sync;
int sts_FeederControl = 2; //default Manual Control
const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 7 * 3600;
const int daylightOffset_sec = 0;
String sts_time = 10;

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
  antares.setDebug(false);
  antares.wifiConnection(WIFISSID,PASSWORD);  // Mencoba untuk menyambungkan ke WiFi
  antares.setMqttServer();  // Inisiasi server MQTT Antares
  
  //inisialisasi variabel
  Serial.println("getting the bloody time, one moment");
  while (!getLocalTime(&timeinfo)) {
      Serial.print(".");
      configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
      delay(500);
  }
}

String receiveData() {
  data = "";
  while(Serial2.available() > 0){
    delay(100);
    char d = Serial2.read();
    data += d;
  }
  return data;
}

int getTimeNow() {
  char fmt[64];
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  if (!getLocalTime(&timeinfo)) {
      Serial.println("Failed to obtain time");
      return 0;
  }
  strftime(fmt,sizeof(fmt), "%A, %B %d %Y %H:%M:%S", &timeinfo);
  snprintf(buf, sizeof(buf), fmt, tv.tv_usec);
  return 1;
}

int getTimeLogical() {
  char fmt[64];
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  if (!getLocalTime(&timeinfo)) {
      Serial.println("Failed to obtain time");
      return 0;
  }
  strftime(fmt,sizeof(fmt), "%H%M", &timeinfo);
  snprintf(timeLogic, sizeof(timeLogic), fmt, tv.tv_usec);
  return 1;
} 

void sendAntares(String data, int id) {
  getTimeNow();
  Serial.println(buf);
  if(id == 1) {
    antares.add("header", 1);
    antares.add("data", data);
    antares.add("WaktuReq", buf);
  }
  
  antares.publish(applicationName, deviceName);
  data = "";
}

void dataMonitoring() { //get data monitoring Arduino
  Serial2.print("monitoring");
  //rec = receiveData();
  receiveData();
  delay(50);
  if (data.length() > 0){
    Serial.println(data);
    sendAntares(data, 1);
  }
}

void getTimeMonitoring() {
  //Lakukan request Data Time Monitoring di db
  antares.add("header", 5);
  antares.add("data", "GetTimeMonitoring");
  antares.publish(applicationName, deviceControl);
  //Tangkap Respon Request Data Monitoring
  antaresAPI.get(applicationName, TimeMonitoring);
  if(antaresAPI.getInt("header") == 4) { //header 4 trigger by sensor
    sts_time = antaresAPI.getInt("waktuPengiriman"); //Dalam menit  
  }
}

void MonitoringSync(unsigned long Mon_Sync) {
  unsigned long TimeSync = sts_time * 60000; //Konversi menit to milisecond
  //getTimeLogical();
  if(Mon_Sync <= TimeSync) { //Jika time dibawah waktu pengiriman
    if(Mon_Sync == TimeSync) { //Jika waktu sama dengan waktu pengiriman
      dataMonitoring();
    }
  } else { //Jika time diatas waktu pengiriman
    if(Mon_Sync%TimeSync == 0) { // Jika waktu adalah kelipatan waktu pengiriman
      dataMonitoring();
    }
  } 
}

void statusFeeder() { //status feeder
  //Lakukan request Status Feeder Saat Ini
  antares.add("header", 6);
  antares.add("data", "FeederStatus");
  antares.publish(applicationName, deviceControl);
  //Tangkap status Feeder
  antaresAPI.get(applicationName, Feeder);
  if(antaresAPI.getInt("header" == 7)) {
    sts_FeederControl = antaresAPI.getInt("statusControl");
  }
}

void runFeeder() { //Jalankan feeder di arduino nya.
  Serial2.print("feeder");
}

void manualFeeder() {
  int manual = 0; //Default Feeder Mati
  //Check status feeder aktif atau tidak
  antares.add("header", 8);
  antares.add("data", "StatusFeederManual");
  antares.publish(applicationName, deviceControl);

  //Tangkap Respon Request feeder aktif atau tidak
  antaresAPI.get(applicationName, manFeeder);
  if(antaresAPI.getInt("header") == 9) { 
    manual = antaresAPI.getInt("statusFeeder");  
  }

  if(manual == 1) { //Jika button ditekan, Feeder Aktif
    runFeeder(); //Jalankan feeder
    antares.add("header", 10); //Rubah Status Feeder di database to disable
    antares.add("statusFeeder", 0);
    antares.publish(applicationName, manFeeder);
  }
}

void autoFeeder() {
  getTimeLogical();
  int waktuPertama = 0700, waktuKedua = 1400, waktuKetiga = 2100; //Waktu pengiriman pertama dan kedua
  //Dapatkan data waktu dari antares - db
  antares.add("header", 11);
  antares.add("data", "AutomaticFeeder");
  antares.publish(applicationName, deviceControl);
  //Tangkap status Feeder
  antaresAPI.get(applicationName, auFeeder);
  if(antaresAPI.getInt("header" == 12)) {
    waktuPertama = antaresAPI.getInt("waktuPertama");
    waktuKedua = antaresAPI.getInt("waktuKedua");
    waktuKetiga = antaresAPI.getInt("waktuKetiga");
  }
  //bandingkan data waktu dengan time sekarang
  if(timeLogic == waktuPertama) { //Jika waktu sama makan jalankan feeder
    runFeeder();
  } else if(timeLogic == waktuKedua) {
    runFeeder();
  } else if(timeLogic == waktuKetiga) {
    runFeeder();
  }
}

void loop() {
  antares.checkMqttConnection();
  TM_Sync = millis();

  getTimeMonitoring();
  MonitoringSync(TM_Sync);
   
  statusFeeder();
  if(sts_FeederControl == 1) { //Status aktif untuk Auto controlling
    autoFeeder();
  } else if(sts_FeederControl == 2) { //Status aktif untuk Manual controlling
    manualFeeder();
  }
}
