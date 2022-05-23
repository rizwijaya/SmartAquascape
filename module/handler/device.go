package handler

import (
	"SmartAquascape/app/helper"
	"SmartAquascape/module/utilities/device"
	"bytes"
	"io/ioutil"
	"log"
	"net/http"
	"time"

	"github.com/gin-gonic/gin"
)

type DeviceHandler interface {
	GetAllTemperature(c *gin.Context)
	GetAllTurbidity(c *gin.Context)
	GetAllWaterLevel(c *gin.Context)
	GetOneTemperature(c *gin.Context)
	GetOneTurbidity(c *gin.Context)
	GetOneWaterLevel(c *gin.Context)
	MonitoringDevice(c *gin.Context)
	ManualFeeder(c *gin.Context)
	StatusFeeder(c *gin.Context)
	DeliveryTime(c *gin.Context)
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

	result, err := h.deviceService.GetOneTemperatureByID(temperature_id)

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

func (h *deviceHandler) MonitoringDevice(c *gin.Context) {

	result, err := h.deviceService.MonitoringDevice()

	if err != nil {
		response := helper.APIRespon("Monitoring Device Failed", http.StatusBadRequest, "error", nil)
		c.JSON(http.StatusBadRequest, response)
		return
	}

	c.JSON(http.StatusOK, gin.H{"data": result})
}

func (h *deviceHandler) ManualFeeder(c *gin.Context) {
	data := "\r\n{\r\n  \"m2m:cin\": {\r\n    \"con\": \r\n      \"{\r\n      \t \\\"header\\\":9,\r\n         \\\"statusFeeder\\\":1\r\n      }\"\r\n    }\r\n}"
	//fmt.Println(data)
	timeout := time.Duration(5 * time.Second)
	client := http.Client{
		Timeout: timeout,
	}
	req, err := http.NewRequest("POST", "https://platform.antares.id:8443/~/antares-cse/antares-id/smartAquascape/Manual-Feeder", bytes.NewBuffer([]byte(data)))
	req.Header.Set("X-M2M-Origin", "9fb52249c593c66d:b719370dce7d93b9")
	req.Header.Set("Content-Type", "application/json;ty=4")
	req.Header.Set("Accept", "application/json")

	if err != nil {
		log.Fatalln(err)
	}

	resp, err := client.Do(req)
	if err != nil {
		log.Fatalln(err)
	}

	defer resp.Body.Close()

	body, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		log.Fatalln(err)
	}

	log.Println(string(body))
	c.Redirect(http.StatusFound, "/dashboard")
}

func (h *deviceHandler) StatusFeeder(c *gin.Context) {
	sts := c.Param("sts")

	data := "\r\n{\r\n  \"m2m:cin\": {\r\n    \"con\": \r\n      \"{\r\n      \t \\\"header\\\":,\r\n         \\\"statusControl\\\":" + sts + "\r\n      }\"\r\n    }\r\n}"
	//fmt.Println(data)
	timeout := time.Duration(5 * time.Second)
	client := http.Client{
		Timeout: timeout,
	}
	req, err := http.NewRequest("POST", "https://platform.antares.id:8443/~/antares-cse/antares-id/smartAquascape/Aquascape-Feeder", bytes.NewBuffer([]byte(data)))
	req.Header.Set("X-M2M-Origin", "9fb52249c593c66d:b719370dce7d93b9")
	req.Header.Set("Content-Type", "application/json;ty=4")
	req.Header.Set("Accept", "application/json")

	if err != nil {
		log.Fatalln(err)
	}

	resp, err := client.Do(req)
	if err != nil {
		log.Fatalln(err)
	}

	defer resp.Body.Close()

	body, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		log.Fatalln(err)
	}

	log.Println(string(body))
	c.Redirect(http.StatusFound, "/dashboard")
}

func (h *deviceHandler) DeliveryTime(c *gin.Context) {
	var input device.Deliver

	err := c.ShouldBind(&input)
	if err != nil {
		c.Redirect(http.StatusFound, "/dashboard")
		return
	}

	data := "\r\n{\r\n  \"m2m:cin\": {\r\n    \"con\": \r\n      \"{\r\n      \t \\\"header\\\":,\r\n         \\\"statusControl\\\":1\r\n      }\"\r\n    }\r\n}"
	//fmt.Println(data)
	timeout := time.Duration(5 * time.Second)
	client := http.Client{
		Timeout: timeout,
	}
	req, err := http.NewRequest("POST", "https://platform.antares.id:8443/~/antares-cse/antares-id/smartAquascape/Aquascape-Feeder", bytes.NewBuffer([]byte(data)))
	req.Header.Set("X-M2M-Origin", "9fb52249c593c66d:b719370dce7d93b9")
	req.Header.Set("Content-Type", "application/json;ty=4")
	req.Header.Set("Accept", "application/json")

	if err != nil {
		log.Fatalln(err)
	}

	resp, err := client.Do(req)
	if err != nil {
		log.Fatalln(err)
	}

	defer resp.Body.Close()

	body, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		log.Fatalln(err)
	}

	log.Println(string(body))
	c.Redirect(http.StatusFound, "/dashboard")
}
