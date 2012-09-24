// Vision_Server.cpp : Defines the entry point for the console application.
//

/*#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}*/

#include "stdafx.h"

#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

int _tmain(int argc, _TCHAR* argv[])
{
        IplImage *img = cvLoadImage("funny-pictures-cat-goes-pew.jpg");
        cvNamedWindow("Image:",1);
        cvShowImage("Image:",img);

        cvWaitKey();
        cvDestroyWindow("Image:");
        cvReleaseImage(&img);

        return 0;
}