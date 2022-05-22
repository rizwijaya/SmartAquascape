#include <AntaresESP32MQTT.h>
#include <AntaresESP32HTTP.h>
// #include <ArduinoJson.h>
// #include <PubSubClient.h>

#define ACCESSKEY "9fb52249c593c66d:b719370dce7d93b9"       // Ganti dengan access key akun Antares anda
#define WIFISSID "Playmedia"         // Ganti dengan SSID WiFi anda
#define PASSWORD "12345678"     // Ganti dengan password WiFi anda

#define applicationName "smartAquascape"   // Ganti dengan application name Antares yang telah dibuat
#define deviceName "Aquascape-001"     // Pantau data monitoring
//#define deviceControl "Aquascape-Control" //Controlling Device
#define TimeMonitoring "TimeMonitoring" //Rentang Waktu Pertukaran Data Monitoring
#define stsFeeder "Aquascape-Feeder"
#define manFeeder "Manual-Feeder"
#define auFeeder "Auto-Feeder"

AntaresESP32MQTT antares(ACCESSKEY);    // Buat objek antares MQTT
AntaresESP32HTTP antaresAPI(ACCESSKEY);    // Buat objek antares API

String data;
struct tm timeinfo;
struct timeval tv;
char buf[64], timeLogic[64];
//unsigned long TM_Sync;
int sts_FeederControl = 2; //default Manual Control
const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 7 * 3600;
const int daylightOffset_sec = 0;
unsigned long sts_time = 1;
unsigned long previousTimeMonitoring = 0;

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
  antares.setDebug(true);
  antaresAPI.setDebug(true);
  antares.wifiConnection(WIFISSID,PASSWORD);  // Mencoba untuk menyambungkan ke WiFi
  antaresAPI.wifiConnection(WIFISSID,PASSWORD);
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
  // antares.add("header", 5);
  // antares.add("data", "GetTimeMonitoring");
  // antares.publish(applicationName, deviceControl);
  //Tangkap Respon Request Data Monitoring
  antaresAPI.get(applicationName, TimeMonitoring);
  //Serial.println(antaresAPI.getResponse());
  Serial.println(antaresAPI.getInt("header"));
  if(antaresAPI.getInt("header") == 4) { //header 4 trigger by sensor
    sts_time = antaresAPI.getInt("waktuPengiriman"); //Dalam menit  
  }
}

void MonitoringSync() {
  Serial.println("Monitoring Sync" + String(sts_time));
  unsigned long Mon_Sync = millis();
  unsigned long TimeSync = sts_time * 30000;//60000; //Konversi menit to milisecond
  //Serial.println(Mon_Sync);
  if ((unsigned long)(Mon_Sync - previousTimeMonitoring) >= TimeSync) {
    dataMonitoring();
    previousTimeMonitoring = Mon_Sync;
  }
  //getTimeLogical();
  // if(Mon_Sync <= TimeSync) { //Jika time dibawah waktu pengiriman
  //   if(Mon_Sync == TimeSync) { //Jika waktu sama dengan waktu pengiriman
  //     dataMonitoring();
  //   }
  // } else { //Jika time diatas waktu pengiriman
  //   if(Mon_Sync%TimeSync == 0) { // Jika waktu adalah kelipatan waktu pengiriman
  //     dataMonitoring();
  //   }
  // } 
}

void statusFeeder() { //status feeder
  //Lakukan request Status Feeder Saat Ini
  // antares.add("header", 6);
  // antares.add("data", "FeederStatus");
  // antares.publish(applicationName, deviceControl);
  //Tangkap status Feeder
  antaresAPI.get(applicationName, stsFeeder);
  if(antaresAPI.getInt("header") == 7) {
    sts_FeederControl = antaresAPI.getInt("statusControl");
  }
}

void runFeeder() { //Jalankan feeder di arduino nya.
  Serial2.print("feeder");
}

void manualFeeder() {
  int manual = 0; //Default Feeder Mati
  //Check status feeder aktif atau tidak
  // antares.add("header", 8);
  // antares.add("data", "StatusFeederManual");
  // antares.publish(applicationName, deviceControl);

  //Tangkap Respon Request feeder aktif atau tidak
  antaresAPI.get(applicationName, manFeeder);
  if(antaresAPI.getInt("header") == 9) { 
    manual = antaresAPI.getInt("statusFeeder");  
  }

  if(manual == 1) { //Jika button ditekan, Feeder Aktif
    runFeeder(); //Jalankan feeder
    antares.add("header", 9); //Rubah Status Feeder di database to disable
    antares.add("statusFeeder", 0);
    antares.publish(applicationName, manFeeder);
  }
}

void autoFeeder() {
  getTimeLogical();
  String waktuPertama = "0700", waktuKedua = "1400", waktuKetiga = "2100"; //Waktu pengiriman pertama dan kedua
  //Dapatkan data waktu dari antares - db
  // antares.add("header", 11);
  // antares.add("data", "AutomaticFeeder");
  // antares.publish(applicationName, deviceControl);
  //Tangkap status Feeder
  antaresAPI.get(applicationName, auFeeder);
  if(antaresAPI.getInt("header") == 12) {
    // snprintf(waktuPertama, sizeof(waktuPertama), antaresAPI.getString("waktuPertama"));
    // snprintf(waktuKedua, sizeof(waktuKedua), antaresAPI.getString("waktuKedua"));
    // snprintf(waktuKetiga, sizeof(waktuKetiga), antaresAPI.getString("waktuKetiga"));
    waktuPertama = antaresAPI.getString("waktuPertama");
    waktuKedua = antaresAPI.getString("waktuKedua");
    waktuKetiga = antaresAPI.getString("waktuKetiga");
  }
  //bandingkan data waktu dengan time sekarang
  String waktuSekarang(timeLogic);
  if(waktuSekarang == waktuPertama) { //Jika waktu sama makan jalankan feeder
    runFeeder();
  } else if(waktuSekarang == waktuKedua) {
    runFeeder();
  } else if(waktuSekarang == waktuKetiga) {
    runFeeder();
  }
}

void loop() {
  //TM_Sync = millis();
  antares.checkMqttConnection();
  getTimeMonitoring();
  MonitoringSync();
   
  // statusFeeder();
  // if(sts_FeederControl == 1) { //Status aktif untuk Auto controlling
  //   autoFeeder();
  // } else if(sts_FeederControl == 2) { //Status aktif untuk Manual controlling
  //   manualFeeder();
  // }
}