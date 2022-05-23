package routes

import (
	"SmartAquascape/app/auth"
	"SmartAquascape/app/middlewares"
	"SmartAquascape/module/handler"
	"SmartAquascape/module/utilities/device"
	"SmartAquascape/module/utilities/user"
	"SmartAquascape/module/view"

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
	deviceHandler := handler.NewDeviceHandler(deviceService)
	//Load View
	deviceView := view.NewDeviceView(deviceService)
	userView := view.NewUserView(userService)

	router := gin.Default()
	router.Use(cors.Default())

	cookieStore := cookie.NewStore([]byte(auth.SECRET_KEY))
	router.Use(sessions.Sessions("tamaskapju", cookieStore))

	router.HTMLRender = ManualRender("./public/template/")

	// Khusus Website
	router.GET("/login", userView.Login)
	router.GET("/device", deviceView.Index)
	// router.GET("/controldevice", middlewares.AllAkses(), deviceView.ControlDevice)
	// router.GET("/controllingdevice", middlewares.AllAkses(), deviceView.ControllingDevice)
	//router.GET("/dashboard", deviceView.MonitoringDevice)
	router.GET("/dashboard", middlewares.AllAkses(), deviceView.Dashboard)

	// Routing API Service
	api := router.Group("/api/v1")

	// User API
	router.POST("/login", userHandler.Login)
	router.GET("/manualfeeder", deviceHandler.ManualFeeder)
	router.GET("/statusfeeder/:sts", deviceHandler.StatusFeeder)
	router.GET("/deliveryTime", deviceHandler.DeliveryTime)
	router.GET("/logout", userHandler.Logout)
	api.POST("/users", userHandler.RegisterUser)
	// api.POST("/login", userHandler.Login)
	// api.POST("/logout", userHandler.Logout)

	// Device API
	api.GET("/getoneturbidity", deviceHandler.GetOneTurbidity)
	api.GET("/getonetemperature", deviceHandler.GetOneTemperature)
	api.GET("/getonewaterlevel", deviceHandler.GetOneWaterLevel)
	api.GET("/getallturbidity", deviceHandler.GetAllTurbidity)
	api.GET("/getalltemperature", deviceHandler.GetAllTemperature)
	api.GET("/getallwaterlevel", deviceHandler.GetAllWaterLevel)
	api.GET("/monitoringdevice", deviceHandler.MonitoringDevice)
	return router
}

func ManualRender(tmpDir string) multitemplate.Renderer {
	r := multitemplate.NewRenderer()
	r.AddFromFiles("login", tmpDir+"home/home_login.html", tmpDir+"layouts/header.html", tmpDir+"layouts/footer.html")
	r.AddFromFiles("dashboard", tmpDir+"home/home_dashboard.html", tmpDir+"layouts/header.html", tmpDir+"layouts/navbar.html", tmpDir+"layouts/footer.html")
	r.AddFromFiles("controldevice", tmpDir+"device/device_control.html", tmpDir+"layouts/header.html", tmpDir+"layouts/menu.html", tmpDir+"layouts/navbar.html", tmpDir+"layouts/footer.html")
	return r
}
