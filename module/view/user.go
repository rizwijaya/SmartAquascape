package view

import (
	"SmartAquascape/module/utilities/user"
	"encoding/json"
	"io/ioutil"
	"net/http"

	"github.com/gin-gonic/gin"
)

type userView struct {
	userService user.Service
}

func NewUserView(userService user.Service) *userView {
	return &userView{userService}
}

func (h *userView) Login(c *gin.Context) {
	c.HTML(http.StatusOK, "login", gin.H{
		"title": "SmartAquascape Login",
		"data":  1})
}

func (h *userView) Register(c *gin.Context) {
	body, _ := ioutil.ReadAll(c.Request.Body)

	var data user.RegisterUserInput
	json.Unmarshal(body, &data)

	c.HTML(http.StatusOK, "register", gin.H{
		"title": "SmartAquascape Register",
		"nama":  ""})
}

// func (h *userView) Dashboard(c *gin.Context) {
// 	session := sessions.Default(c)

// 	data := h.userService.MonitoringDevice()

// 	c.HTML(http.StatusOK, "dashboard", gin.H{
// 		"UserID":   session.Get("userID"),
// 		"UserName": session.Get("userName"),
// 		"page":     "dashboard",
// 		"title":    "SmartAquascape"})
// }
