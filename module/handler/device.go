package handler

import (
	"SmartAquascape/app/helper"
	"SmartAquascape/module/utilities/device"
	"net/http"

	"github.com/gin-gonic/gin"
)

type DeviceHandler interface {
	GetAllTemperature(c *gin.Context)
	GetAllTurbidity(c *gin.Context)
	GetAllWaterLevel(c *gin.Context)
	GetOneTemperature(c *gin.Context)
	GetOneTurbidity(c *gin.Context)
	GetOneWaterLevel(c *gin.Context)
}

type deviceHandler struct {
	deviceService device.Service
}

func NewDeviceHandler(deviceService device.Service) *deviceHandler {
	return &deviceHandler{deviceService}
}

func (h *deviceHandler) GetAllTemperature(c *gin.Context) {

	//userId := c.Param("id_user")

	result, err := h.deviceService.GetAllTemperatures()

	if err != nil {
		response := helper.APIRespon("Get All Temperature Failed", http.StatusBadRequest, "error", nil)
		c.JSON(http.StatusBadRequest, response)
		return
	}

	c.JSON(http.StatusOK, gin.H{"data": result})
}

func (h *deviceHandler) GetOneTemperature(c *gin.Context) {

	temperature_id := c.Param("temperature_id")

	result, err := h.deviceService.GetOneTemperatureByID(temperature_id )

	if err != nil {
		response := helper.APIRespon("Get All Temperature Failed", http.StatusBadRequest, "error", nil)
		c.JSON(http.StatusBadRequest, response)
		return
	}

	c.JSON(http.StatusOK, gin.H{"data": result})
}

func (h *deviceHandler) GetAllWaterLevel(c *gin.Context) {

	//userId := c.Param("id_user")

	result, err := h.deviceService.GetAllWaterLevel()

	if err != nil {
		response := helper.APIRespon("Get All Water Level Failed", http.StatusBadRequest, "error", nil)
		c.JSON(http.StatusBadRequest, response)
		return
	}

	c.JSON(http.StatusOK, gin.H{"data": result})
}

func (h *deviceHandler) GetOneWaterLevel(c *gin.Context) {

	waterlevel_id := c.Param("waterlevel_id")

	result, err := h.deviceService.GetOneWaterLevelByID(waterlevel_id)

	if err != nil {
		response := helper.APIRespon("Get One Water Level Failed", http.StatusBadRequest, "error", nil)
		c.JSON(http.StatusBadRequest, response)
		return
	}

	c.JSON(http.StatusOK, gin.H{"data": result})
}

func (h *deviceHandler) GetAllTurbidity(c *gin.Context) {

	//userId := c.Param("id_user")

	result, err := h.deviceService.GetAllTemperatures()

	if err != nil {
		response := helper.APIRespon("Get All Turbidity Failed", http.StatusBadRequest, "error", nil)
		c.JSON(http.StatusBadRequest, response)
		return
	}

	c.JSON(http.StatusOK, gin.H{"data": result})
}

func (h *deviceHandler) GetOneTurbidity(c *gin.Context) {

	turbidity_id := c.Param("turbidity_id")

	result, err := h.deviceService.GetOneTurbidityByID(turbidity_id)

	if err != nil {
		response := helper.APIRespon("Get One Water Level Failed", http.StatusBadRequest, "error", nil)
		c.JSON(http.StatusBadRequest, response)
		return
	}

	c.JSON(http.StatusOK, gin.H{"data": result})
}