package view

import (
	"SmartAquascape/module/utilities/device"
	"net/http"
	"strconv"

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

func (h *deviceView) Edit(c *gin.Context) {
	idParam := c.Param("id")
	id, _ := strconv.Atoi(idParam)

	device, err := h.deviceService.GetDeviceByID(id)
	if err != nil {
		c.HTML(http.StatusInternalServerError, "error.html", nil)
		return
	}

	c.HTML(http.StatusOK, "device_edit.html", gin.H{"device": device})
}

func (h *deviceView) DaftarDevice(c *gin.Context) {
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
		c.HTML(http.StatusOK, "daftardevice", gin.H{
			"UserID":     session.Get("userID"),
			"UserName":   session.Get("userName"),
			"Role":       session.Get("Role"),
			"title":      "Daftar Device Tamaska",
			"page":       "daftardevice",
			"notifikasi": session.Flashes(),
			"device":     device})
	} else {
		// kawasan := fmt.Sprintf("%v", session.Get("kawasan"))
		// device, err := h.deviceService.GetDeviceKawasan(kawasan) // Get device by id user
		// if err != nil {
		// 	c.HTML(http.StatusInternalServerError, "error.html", nil)
		// 	return
		// }
		c.HTML(http.StatusOK, "daftardevice", gin.H{
			"UserID":     session.Get("userID"),
			"UserName":   session.Get("userName"),
			"Role":       session.Get("Role"),
			"title":      "Daftar Device Tamaska",
			"page":       "daftardevice",
			"notifikasi": session.Flashes(),
			//"device":     device
		})
	}
}

// func (h *deviceView) DeleteDevice(c *gin.Context) {
// 	sessions := sessions.Default(c)

// 	idParam := c.Param("id")
// 	id, _ := strconv.Atoi(idParam)

// 	delete, err := h.deviceService.DeleteDevice(id)
// 	if err != nil {
// 		fmt.Println(err)
// 		c.HTML(http.StatusInternalServerError, "error.html", nil)
// 		return
// 	}
// 	if delete == 1 {
// 		sessions.AddFlash("sukseshapusdevice")
// 	} else {
// 		sessions.AddFlash("gagalhapusdevice")
// 	}
// 	//sessions.Save()
// 	//c.Redirect(http.StatusFound, "/daftardevice")
// 	h.DaftarDevice(c)
// }

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
			"device":     device})
	} else {
		//kawasan := fmt.Sprintf("%v", session.Get("kawasan"))
		// device, err := h.deviceService.GetDeviceKawasan(kawasan) // Get device by id user
		// if err != nil {
		// 	c.HTML(http.StatusInternalServerError, "error.html", nil)
		// 	return
		// }
		c.HTML(http.StatusOK, "controldevice", gin.H{
			"UserID":     session.Get("userID"),
			"UserName":   session.Get("userName"),
			"Role":       session.Get("Role"),
			"title":      "Kendali Jarak Jauh",
			"page":       "controldevice",
			"notifikasi": session.Flashes(),
			//"device":     device
		})
	}
}

func (h *deviceView) ControllingDevice(c *gin.Context) {
	// sessions := sessions.Default(c)

	// idParam := c.Param("id")
	// id, _ := strconv.Atoi(idParam)

	h.ControlDevice(c)
}
