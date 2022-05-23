package device

type Deliver struct {
	DeliveryTime string `json:"deliverytime" binding:"required"`
}

type AutoF struct {
	WaktuPertama string `json:"waktupertama" binding:"required"`
	WaktuKedua   string `json:"waktukedua" binding:"required"`
	WaktuKetiga  string `json:"waktuketiga" binding:"required"`
}
