package main

import
(
	"fmt"
	"runtime"
)

var (
	g_cam_server *Camera_Server
	g_client_server *Client_Server
	g_graphics_manager *Graphics_Manager
		
)

type Main_Server struct {
	CamPort int
	ClientPort int
}

func NewMainServer(p_cam int, p_client int) *Main_Server {
	return &Main_Server{ CamPort: p_cam, ClientPort: p_client }
}

func (main_s *Main_Server) RunServer() {
	fmt.Println("[Main_Server] Starting Main server... [Succeeded]")
    //Initiate different servers
    g_cam_server = NewCamServer(main_s.CamPort)
    g_client_server = NewClientServer(main_s.ClientPort)
    g_graphics_manager = NewGraphicsManager()
	//Start multiple servers in seperate threads (GoRoutines)
	go g_cam_server.RunServer() //Manages camera in-/output
   	go g_client_server.RunServer() //Manages clients (GUI) in-/output
   	go g_graphics_manager.RunManager()
   	
	for {
    	//Gosched yields the processor, allowing other goroutines to run
     	runtime.Gosched()
    }
}
