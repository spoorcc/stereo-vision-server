package main

import
(
//	"fmt"
	"net"
)

type Client struct {
	id int
	socket   net.Conn
}
