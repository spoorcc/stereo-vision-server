package main

import
(
	"fmt"
	"net"
	"os"
)

type Camera_Server struct {
	port int	
	cams map[int]*Camera
}

func NewCamServer(_port int) *Camera_Server {
	return &Camera_Server{port: _port, cams: make(map[int]*Camera) }
}

func (cam_s *Camera_Server) RunServer() {
    fmt.Println("[Camera_Server] Starting Camera server... ")	
	//TODO entire camera handling
	
	//Resolve UDP address, it's only looking to the port
	service := fmt.Sprintf(":%d", cam_s.port)
	udpAddr, err := net.ResolveUDPAddr("up4", service)
	checkError(err)

	//Listen UDP on the port
	conn, err := net.ListenUDP("udp", udpAddr)
	checkError(err)
	
	fmt.Printf("[Camera_Server] Camera server running... Listening to %s [%s]\n", udpAddr.String(), udpAddr.Network())
	
	// close connection on exit
	defer conn.Close()
	
	var buf [512]byte
	for {
		// read upto 512 bytes
		n, err := conn.Read(buf[0:])
		checkError(err)
		
		fmt.Printf("Bytes: %d, Message: %s", n, string(buf[0:n]))	
	}
}

func checkError(err error) {
	if err != nil {
		fmt.Fprintf(os.Stderr, "[Fatal Camera_Server error] ", err.Error())
		os.Exit(1)
	}
}