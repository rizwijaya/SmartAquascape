package device

import "gorm.io/gorm"

type Repository interface {
	GetAllDevice() ([]Device, error)
	FindByID(ID int) (Device, error)
	GetAllTemperatures() ([]Temperature, error)
	GetAllWaterLevel() ([]WaterLevel, error)
	FindTurbidityByID(ID int) (Turbidity, error)
	GetAllTurbidity() ([]Turbidity, error)
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

func (r * repository) FindTurbidityByID(ID int) (Turbidity, error){
	var turbidity Turbidity
	err := r.db.Where("id").Find(&turbidity).Error
	if err != nil {
		return turbidity, err
	}
	return turbidity, nil
}