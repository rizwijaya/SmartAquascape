package device

import "gorm.io/gorm"

type Repository interface {
	GetAllDevice() ([]Device, error)
	FindByID(ID int) (Device, error)
	GetAllTemperatures() ([]Temperature, error)
	GetAllWaterLevel() ([]WaterLevel, error)
	FindTurbidityByID(ID string) (Turbidity, error)
	FindWaterLevelByID(ID string) (WaterLevel, error)
	FindTemperatureByID(ID string) (Temperature, error)
	GetAllTurbidity() ([]Turbidity, error)
	MonitoringDevice() ([]Monitoring, error)
}

type repository struct {
	db *gorm.DB
}

func NewRepository(db *gorm.DB) *repository {
	return &repository{db}
}

func (r *repository) GetAllDevice() ([]Device, error) {
	var device []Device

	err := r.db.Find(&device).Error
	if err != nil {
		return device, err
	}

	return device, nil
}

func (r *repository) FindByID(ID int) (Device, error) {
	var device Device

	err := r.db.Where("no_device = ?", ID).Find(&device).Error
	if err != nil {
		return device, err
	}

	return device, nil
}

func (r *repository) GetAllTemperatures() ([]Temperature, error) {
	var temp []Temperature
	err := r.db.Find(&temp).Error
	if err != nil {
		return temp, err
	}
	return temp, nil
}

func (r *repository) GetAllWaterLevel() ([]WaterLevel, error) {
	var waterLevel []WaterLevel
	err := r.db.Find(&waterLevel).Error
	if err != nil {
		return waterLevel, err
	}
	return waterLevel, nil
}

func (r *repository) GetAllTurbidity() ([]Turbidity, error) {
	var turbidity []Turbidity
	err := r.db.Find(&turbidity).Error
	if err != nil {
		return turbidity, err
	}
	return turbidity, nil
}

func (r *repository) FindTurbidityByID(ID string) (Turbidity, error) {
	var turbidity Turbidity
	err := r.db.Where("id").Find(&turbidity).Error
	if err != nil {
		return turbidity, err
	}
	return turbidity, nil
}

func (r *repository) FindWaterLevelByID(ID string) (WaterLevel, error) {
	var water_level WaterLevel
	err := r.db.Where("id").Find(&water_level).Error
	if err != nil {
		return water_level, err
	}
	return water_level, nil
}

func (r *repository) FindTemperatureByID(ID string) (Temperature, error) {
	var temperature Temperature
	err := r.db.Where("id").Find(&temperature).Error
	if err != nil {
		return temperature, err
	}
	return temperature, nil
}

func (r *repository) MonitoringDevice() ([]Monitoring, error) {
	var monitoring []Monitoring
	err := r.db.Table("monitoring").Find(&monitoring).Error
	if err != nil {
		return monitoring, err
	}
	return monitoring, nil
}
