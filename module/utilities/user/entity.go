package user

import "time"

type User struct {
	UserID       int
	Nama         string
	Email        string
	Password     string
	Avatar       string
	Id_role      string
	Date_updated time.Time
	Date_created time.Time
}
