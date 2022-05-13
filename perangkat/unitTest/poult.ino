//Smart Poultry dan Mitigasi jika terjadi Bencana
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0

#include<LiquidCrystal.h>
#include<Servo.h>

LiquidCrystal lcd(7,6,5,4,3,2);
Servo servo;

const int blower1=8, buzz=12, blower2=13, pir=9, photo=A2, jarak=11, feeder=10;
int feedgate=A4;
int gas,temp, intensitas, buzzStatus;
float mois;
byte degree[8]={
  B00110,
  B01001,
  B01001,
  B00110,
  B00000,
  B00000
};

//Koneksi ke internet
String ssid     = "Simulator Wifi";
String password = "";
String host     = "api.thingspeak.com";
const int httpPort   = 80;
String url     = "/update?api_key=OSFPQ23I3EZ5JY5L&field";

int setupESP8266(void) { // Setup ESP8266 Serial Communication
  Serial.begin(115200);
  Serial.println("AT");
  delay(10);        
  if (!Serial.find("OK")) return 1;
  // Menghubungkan ke wifi
  Serial.println("AT+CWJAP=\"" + ssid + "\",\"" + password + "\"");
  delay(10);        //Menunggu respon terhubung
  if (!Serial.find("OK")) return 2;
  // Buka TCP Connection ke host
  Serial.println("AT+CIPSTART=\"TCP\",\"" + host + "\"," + httpPort);
  delay(50);
  if (!Serial.find("OK")) return 3;
  
  return 0;
}

void setup(){ 
  setupESP8266();  
  Serial.begin(9600);
  lcd.begin(16,2);
  //servo.attach(feeder);
  //delay(100);
  
  pinMode(buzz,OUTPUT);
  pinMode(blower2,OUTPUT);
  pinMode(blower1,OUTPUT);
  pinMode(feeder, OUTPUT); //Feeder Servo
  
  pinMode(pir,INPUT);
  pinMode(A0,INPUT); //Temperature
  pinMode(A1,INPUT); //Gas sensor
  pinMode(photo,INPUT); //Sensor Cahaya
  pinMode(A3,INPUT); //Potetiometer Blower
  pinMode(feedgate, INPUT); //Potentiometer Feeder Servo
}

void senddata(int data, int diagram) { //Kirim data
  String httpPacket = "GET " + url + String(diagram) + "=" + String(data) + " HTTP/1.1\r\nHost: " + host + "\r\n\r\n";
  int length = httpPacket.length();
  
  Serial.print("AT+CIPSEND=");
  Serial.println(length);
  delay(10);
  //Mengirimkan data menggunakan protokol HTTP
  Serial.print(httpPacket);
  delay(10);
  if (!Serial.find("SEND OK\r\n")) return;   
}

int temperature() { //Sistem Pengaturan suhu cerdas
//Blower/kipas bergerak sesuai dengan temperatur
  if(temp>=42) {
    digitalWrite(blower1,HIGH);
    digitalWrite(blower2,HIGH);
  } else if(temp>35 && temp<=40) {
    digitalWrite(blower1,HIGH);
    digitalWrite(blower2,LOW);
  } else if(temp>41 && temp<=45) {
    digitalWrite(blower1,LOW);
    digitalWrite(blower2,HIGH);
  } else if(temp<45) {
    digitalWrite(blower1,LOW);
    digitalWrite(blower2,LOW);
  } 
  delay(200);
  senddata(temp,1); //Mengirim Data
  return temp;
}

int amonia(){ //Sistem pengaturan kadar amoniak di kandang
  if(gas >= 25){
    digitalWrite(blower1, HIGH);
    digitalWrite(blower2, HIGH);
  }else if(gas < 20 && gas >25){
    digitalWrite(blower1, HIGH);
    digitalWrite(blower2, LOW);
  }else{
    digitalWrite(blower1, LOW);
    digitalWrite(blower2, LOW);
  }
  senddata(gas,2); //Mengirim Data
  return gas;
}

void nada(int freq, int del) { //Fungsi untuk memutar nada
    tone(buzz, freq, del);
    delay(del);	
}

int cahaya() { //Fungsi Deteksi Intrusi saat malam hari
  int value = analogRead(photo);
  //Aktivasi PIR Sensor
  if(value < 500){
    if(digitalRead(pir)==1) {
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("Ada Penyusup");
        delay(300);
        if(buzzStatus == 0) { //Mengecek status buzzer, Jika mati maka akan menyala
          buzzStatus = 1;
          //Lirik Lagu Armada Pencuri Hati (Line 4) 
          //do, do, _, re, mi, so, _, so, fa, mi (Kamu pencuri pencuri)
          for(int i=1;i<=2;i++){  // 100 Hz do
              nada(100, 500*i); 
          }
          nada(250, 1000);  // 250 Hz re
          nada(500, 1000);  // 500 Hz mi
          nada(800, 1000);  // 250 Hz so
          nada(800, 1000);  // 250 Hz so
          nada(700, 1000);  // 500 Hz fa
          nada(500, 1000);  // 500 Hz mi
        }
    }
    buzzStatus = 0; 
  }
  return value;
}

void kebakaran() { //Sistem deteksi kebakaran
  if(gas >= 40) { //Jika terdapat kepulan asap
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Asap!!");
      lcd.setCursor(0, 1);
      lcd.print("Udara " + String(gas) + " ppm");
      if(buzzStatus == 0) { //Putar Audio
        buzzStatus = 1;
        for(int i=1; i<=3; i++) { //Alarm Peringatan asap
          nada(500, 1000);
        }
      }
  } else if(temp >= 75 && gas >= 40) { //Jika terjadi kebakaran dan terdapat Api
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Kebakaran!!");
      lcd.setCursor(0, 1);
      lcd.print("Udara " + String(gas) + " ppm");
      if(buzzStatus == 0) { //Putar Audio
        buzzStatus = 1;
        alarmKebakaran(); //Alarm Peringatan kebakaran  
      }
  }
  buzzStatus = 0;
}

long microsecondsToCentimeters(long microseconds) { //Konversi hasil pengurukuran ultrasonik ke cm
  return microseconds / 29 / 2;
}

void smartFeeder() { //Sistem pakan dan minum cerdas
    int wadah = 400;
    long duration, cm;
    //Pengaturan sensor ultrasonik
  	pinMode(jarak, OUTPUT);
    digitalWrite(jarak, LOW);
    delayMicroseconds(2);
    digitalWrite(jarak, HIGH);
    delayMicroseconds(5);
    digitalWrite(jarak, LOW);
  
	pinMode(jarak, INPUT);
    duration = pulseIn(jarak, HIGH);
    cm = microsecondsToCentimeters(duration);
    Serial.println(cm);
    if(cm>200) { //Jika kapasitas dibawah 200 cm/setengah dari wadah
      //digitalWrite(feeder, HIGH); //Servo
      servo.attach(feeder);
      servo.write(90);
      delay(1000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Pakan Habis!!");
      lcd.setCursor(0, 1);
      lcd.print("Sisa " + String(wadah-cm) + " cm");
      senddata(1, 3); //Kirim data riwayat pengisian pakan
      peringatan(); //Putar Audio Peringatan 
    } else { //Jika kapasitas lebih dari setengah
      if(digitalRead(jarak)==1) {
          //digitalWrite(feeder, LOW); //Servo
          servo.attach(feeder);
		  servo.write(0);
  	  	  delay(1000);
      }
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Pakan Aman");
      lcd.setCursor(0, 1);
      lcd.print("Kondisi " + String(wadah-cm) + " cm");
      musik(); //Putar Musik Nyaman
    }
}

void view(int temp, int gas, int intensitas) { //Fungsi untuk menampilkan di LCD
  lcd.setCursor(0,0); //Mencetak Temperature
  lcd.print("Temp = " + String(temp) + " C");  
  lcd.setCursor(0, 1); //Mencetak Amoniak (NH3)
  lcd.print("NH3 = " + String(gas) + " ppm");
  delay(1000);
  lcd.setCursor(0, 0); //Mencetak Intensitas
  lcd.print("Intensitas = " + String(intensitas));
  delay(1000);
}

void loop() {
  // Inisiliasasi Analog sensor
  gas=map(analogRead(A1),0,358,0,125);
  temp=map(analogRead(A0),20,358,-40,125);
  mois=map(analogRead(A3),0,5,0,1); //Potention Meter Blower
  feedgate=map(analogRead(A4),0,1023,0,180); //Potention Meter Feeder Servo
  
  temp = temperature(); //Sensor Temperature
  gas = amonia(); // NH3 Sensor
  intensitas = cahaya(); //Sensor Cahaya Photoresistor
  view(temp, gas, intensitas); //Tampilkan hasil ke LCD
  kebakaran(); //Sistem Kebakaran
  smartFeeder(); //Smart Feeder
}

// Musik Nyaman dan Peringatan
void peringatan() { //Peringatan pakan habis
  int tempo = 180; 
  int melody[] = { // Nokia Ringtone
    NOTE_E5, 8, NOTE_D5, 8, NOTE_FS4, 4, NOTE_GS4, 4, 
    NOTE_CS5, 8, NOTE_B4, 8, NOTE_D4, 4, NOTE_E4, 4, 
    NOTE_B4, 8, NOTE_A4, 8, NOTE_CS4, 4, NOTE_E4, 4,
    NOTE_A4, 2, 
  };
  int notes = sizeof(melody) / sizeof(melody[0]) / 2;
  int wholenote = (60000 * 4) / tempo;

  int divider = 0, noteDuration = 0;
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
    divider = melody[thisNote + 1];
    if (divider > 0) {
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5;
    }
    
    tone(buzz, melody[thisNote], noteDuration * 0.9);
    delay(noteDuration);
    noTone(buzz);
  }
}

void musik() { //Peringatan pakan penuh / Ayam nyaman
  int tempo = 100;
  int melody[] = { // Cannon in D - Pachelbel
    NOTE_FS4,2, NOTE_E4,2,
    NOTE_D4,2, NOTE_CS4,2,
    NOTE_B3,2, NOTE_A3,2,
    NOTE_B3,2, NOTE_CS4,2,
    NOTE_FS4,2, NOTE_E4,2,
    NOTE_D4,2, NOTE_CS4,2,
    NOTE_B3,2, NOTE_A3,2,
    NOTE_B3,2, NOTE_CS4,2,
    NOTE_D4,2, NOTE_CS4,2,
    NOTE_B3,2, NOTE_A3,2,
    NOTE_G3,2, NOTE_FS3,2,
    NOTE_G3,2, NOTE_A3,2,

    NOTE_D4,4, NOTE_FS4,8, NOTE_G4,8, NOTE_A4,4, NOTE_FS4,8, NOTE_G4,8, 
    NOTE_A4,4, NOTE_B3,8, NOTE_CS4,8, NOTE_D4,8, NOTE_E4,8, NOTE_FS4,8, NOTE_G4,8, 
    NOTE_FS4,4, NOTE_D4,8, NOTE_E4,8, NOTE_FS4,4, NOTE_FS3,8, NOTE_G3,8,
    NOTE_A3,8, NOTE_G3,8, NOTE_FS3,8, NOTE_G3,8, NOTE_A3,2,
    NOTE_G3,4, NOTE_B3,8, NOTE_A3,8, NOTE_G3,4, NOTE_FS3,8, NOTE_E3,8, 
    NOTE_FS3,4, NOTE_D3,8, NOTE_E3,8, NOTE_FS3,8, NOTE_G3,8, NOTE_A3,8, NOTE_B3,8,

    NOTE_G3,4, NOTE_B3,8, NOTE_A3,8, NOTE_B3,4, NOTE_CS4,8, NOTE_D4,8,
    NOTE_A3,8, NOTE_B3,8, NOTE_CS4,8, NOTE_D4,8, NOTE_E4,8, NOTE_FS4,8, NOTE_G4,8, NOTE_A4,2,
    NOTE_A4,4, NOTE_FS4,8, NOTE_G4,8, NOTE_A4,4,
    NOTE_FS4,8, NOTE_G4,8, NOTE_A4,8, NOTE_A3,8, NOTE_B3,8, NOTE_CS4,8,
    NOTE_D4,8, NOTE_E4,8, NOTE_FS4,8, NOTE_G4,8, NOTE_FS4,4, NOTE_D4,8, NOTE_E4,8,
    NOTE_FS4,8, NOTE_CS4,8, NOTE_A3,8, NOTE_A3,8,

    NOTE_CS4,4, NOTE_B3,4, NOTE_D4,8, NOTE_CS4,8, NOTE_B3,4,
    NOTE_A3,8, NOTE_G3,8, NOTE_A3,4, NOTE_D3,8, NOTE_E3,8, NOTE_FS3,8, NOTE_G3,8,
    NOTE_A3,8, NOTE_B3,4, NOTE_G3,4, NOTE_B3,8, NOTE_A3,8, NOTE_B3,4,
    NOTE_CS4,8, NOTE_D4,8, NOTE_A3,8, NOTE_B3,8, NOTE_CS4,8, NOTE_D4,8, NOTE_E4,8,
    NOTE_FS4,8, NOTE_G4,8, NOTE_A4,2,
  };
  int notes = sizeof(melody) / sizeof(melody[0]) / 2;
  int wholenote = (60000 * 4) / tempo;
  int divider = 0, noteDuration = 0;
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
    divider = melody[thisNote + 1];
    if (divider > 0) {
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5;
    }

    tone(buzz, melody[thisNote], noteDuration * 0.9);
    delay(noteDuration);
    noTone(buzz);
  }
}

void alarmKebakaran() { //Peringatan jika terjadi kebakaran
  int tempo = 200;
  int melody[] = { // Super Mario Bros theme
    //game over sound
    NOTE_C5,-4, NOTE_G4,-4, NOTE_E4,4, //45
    NOTE_A4,-8, NOTE_B4,-8, NOTE_A4,-8, NOTE_GS4,-8, NOTE_AS4,-8, NOTE_GS4,-8,
    NOTE_G4,8, NOTE_D4,8, NOTE_E4,-2,  

  };

  int notes = sizeof(melody) / sizeof(melody[0]) / 2;
  int wholenote = (60000 * 4) / tempo;
  int divider = 0, noteDuration = 0;
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    divider = melody[thisNote + 1];
    if (divider > 0) {
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5;
    }

    tone(buzz, melody[thisNote], noteDuration * 0.9);
    delay(noteDuration);
    noTone(buzz);
  }
}