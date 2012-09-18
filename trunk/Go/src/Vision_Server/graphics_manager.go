package main

import
(
	"fmt"
//	"net"
	"opencv"
	"os"
)

type Graphics_Manager struct {
	
}

func NewGraphicsManager() *Graphics_Manager {
	return &Graphics_Manager{ }
}

func (graphic_s *Graphics_Manager) RunManager() {
	fmt.Println("[Graphics_Manager] Starting open CV debug mode... ")	
	//TODO entire client handling
		filename := "images/lena.jpg"
	if len(os.Args) == 2 {
		filename = os.Args[1]
	}

	image := opencv.LoadImage(filename)
	if image == nil {
		panic("LoadImage fail")
	}
	defer image.Release()

	win := opencv.NewWindow("Go-OpenCV")
	defer win.Destroy()

	win.SetMouseCallback(func(event, x, y, flags int) {
		fmt.Printf("event = %d, x = %d, y = %d, flags = %d\n",
			event, x, y, flags,
		)
	})
	win.CreateTrackbar("Thresh", 1, 100, func(pos int) {
		fmt.Printf("pos = %d\n", pos)
	})

	win.ShowImage(image)

	opencv.WaitKey(0)
}




