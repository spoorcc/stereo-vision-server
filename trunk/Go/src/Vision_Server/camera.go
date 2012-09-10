package main

import
(
//	"fmt"
	"net"
)

type Camera struct {
	id int
	socket   net.Conn
}
