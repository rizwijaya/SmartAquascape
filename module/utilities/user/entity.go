package user

import "time"

type User struct {
	Id_users     int
	Nama         string
	Email        string
	Password     string
	Avatar       string
	Date_updated time.Time
	Date_created time.Time
}
