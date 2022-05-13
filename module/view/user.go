package view

import (
	"TamaskaPJU/module/utilities/user"
	"net/http"

	"github.com/gin-contrib/sessions"
	"github.com/gin-gonic/gin"
)

type userView struct {
	userService user.Service
}

func NewUserView(userService user.Service) *userView {
	return &userView{userService}
}

// func (h *userView) Index(c *gin.Context) {
// 	//device, err := h.deviceService.GetAllDevice()
// 	if err != nil {
// 		c.HTML(http.StatusInternalServerError, "error.html", nil)
// 		return
// 	}

// 	c.HTML(http.StatusOK, "device_index.html", gin.H{"device": device})
// }

func (h *userView) Login(c *gin.Context) {
	c.HTML(http.StatusOK, "login", gin.H{
		"title": "Tamaska Public Lighting Login",
		"data":  1})
}

func (h *userView) Dashboard(c *gin.Context) {
	session := sessions.Default(c)

	c.HTML(http.StatusOK, "dashboard", gin.H{
		"UserID":   session.Get("userID"),
		"UserName": session.Get("userName"),
		"page":     "dashboard",
		"Role":     session.Get("Role"),
		"title":    "Tamaska Public Lighting"})
}
