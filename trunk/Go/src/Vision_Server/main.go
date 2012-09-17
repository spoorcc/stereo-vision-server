package main

import (
	"fmt"
	"runtime"
	"flag"
	"goconf"
)

var (
	g_main_server *Main_Server
	g_config *conf.ConfigFile
)

func main() {
	//Starting the server
    fmt.Println("----------------------------------")
    fmt.Println("--  Starting Vision Server v0.1 --")
    fmt.Println("----------------------------------")
	
	// Flags
	configFile := flag.String("config", "server.conf", "Name of the config file to load")
	flag.Parse()
	
	//Use the maximum number of CPUs available
	runtime.GOMAXPROCS(runtime.NumCPU())
	fmt.Printf("[Main] Using %d CPU cores... [Succeeded]\n", runtime.NumCPU())
		
	// Load config file
	fmt.Printf("[Main] Loading config file... ")
	if initConfig(configFile) == false {
		fmt.Printf("[FAILED]\n")
		return
	}
	fmt.Printf("[Succeeded]\n")
    
    //Create and run main server
    CamPort, _ := g_config.GetInt("default", "CamPort")
    ClientPort, _ := g_config.GetInt("default", "ClientPort")
    g_main_server := NewMainServer(CamPort, ClientPort)
    g_main_server.RunServer()
}

func initConfig(configFile *string) bool {
	c, err := conf.ReadConfigFile("data/" + *configFile)
	if err != nil {
		fmt.Printf("Could not load config file: %v\n\r", err)
		return false
	}

	g_config = c

	return true
}