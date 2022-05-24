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
	ID          string    `json:"id"`
	Temperature float64   `json:"temperature"`
	CurrentTime time.Time `json:"current_time"`
	Data        string    `json:"data"`
}

type WaterLevel struct {
	ID          string    `json:"id"`
	WaterLevel  float64   `json:"water_level"`
	CurrentTime time.Time `json:"current_time"`
	Data        string    `json:"data"`
}

type Turbidity struct {
	ID          string    `json:"id"`
	Turbidity   float64   `json:"turbidity"`
	CurrentTime time.Time `json:"current_time"`
	Data        string    `json:"data"`
}

type Monitoring struct {
	ID           string    `json:"id"`
	Temperature  string    `json:"temperature"`
	WaterLevel   string    `json:"water_level"`
	Turbidity    string    `json:"turbidity"`
	Request_time time.Time `json:"request_time"`
}

type MonTable struct {
	ID           string    `json:"id"`
	Temperature  string    `json:"temperature"`
	WaterLevel   string    `json:"water_level"`
	Turbidity    string    `json:"turbidity"`
	Request_time time.Time `json:"request_time"`
}

type LastDataSensor struct {
	ID           string    `json:"id"`
	Temperature  string    `json:"temperature"`
	WaterLevel   string    `json:"water_level"`
	Turbidity    string    `json:"turbidity"`
	Request_time time.Time `json:"request_time"`
}

type Inner struct {
	StatusControl int `json:"statusControl"`
}

type Outer struct {
	Con Inner `json:"con"`
}

type Outmost struct {
	MM Outer `json:"m2m:cin"`
}

type StatusFeed struct {
	//Con []StatusControl `json:"con"`
	Satu string `json:"m2m:cin"`
}

// type StatusControl struct {
// 	StatusControl int `json:"statusControl"`
// }
