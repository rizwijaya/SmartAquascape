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
	GetOneTurbidityByID(ID Turbidity) (Turbidity, error)
	GetOneWaterLevelByID(ID WaterLevel) (WaterLevel, error)
	GetOneTemperatureByID(ID Temperature) (Temperature, error)
	GetAllTurbidity() ([]Turbidity, error)
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

func (s *service) GetOneTurbidityByID(ID int) (Turbidity, error) {
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

func (s *service) GetOneWaterLevelByID(ID int) (WaterLevel, error) {
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

func (s *service) GetOneTemperatureByID(ID int) (Temperature, error) {
	temperature, err := s.repository.FindTemperatureByID(ID)
	if err != nil {
		return temperature, err
	}

	var check Temperature
	if check.Data < `24`|| check.Data > `25` {
		fmt.Println("Suhu air tidak normal")
	} else if check.Data >= `24` || check.Data <= `25` {
		fmt.Println("Suhu air normal")
	}

	return temperature, nil
}


