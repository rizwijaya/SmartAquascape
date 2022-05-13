package device

import "time"

type Device struct {
	No_device         int
	Id_device         string
	Energy            string
	Power             string
	Voltage           string
	Ampere            string
	PowerF            string
	Battery           string
	Relay_status      int
	Device_time       time.Time
	Alarm_type        int
	Device_registered time.Time
	Restart_status    int
	Blue_status       int
	Lamp_treshold     string
}

type Temperature struct {
	TempID      int
	Temperature float64
	CurrentTime time.Time
	Data        string
}

type WaterLevel struct {
	LevelID     int
	WaterLevel  float64
	CurrentTime time.Time
	Data        string
}

type Turbidity struct {
	TurbidityID int
	CurrentTime time.Time
	Data        string
}
