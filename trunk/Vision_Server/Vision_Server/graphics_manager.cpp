#include "graphics_manager.h"

using namespace std;
using namespace cv;
using namespace boost;

Graphics_Manager::Graphics_Manager(void)
{
	boost::thread t = boost::thread(&Graphics_Manager::startGraphicsManager,this);
}

void Graphics_Manager::startGraphicsManager(void)
{
	/*
	cv::Mat testImage = cv::imread("test.jpg", CV_LOAD_IMAGE_COLOR);
	if(! testImage.data )                              // Check for invalid input
    {
        printf("Could not open or find the image\n");
        return;
    }	
	*/
	vector<int> params;
	params.push_back(CV_IMWRITE_JPEG_QUALITY);
	params.push_back(10);

	std::vector<uchar> jpegImageBuffer;
	
	cv::Mat frame;
	cv::VideoCapture cap;

	cap.open(0);

	while (!cap.isOpened())
	{
		printf("[Graphics Manager] Can't start videocapture!!! Let's retry! \n");
		cap.open(0);
		Sleep(1000);
	}

	cv::namedWindow( "Display window", CV_WINDOW_AUTOSIZE );// Create a window for display.

	for(;;)
	{
		//Capture
		cap >> frame;
	
		//Show
		cv::imshow("Display window", frame);

		//Encode to .jpg
		cv::imencode(".jpg", frame, jpegImageBuffer, params);
		printf("jpegImageBuffer Size: %d\n",jpegImageBuffer.size());
		if(cv::waitKey(30) >= 0) break;
	}
}