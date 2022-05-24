package view

import (
	"SmartAquascape/module/utilities/device"
	"crypto/tls"
	"fmt"
	"io/ioutil"
	"log"
	"net/http"
	"strings"

	"github.com/gin-contrib/sessions"
	"github.com/gin-gonic/gin"
)

type deviceView struct {
	deviceService device.Service
}

func NewDeviceView(deviceService device.Service) *deviceView {
	return &deviceView{deviceService}
}

func (h *deviceView) Dashboard(c *gin.Context) {
	session := sessions.Default(c)

	tr := &http.Transport{
		TLSClientConfig: &tls.Config{
			MaxVersion: tls.VersionTLS12,
		},
	}
	client := &http.Client{Transport: tr}

	req, err := http.NewRequest("GET", "https://platform.antares.id:8443/~/antares-cse/antares-id/smartAquascape/Aquascape-Feeder/la", nil)
	req.Header.Add("X-M2M-Origin", "9fb52249c593c66d:b719370dce7d93b9")
	req.Header.Add("Content-Type", "application/json;ty=4")
	req.Header.Add("Accept", "application/json")

	if err != nil {
		log.Fatalln(err)
		fmt.Println(err)
	}

	resp, err := client.Do(req)

	if err != nil {
		log.Fatalln(err)
		fmt.Println(err)
	}
	body, _ := ioutil.ReadAll(resp.Body)

	str := string(body)

	split1 := strings.Split(str, ":")
	split2 := split1[15]
	split3 := split2[0:1]

	//fmt.Println(split3)

	data, err := h.deviceService.MonitoringDevice()
	data2, err2 := h.deviceService.MonitoringTable()
	data3, err3 := h.deviceService.GetLatest()
	if err != nil || err2 != nil || err3 != nil {
		c.HTML(http.StatusInternalServerError, "error.html", nil)
		return
	}

	c.HTML(http.StatusOK, "dashboard", gin.H{
		"UserID":          session.Get("userID"),
		"UserName":        session.Get("userName"),
		"page":            "dashboard",
		"title":           "SmartAquascape",
		"monitoring":      data,
		"monitoringtable": data2,
		"grafikdata":      data3,
		"status":          split3,
	})
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
