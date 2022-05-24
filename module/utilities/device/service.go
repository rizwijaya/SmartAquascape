package device

import (
	"errors"
	"fmt"
)

type Service interface {
	GetAllDevice() ([]Device, error)
	GetDeviceByID(ID int) (Device, error)
	GetAllTemperatures() ([]Temperature, error)
	GetAllWaterLevel() ([]WaterLevel, error)
	GetOneTurbidityByID(ID string) (Turbidity, error)
	GetOneWaterLevelByID(ID string) (WaterLevel, error)
	GetOneTemperatureByID(ID string) (Temperature, error)
	GetAllTurbidity() ([]Turbidity, error)
	MonitoringDevice() ([]Monitoring, error)
	MonitoringTable() ([]MonTable, error)
	GetLatest() ([]LastDataSensor, error)
}

type service struct {
	repository Repository
}

func NewService(repository Repository) *service {
	return &service{repository}
}

func (s *service) GetAllDevice() ([]Device, error) {
	device, err := s.repository.GetAllDevice()
	if err != nil {
		return device, err
	}

	return device, nil
}

func (s *service) GetDeviceByID(ID int) (Device, error) {
	device, err := s.repository.FindByID(ID)
	if err != nil {
		return device, err
	}

	if device.No_device == 0 {
		return device, errors.New("no device found on with that ID")
	}

	return device, nil
}

func (s *service) GetAllTemperatures() ([]Temperature, error) {
	temperature, err := s.repository.GetAllTemperatures()
	if err != nil {
		return temperature, err
	}

	return temperature, nil
}

func (s *service) GetAllWaterLevel() ([]WaterLevel, error) {
	waterLevel, err := s.repository.GetAllWaterLevel()
	if err != nil {
		return waterLevel, err
	}

	return waterLevel, nil
}

func (s *service) GetAllTurbidity() ([]Turbidity, error) {
	turbidity, err := s.repository.GetAllTurbidity()
	if err != nil {
		return turbidity, err
	}

	return turbidity, nil
}

func (s *service) GetOneTurbidityByID(ID string) (Turbidity, error) {
	turbidity, err := s.repository.FindTurbidityByID(ID)
	if err != nil {
		return turbidity, err
	}

	var check Turbidity
	if check.Data >= `400` {
		fmt.Println("Air Keruh")
	} else if check.Data < `400` {
		fmt.Println("Air Jernih")
	}

	return turbidity, nil
}

func (s *service) GetOneWaterLevelByID(ID string) (WaterLevel, error) {
	water_level, err := s.repository.FindWaterLevelByID(ID)
	if err != nil {
		return water_level, err
	}

	var check WaterLevel
	if check.Data >= `23` && check.Data <= `25` {
		fmt.Println("Ketinggian Air Normal")
	} else if check.Data < `23` {
		fmt.Println("Ketinggian Air Kurang")
	}

	return water_level, nil
}

func (s *service) GetOneTemperatureByID(ID string) (Temperature, error) {
	temperature, err := s.repository.FindTemperatureByID(ID)
	if err != nil {
		return temperature, err
	}

	var check Temperature
	if check.Data < `24` || check.Data > `25` {
		fmt.Println("Suhu air tidak normal")
	} else if check.Data >= `24` || check.Data <= `25` {
		fmt.Println("Suhu air normal")
	}

	return temperature, nil
}

func (s *service) MonitoringDevice() ([]Monitoring, error) {
	monitoring, err := s.repository.MonitoringDevice()
	if err != nil {
		return monitoring, err
	}

	return monitoring, nil
}

func (s *service) MonitoringTable() ([]MonTable, error) {
	MonTable, err := s.repository.MonitoringTable()
	if err != nil {
		return MonTable, err
	}

	return MonTable, nil
}

func (s *service) GetLatest() ([]LastDataSensor, error) {
	last, err := s.repository.GetLatest()
	if err != nil {
		return last, err
	}

	// var check LastDataSensor
	// //fmt.Println(check.Turbidity, err, reflect.TypeOf(check.Turbidity))
	// //fmt.Println(data3)
	// //turb, err := strconv.ParseFloat(check.Turbidity, 8)
	// // turb, err := strconv.Atoi(check.Turbidity)
	// // fmt.Println(turb, err)
	// fmt.Println(check.Turbidity)

	return last, nil
}

// func (s *service) GetStatusFeeder(string, error) {
// 	tr := &http.Transport{
// 		TLSClientConfig: &tls.Config{
// 			MaxVersion: tls.VersionTLS12,
// 		},
// 	}
// 	client := &http.Client{Transport: tr}

// 	req, err := http.NewRequest("GET", "https://platform.antares.id:8443/~/antares-cse/antares-id/smartAquascape/Aquascape-Feeder/la", nil)
// 	req.Header.Add("X-M2M-Origin", "9fb52249c593c66d:b719370dce7d93b9")
// 	req.Header.Add("Content-Type", "application/json;ty=4")
// 	req.Header.Add("Accept", "application/json")

// 	if err != nil {
// 		log.Fatalln(err)
// 		fmt.Println(err)
// 	}

// 	resp, err := client.Do(req)

// 	if err != nil {
// 		log.Fatalln(err)
// 		fmt.Println(err)
// 	}
// 	body, _ := ioutil.ReadAll(resp.Body)

// 	str := string(body)

// 	split1 := strings.Split(str, ":")
// 	split2 := split1[15]
// 	split3 := split2[0:1]

// 	//fmt.Println(split3)
// 	return split3, nil
// }
