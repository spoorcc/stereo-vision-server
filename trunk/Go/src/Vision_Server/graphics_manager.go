package main

import
(
	"fmt"
//	"net"
	"opencv"
)

type Graphics_Manager struct {
	
}

func NewGraphicsManager() *Graphics_Manager {
	return &Graphics_Manager{ }
}

func (graphic_s *Graphics_Manager) RunManager() {
	fmt.Println("[Graphics_Manager] Starting open CV debug mode... ")	
	fmt.Println("[Graphics_Manager] Start 50 frames camera test!")

	capture := opencv.NewCameraCapture(0)	
	win := opencv.NewWindow("Go-OpenCV")
	i := 0
	for  {
		i++
		img := capture.QueryFrame()
         
        win.ShowImage(img)
        fmt.Printf("[Graphics_Manager] Frame %d opened\n", i)
        //opencv.WaitKey(0)
        opencv.WaitKey(50)
	}
	opencv.WaitKey(0)
}