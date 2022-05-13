package middlewares

import (
	"fmt"
	"net/http"

	"github.com/gin-contrib/sessions"
	"github.com/gin-gonic/gin"
)

func AllAkses() gin.HandlerFunc {
	return func(c *gin.Context) {
		session := sessions.Default(c)

		userIDSession := session.Get("userID")

		if userIDSession == nil {
			c.Redirect(http.StatusFound, "/login")
			return
		}
	}
}

func AuthPrivellege(page string) gin.HandlerFunc {
	return func(c *gin.Context) {
		session := sessions.Default(c)
		userIDSession := session.Get("userID")
		userRole := fmt.Sprintf("%v", session.Get("Role"))

		if userIDSession == nil {
			c.Redirect(http.StatusFound, "/login")
			return
		}
		//Hak Akses Daftar admin untuk semua Role
		if page == "admin" && (userRole != "1") {
			c.Redirect(http.StatusFound, "/login")
			return
		} else if page == "deleteDevice" && userRole != "1" || userRole != "3" {
			c.Redirect(http.StatusFound, "/login")
			return
		}
		//1 Untuk akses admin
		//2 Untuk akses
		//5 untuk akses admin,user,tenant,pengelola kawasan

		//Re modeling DB untuk use case single dashboard for many kawasan.
	}
}
