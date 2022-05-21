package view

import (
	"SmartAquascape/module/utilities/device"
	"net/http"

	"github.com/gin-contrib/sessions"
	"github.com/gin-gonic/gin"
)

type deviceView struct {
	deviceService device.Service
}

func NewDeviceView(deviceService device.Service) *deviceView {
	return &deviceView{deviceService}
}

func (h *deviceView) Index(c *gin.Context) {
	device, err := h.deviceService.GetAllDevice()
	if err != nil {
		c.HTML(http.StatusInternalServerError, "error.html", nil)
		return
	}

	c.HTML(http.StatusOK, "device_index.html", gin.H{"device": device})
}

func (h *deviceView) ControlDevice(c *gin.Context) {
	session := sessions.Default(c)
	userID := session.Get("userID")
	if userID == nil {
		c.Redirect(http.StatusFound, "/login")
		return
	}

	if userID == 1 {
		device, err := h.deviceService.GetAllDevice()
		if err != nil {
			c.HTML(http.StatusInternalServerError, "error.html", nil)
			return
		}
		c.HTML(http.StatusOK, "controldevice", gin.H{
			"UserID":     session.Get("userID"),
			"UserName":   session.Get("userName"),
			"Role":       session.Get("Role"),
			"title":      "Kendali Jarak Jauh",
			"page":       "controldevice",
			"notifikasi": session.Flashes(),
			"device":     device,
		})
	}
}

func (h *deviceView) ControllingDevice(c *gin.Context) {
	// sessions := sessions.Default(c)

	// idParam := c.Param("id")
	// id, _ := strconv.Atoi(idParam)

	h.ControlDevice(c)
}

func (h *deviceView) MonitoringDevice(c *gin.Context) {
	session := sessions.Default(c)
	userID := session.Get("userID")

	if userID == nil {
		c.Redirect(http.StatusFound, "/login")
		return
	}

	if userID == 1 {
		temperature, err1 := h.deviceService.GetAllTemperatures()
		turbidity, err2 := h.deviceService.GetAllTurbidity()
		water_level, err3 := h.deviceService.GetAllWaterLevel()
		if err1 != nil || err2 != nil || err3 != nil {
			c.HTML(http.StatusInternalServerError, "error.html", nil)
			return
		}

		c.HTML(http.StatusOK, "dashboard", gin.H{
			"UserID":      session.Get("userID"),
			"UserName":    session.Get("userName"),
			"Role":        session.Get("Role"),
			"title":       "Monitoring Jarak Jauh",
			"page":        "dashboard",
			"temperature": temperature,
			"turbidity":   turbidity,
			"water_level": water_level,
		})
	}
}
