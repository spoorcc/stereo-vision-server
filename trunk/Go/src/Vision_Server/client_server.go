package main

import
(
	"fmt"
//	"net"
)

type Client_Server struct {
	port int
	clients map[int]*Client
}

func NewClientServer(_port int) *Client_Server {
	return &Client_Server{port: _port, clients: make(map[int]*Client) }
}

func (client_s *Client_Server) RunServer() {
	fmt.Println("Starting Client server... ")	
	//TODO entire client handling
}
