package main

import
(
	"fmt"
	"runtime"
)

var (
	g_cam_server *Camera_Server
	g_client_server *Client_Server	
)

type Main_Server struct {
}

func NewMainServer() *Main_Server {
	return &Main_Server{ }
}

func (main_s *Main_Server) RunServer() {
	fmt.Println("[Main_Server] Starting Main server... ")
    //Initiate different servers
    g_cam_server = NewCamServer(CAMSERVER_PORT)
    g_client_server = NewClientServer(CLIENTSERVER_PORT)
    
	//Start multiple servers in seperate threads (GoRoutines)
	go g_cam_server.RunServer() //Manages camera in-/output
   	go g_client_server.RunServer() //Manages clients (GUI) in-/output
   	
   	fmt.Println("[Main_Server] Main server running")
   	
	for {
    	//Gosched yields the processor, allowing other goroutines to run
     	runtime.Gosched()
    }
}
