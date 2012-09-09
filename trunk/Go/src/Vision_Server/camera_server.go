package main

import
(
	"fmt"
//	"net"
)

type Camera_Server struct {
	port int	
	cams map[int]*Camera
}

func NewCamServer(_port int) *Camera_Server {
	return &Camera_Server{port: _port, cams: make(map[int]*Camera) }
}

func (cam_s *Camera_Server) RunServer() {
    fmt.Println("Starting Camera server... ")	
	//TODO entire camera handling
}
