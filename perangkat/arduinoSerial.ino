#include <SoftwareSerial.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>
#include <Servo.h>
#define turbPin A0
#define m1 15

SoftwareSerial Serial2(13, 19); // 2 rx, 3 tx

String data, data2;
int trigPin = 4, echoPin = 3, tempPin = 12, buzzPin = 11, ledPin = 2;
const int rs = 10, en = 9, d4 = 5, d5 = 6, d6 = 7, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
Servo servoku;
int pos = 0;

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
  servoku.attach(m1);
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
}

void getDataSensor() {
  data2 = "";
  float waterL = WaterLevel();
  float temp = TempAquscape();
  float turb = Turbidity();
  data2 = "1:"+String(waterL)+":"+String(temp)+":"+String(turb)+";";
  Serial.println(data2);
  sendData(data2);
}

int runFeeder(){
  for (pos = 0; pos <= 180; pos += 1) {
    servoku.write(pos);              
    delay(15);                       
    Serial.println(pos);
  }
  data = "";
  return 1;
}

void cekData(String data) {
  if (data.length() > 0){
    Serial.print(data.c_str());
    String mon = "monitoring";
    String feed = "feeder";
    if(mon.equals(data.c_str())) {
      Serial.print(data);
      getDataSensor();
      data = "";
    } else if(feed.equals(data.c_str())) {
      Serial.println("Feeder Running"); //Program debug feeder
      runFeeder();
      data = "";
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
    cekData(data);
  }
}


void viewData() {
  lcd.setCursor(0, 0);
  lcd.print("S:"+ String(TempAquscape()) + "C" + " T:" + String(Turbidity()));
  lcd.setCursor(0, 1);
  lcd.print("WL : "+ String(WaterLevel()) + " cm");
}

void loop() {
  Serial.println("\nIni Arduino Uno");
  viewData();
  recData();
}