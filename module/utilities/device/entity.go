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
	ID          string    `json:"temperature_id"`
	Temperature float64   `json:"temperature"`
	CurrentTime time.Time `json:"current_time"`
	Data        string    `json:"data"`
}

type WaterLevel struct {
	ID          string    `json:"waterlevel_id"`
	WaterLevel  float64   `json:"water_level"`
	CurrentTime time.Time `json:"current_time"`
	Data        string    `json:"data"`
}

type Turbidity struct {
	ID          string    `json:"turbidity_id"`
	Turbidity   float64   `json:"turbidity"`
	CurrentTime time.Time `json:"current_time"`
	Data        string    `json:"data"`
}

type Monitoring struct {
	ID          string    `json:"id"`
	Turbidity   float64   `json:"turbidity"`
	WaterLevel  float64   `json:"water_level"`
	Temperature float64   `json:"temperature"`
	RequestTime time.Time `json:"request_time"`
}
