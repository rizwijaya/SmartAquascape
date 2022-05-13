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
Monitoring Sensor
{
    header : 1,
    Suhu : "",
    WaterLevel : "",
    Turbidity : "",
    WaktuReq : ""
}
Konfigure Sending Sensor Data:
{
    header : 4,
    WaktuPengiriman : "", // Waktu pengiriman data Monitoring dalam menit
}
Controlling Sensor Feeder:
{
    header : 2,
    status : "",
    statusFeeder: "",
    WaktuReq : ""
}
Trigger Sensor By Time:
{
    header : 3,
    status: "",
    WaktuON_jam : "",
    WaktuON_menit : "",
    WaktuOFF_jam : "",
    WaktuOFF_menit : "",
    WaktuReq : ""
}
```