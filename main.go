package main

import (
	"SmartAquascape/app/config"
	"SmartAquascape/module/routes"
)

func main() {
	db := config.Init()
	router := routes.Init(db)

	//Load HTML Template
	router.Static("/assets", "./public/assets")
	router.Static("/images", "./public/images")

	router.Static("/css", "./public/assets/css")
	router.Static("/img", "./public/assets/img")
	router.Static("/js", "./public/assets/js")
	router.Static("/vendoring", "./public/assets/vendor")
	router.Static("/vendor/css", "./public/assets/vendor/css")
	router.Static("/vendor/fonts", "./public/assets/vendor/fonts")
	router.Static("/vendor/js", "./public/assets/vendor/js")
	router.Static("/vendor/libs", "./public/assets/vendor/libs")

	router.Run(":9001")
}
