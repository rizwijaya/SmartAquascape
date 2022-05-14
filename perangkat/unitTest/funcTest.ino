#define ledPin  2
#define trigPin 4
#define echoPin 3
#define tempPin 12
#define buzPin 11
#define turbPin A0
#define m1 15
#define m2 16
#define m3 17
#define m4 18
#define rotation 512

#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>

const int rs = 10, en = 9, d4 = 8, d5 = 7, d6 = 6, d7 = 5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

OneWire oneWire(tempPin);

DallasTemperature sensors(&oneWire);
float Celcius=0;
float Fahrenheit=0;

float volt;
float ntu;

long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement


void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(echoPin, INPUT);
  pinMode(turbPin, INPUT); 
  pinMode(ledPin, OUTPUT);
  pinMode(trigPin, OUTPUT); 
  pinMode(buzPin, OUTPUT);
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);
  analogWrite(13, 100);
  lcd.begin(16, 2);
}

void loop() {
  //stepMotorTest();
  lcdTest();
  //turbTest();
  //buzTest();
  //tempTest();
  //usTest();
  ledTest();
  // put your main code here, to run repeatedly:
}

void ledTest(){
  digitalWrite(ledPin, HIGH);
  delay(50);
  digitalWrite(ledPin,LOW);
  delay(50);  
}

void usTest(){
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}

void tempTest(){
  sensors.requestTemperatures(); 
  Celcius=sensors.getTempCByIndex(0);
  Fahrenheit=sensors.toFahrenheit(Celcius);
  Serial.print(" C  ");
  Serial.print(Celcius);
  Serial.print(" F  ");
  Serial.println(Fahrenheit);
  delay(1000);
}


void buzTest(){
  tone(buzPin, 1000); // Send 1KHz sound signal...
  delay(1000);        // ...for 1 sec
  noTone(buzPin);     // Stop sound...
  delay(1000);  
}

void turbTest(){
    volt = 0;
    for(int i=0; i<800; i++)
    {
        volt += ((float)analogRead(turbPin)/1023)*5;
    }
    volt = volt/800;
    volt = round_to_dp(volt,2);
    if(volt < 2.5){
      ntu = 3000;
    }else{
      ntu = -1120.4*square(volt)+5742.3*volt-4353.8; 
    }
    Serial.print("Voltase: "+String(volt) +"  Kadar Kekeruhan: "+String(ntu));
}

float round_to_dp( float in_value, int decimal_place )
{
  float multiplier = powf( 10.0f, decimal_place );
  in_value = roundf( in_value * multiplier ) / multiplier;
  return in_value;
}

void onestep(){
write(1,0,0,0);
delay(5);
write(1,1,0,0);
delay(5);
write(0,1,0,0);
delay(5);
write(0,1,1,0);
delay(5);
write(0,0,1,0);
delay(5);
write(0,0,1,1);
delay(5);
write(0,0,0,1);
delay(5);
write(1,0,0,1);
delay(5);
}


void stepMotorTest(){
    int i;
    i=0;
    while(i<rotation){
      onestep();
      i++;
    }
}

void lcdTest(){
  Serial.println("mulai muncul");
  lcd.print("First line");
  lcd.setCursor(0,1);
  lcd.print("Second line");
  Serial.println("harusnya muncul");
  delay(200);
}

void write(int a,int b,int c,int d){
digitalWrite(m1,a);
digitalWrite(m2,b);
digitalWrite(m3,c);
digitalWrite(m4,d);
}