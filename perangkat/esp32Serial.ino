#include <AntaresESP32MQTT.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>
#include "time.h"

#define ACCESSKEY "9fb52249c593c66d:b719370dce7d93b9"       // Ganti dengan access key akun Antares anda
#define WIFISSID "ayangto"         // Ganti dengan SSID WiFi anda
#define PASSWORD "ywsh5677"     // Ganti dengan password WiFi anda

#define applicationName "smartAquascape"   // Ganti dengan application name Antares yang telah dibuat
#define deviceName "Aquascape-001"     // Ganti dengan device Antares yang telah dibuat

AntaresESP32MQTT antares(ACCESSKEY);    // Buat objek antares
String data, rec;
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 7 * 3600;
const int  daylightOffset_sec = 0;

void callback(char topic[], byte payload[], unsigned int length) {
  antares.get(topic, payload, length);  // Menyimpan topic dan payload ke penampungan data sementara
  if(antares.getInt("header") == 2) { //header 2 controlling device
    int status = antares.getInt("statusFeeder");
    if(status == 1) { //Status aktif untuk Manual controlling
      controlFeeder(); //Nyalakan servo atau feeder
    }
  } else if(antares.getInt("header") == 3) { //header 3 trigger by time
    //Setting Template for trigger by time
  }
}

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
  antares.setDebug(false);
  antares.wifiConnection(WIFISSID,PASSWORD);  // Mencoba untuk menyambungkan ke WiFi
  antares.setMqttServer();  // Inisiasi server MQTT Antares
  antares.setCallback(callback);
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  getTime();
}

String getTime(){
  struct tm timeinfo;
  char buffer[40];
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return "0";
  }
  //Serial.println(&timeinfo, "%d %B %Y %H:%M:%S");
  sprintf(buffer, "%d:%B:%Y:%H:%M:%S", &timeinfo);
  return buffer;
}

String getTimeNoSplit(){
  struct tm timeinfo;
  char buffer[40];
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return "0";
  }
  //Serial.println(&timeinfo, "%d %B %Y %H:%M:%S");
  sprintf(buffer, "%d%B%Y%H%M%S", &timeinfo);
  return buffer;
}

String receiveData() {
  while(Serial2.available() > 0){
    delay(10);
    char d = Serial2.read();
    data += d;
  }
  return data;
}

void sendAntares(String data, int id) {
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  if(id == 1) {
    antares.add("header", 1);
    antares.add("data", data);
    antares.add("WaktuReq", getTime());
  }
  
  antares.publish(applicationName, deviceName);   
}

void dataMonitoring() { //get data monitoring Arduino
  Serial2.print("monitoring");
  rec = receiveData();
  sendAntares(rec, 1);
}

void controlFeeder() { //control feeder
  Serial2.print("feeder");
  // rec = receiveData();
  // sendAntares(rec, 3);
}

void loop() {
  antares.checkMqttConnection();
  dataMonitoring();  
  //controlFeeder();
}

void kirimAntares(String data, int id) {
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  if(id == 1) {
    antares.add("header", 1);
    antares.add("data", data);
    antares.add("WaktuReq", getTime());
  }
  
  antares.publish(applicationName, deviceName);   
}   