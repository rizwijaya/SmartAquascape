package device

type Deliver struct {
	DeliveryTime string `json:"deliverytime" binding:"required"`
}
