#define ledPin  2
#define trigPin 4
#define echoPin 3
#define tempPin 12
#define buzPin 11

#include <OneWire.h>
#include <DallasTemperature.h>

OneWire oneWire(tempPin);

DallasTemperature sensors(&oneWire);
float Celcius=0;
float Fahrenheit=0;


long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement


void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  pinMode(buzPin, OUTPUT);

}

void loop() {
  buzTest();
  tempTest();
  usTest();
  ledTest();
  // put your main code here, to run repeatedly:

}

void ledTest(){
  digitalWrite(ledPin, HIGH);
  delay(500);
  digitalWrite(ledPin,LOW);
  delay(500);  
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