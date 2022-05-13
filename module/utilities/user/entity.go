package user

import "time"

type User struct {
	Id_users     int
	Id_Kawasan   int
	Nama         string
	Email        string
	Password     string
	Avatar       string
	Id_role      string
	Date_updated time.Time
	Date_created time.Time
}
