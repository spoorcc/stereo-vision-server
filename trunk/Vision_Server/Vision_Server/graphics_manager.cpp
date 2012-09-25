#include "includes.h"

using namespace std;

void startGraphicsManager(void)
{
	CvCapture* capture;
	IplImage* img = 0;

	cvNamedWindow( "Example1", CV_WINDOW_AUTOSIZE );
	while(true)
	{
        capture = cvCreateCameraCapture(0);
        img = cvQueryFrame(capture);
        cvShowImage("Example1", img);
		cvWaitKey(50);
		cvReleaseImage( &img );
	}
	cvDestroyWindow("Example1");
}