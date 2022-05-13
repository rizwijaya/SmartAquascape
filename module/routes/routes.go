package routes

import (
	"TamaskaPJU/app/auth"
	"TamaskaPJU/app/middlewares"
	"TamaskaPJU/module/handler"
	"TamaskaPJU/module/utilities/device"
	"TamaskaPJU/module/utilities/user"
	"TamaskaPJU/module/view"

	"github.com/gin-contrib/cors"
	"github.com/gin-contrib/multitemplate"
	"github.com/gin-contrib/sessions"
	"github.com/gin-contrib/sessions/cookie"
	"github.com/gin-gonic/gin"
	"gorm.io/gorm"
)

func Init(db *gorm.DB) *gin.Engine {
	// Load Repository
	userRepository := user.NewRepository(db)
	deviceRepository := device.NewRepository(db)
	//Load Service
	userService := user.NewService(userRepository)
	deviceService := device.NewService(deviceRepository)
	//Load Handler
	userHandler := handler.NewUserHandler(userService)
	//deviceHandler := handler.NewDeviceHandler(deviceService)
	//Load View
	deviceView := view.NewDeviceView(deviceService)
	userView := view.NewUserView(userService)

	router := gin.Default()
	router.Use(cors.Default())

	cookieStore := cookie.NewStore([]byte(auth.SECRET_KEY))
	router.Use(sessions.Sessions("tamaskapju", cookieStore))

	router.HTMLRender = ManualRender("./public/template/")

	// Routing Website Service
	router.GET("/device", deviceView.Index)
	router.GET("/device/edit/:id", deviceView.Edit)
	router.GET("/daftardevice", middlewares.AllAkses(), deviceView.DaftarDevice)
	router.GET("/login", userView.Login)
	router.POST("/login", userHandler.Login)
	router.GET("/logout", userHandler.Logout)
	router.GET("/dashboard", middlewares.AllAkses(), userView.Dashboard)
	router.GET("/deletedevice/:id", deviceView.DeleteDevice)
	//router.GET("/editdevice/:id", deviceView.EditDevice)
	router.GET("/controldevice", middlewares.AllAkses(), deviceView.ControlDevice)
	router.GET("/controllingdevice", middlewares.AllAkses(), deviceView.ControllingDevice)
	router.GET("/newdevice", middlewares.AllAkses(), deviceView.NewDevice)
	//router.POST("/newdevice", middlewares.AllAkses(), deviceHandler.NewDevice)
	//Routing API Service
	api := router.Group("/api/v1")
	api.POST("/users", userHandler.RegisterUser)

	return router
}

func ManualRender(tmpDir string) multitemplate.Renderer {
	r := multitemplate.NewRenderer()
	r.AddFromFiles("login", tmpDir+"home/home_login.html", tmpDir+"layouts/header.html", tmpDir+"layouts/footer.html")
	r.AddFromFiles("dashboard", tmpDir+"home/home_dashboard.html", tmpDir+"layouts/header.html", tmpDir+"layouts/menu.html", tmpDir+"layouts/navbar.html", tmpDir+"layouts/footer.html")
	r.AddFromFiles("daftardevice", tmpDir+"device/device_daftar.html", tmpDir+"layouts/header.html", tmpDir+"layouts/menu.html", tmpDir+"layouts/navbar.html", tmpDir+"layouts/footer.html")
	r.AddFromFiles("controldevice", tmpDir+"device/device_control.html", tmpDir+"layouts/header.html", tmpDir+"layouts/menu.html", tmpDir+"layouts/navbar.html", tmpDir+"layouts/footer.html")
	r.AddFromFiles("newdevice", tmpDir+"device/device_new.html", tmpDir+"layouts/header.html", tmpDir+"layouts/menu.html", tmpDir+"layouts/navbar.html", tmpDir+"layouts/footer.html")
	return r
}
