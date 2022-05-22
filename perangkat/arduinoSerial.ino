#include <SoftwareSerial.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>
#define turbPin A0
#define m1 15
#define m2 16
#define m3 17
#define m4 18
#define rotation 512

SoftwareSerial Serial2(13, 19); // 2 rx, 3 tx

String data, data2;
int trigPin = 4, echoPin = 3, tempPin = 12, buzzPin = 11, ledPin = 2;
const int rs = 10, en = 9, d4 = 5, d5 = 6, d6 = 7, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

OneWire oneWire(tempPin);
DallasTemperature sensors(&oneWire);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial2.begin(9600);
  sensors.begin();
  
  pinMode(turbPin, INPUT); 
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzPin, OUTPUT);
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);
  lcd.begin(16, 2);
}

float WaterLevel() {
  long duration;
  int distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  if (distance < 23) {
    tone(buzzPin, 1000);
    delay(1000);
    noTone(buzzPin);
    delay(1000);
    digitalWrite(ledPin, HIGH);  
  } else {
    digitalWrite(ledPin, LOW);
  }
  return distance;
}

float TempAquscape() {
  float Celcius;
  sensors.requestTemperatures(); 
  Celcius=sensors.getTempCByIndex(0);
  if (Celcius < 23 && Celcius > 26) {
    digitalWrite(ledPin, HIGH);  
  } else {
    digitalWrite(ledPin, LOW);
  }
  return Celcius;
}

float round_to_dp( float in_value, int decimal_place ) {
  float multiplier = powf( 10.0f, decimal_place );
  in_value = roundf( in_value * multiplier ) / multiplier;
  return in_value;
}

float Turbidity() {
  float volt = 0;
  float ntu;
  for(int i=0; i<800; i++) {
      volt += ((float)analogRead(turbPin)/1023)*5;
  }
  volt = volt/800;
  volt = round_to_dp(volt,2);
  if(volt < 2.5){
    ntu = 3000;
  }else{
    ntu = -1120.4*square(volt)+5742.3*volt-4353.8; 
  }
  //Serial.print("Voltase: "+String(volt) +"  Kadar Kekeruhan: "+String(ntu));
  if (ntu > 400) {
    tone(buzzPin, 1000);
    delay(1000);
    noTone(buzzPin);
    delay(1000);
    digitalWrite(ledPin, HIGH);  
  } else {
    digitalWrite(ledPin, LOW);
  }
  return ntu;
}

void sendData(String data2) {
  Serial2.print(data2);
  //data = "";
  //data2 = "";
}

void getDataSensor() {
  data2 = "";
  float waterL = WaterLevel();
  float temp = TempAquscape();
  float turb = Turbidity();
  data2 = "1:"+String(waterL)+":"+String(temp)+":"+String(turb)+";";
  //Serial.println(data2);
  sendData(data2);
}

void runFeeder(){
  Serial.println("Harusnya servo jalan");
  // fwrite(1,0,0,0);
  // //delay(5);
  // fwrite(1,1,0,0);
  // //delay(5);
  // fwrite(0,1,0,0);
  // //delay(5);
  // fwrite(0,1,1,0);
  // //delay(5);
  // fwrite(0,0,1,0);
  // //delay(5);
  // fwrite(0,0,1,1);
  // //delay(5);
  // fwrite(0,0,0,1);
  // //delay(5);
  // fwrite(1,0,0,1);
  // //delay(5);
}

void cekData(String data) {
  if (data.length() > 0){
    //Serial.print(data);
    if(strcmp(data.c_str(), "monitoring")) {
      Serial.print(data);
      getDataSensor();
      data = "";
    } else if(strcmp(data.c_str(), "feeder")) {
      runFeeder();
      Serial.println("Feeder Running"); //Program debug feeder
    }
  }
}

void recData() {
  while(Serial2.available() > 0){
    delay(50);
    char d = Serial2.read();
    data += d;
  }
  if (data.length() > 0){
    //Serial.println(data);
    cekData(data);
    //data = "";
  }
}

void viewData() {
  lcd.setCursor(0, 0);
  lcd.print("Suhu: "+ String(TempAquscape()) + " C");
  lcd.setCursor(15, 0);
  lcd.print("Kejernihan: "+ String(Turbidity()));
  lcd.setCursor(0, 1);
  lcd.print("Water Level: "+ String(WaterLevel()) + 
  " cm");
}

void loop() {
  Serial.println("\nIni Arduino Uno");
  viewData();
  recData();
}