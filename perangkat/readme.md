### Mikrocontroller
## Arduino Uno R3
## ESP8266 01
### Input
## Sensor Suhu DS18b20
## Sensor PH-4502C
## Sensor TDS RK500-18
## Sensor Ultrasonik
### Output
## Motor Servo (Feeder)
## LCD
## LED Red
## Buzzer
### Extended
## Jumper Wired
## Relay
```json
Data Structure:
//Data Monitoring from Device - antares
Monitoring Sensor //Device Name Topic
{
    header : 1,
    data    :"1:WaterLevel:Temperature:Turbidity",
    waktuReq : ""
}
//Get Time Monitoring from device to antares
// Get Data Sensor Monitoring:
// {
//     header : 5,
//     data   :"GetTimeMonitoring"
// }

Respon Data Sensor Monitoring: //from website (mqtt service) to antares
{ //Time Monitoring Topic
    header : 4,
    waktuPengiriman : "", // Waktu pengiriman data Monitoring dalam menit
}

//Cek Status Feeder
// Check Status Feeder: //from device to antares
// {
//     header : 6,
//     data : "FeederStatus"
// }
Respon Status Feeder //from website (mqtt service) to antares
{ ///sts feeeder topic
    header : 7,
    statusControl : 1 //sts 1 untk time, sts 2 untk manual.
}

//Controlling Feeder Manual
// Check Status Feeder Manual { //From device to antares
//     header : 8,
//     data : "StatusFeederManual"
// }

Respon Status Feeder Manual { //From website service to antares //ManFeeder Topic
    header : 9,
    statusFeeder : 1 // jika 1 feeder aktif/button ditekan, jika 0 feeder tidak aktif/button tidak ditekan
}

Request Disable Feeder From Perangkat to DB { //From device to antares //ManFeeder Topic
    header : 9,
    statusFeeder : 0
}
//Request Data Automatic Feeder Nyala dan Mati dengan 2 data:
// Request Data Automatic Feeder //From device to antares
// {
//     header : 11,
//     data : "AutomaticFeeder"
// }

Respon Data Feeder Automatic //From website (mqtt service) to antares
{ //auFeeder Topic
    header : 12,
    waktuPertama : "HHMM",
    waktuKedua : "HHMM",
    waktuKetiga : "HHMM"
}
```