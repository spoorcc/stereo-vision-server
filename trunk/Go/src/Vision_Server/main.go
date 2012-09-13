package main

import (
	"fmt"
	"runtime"
)

const (
	//TODO Ports in config (.conf) file
	CAMSERVER_PORT = 59192
	CLIENTSERVER_PORT = 59193
)

var (
	g_main_server *Main_Server
)

func main() {
	//Starting the server
    fmt.Println("----------------------------------")
    fmt.Println("--  Starting Vision Server v0.1 --")
    fmt.Println("----------------------------------")

	//Use the maximum number of CPUs available
	runtime.GOMAXPROCS(runtime.NumCPU())
	fmt.Printf("Using %d CPU cores\n", runtime.NumCPU())
    
    //Create and run main server
    g_main_server = NewMainServer()
    g_main_server.RunServer()
}