#include "packetReceiver.h"

#define OFFSET_STARTADRES 4
	
uint8_t imageBuffer_cam1[FILL_UP_PIXEL_SIZE];
uint8_t imageBuffer_cam2[FILL_UP_PIXEL_SIZE];
uint8_t imageBuffer_cam3[FILL_UP_PIXEL_SIZE];
uint8_t imageBuffer_cam4[FILL_UP_PIXEL_SIZE];
uint8_t imageBuffer_cam5[FILL_UP_PIXEL_SIZE];
uint8_t imageBuffer_cam6[FILL_UP_PIXEL_SIZE];
uint8_t imageBuffer_cam7[FILL_UP_PIXEL_SIZE];
uint8_t imageBuffer_cam8[FILL_UP_PIXEL_SIZE];

void maikeImage(uint8_t bufferArray[FILL_UP_PIXEL_SIZE])
{
		IplImage* imgTest = cvCreateImage(cvSize(640, 480), IPL_DEPTH_8U, 3);
       
		for (int i = 0; i < 921600; i++)
        {
			imgTest->imageData[i] = bufferArray[i];
        }
        cvNamedWindow( "Example1", CV_WINDOW_AUTOSIZE );
        cvShowImage("Example1", imgTest);
        cvWaitKey(0);
        cvReleaseImage( &imgTest );
        cvDestroyWindow("Example1");
}

void cam_config(void){
}

void proces_config(void){
}

void callib_data(void){
}

void raw_rgb_data(boost::array<uint8_t,BUFFER_SIZE > bufferArray){
/*	
	uint8_t imageBuffer_cam_1 [921600];

	uint16_t startAdres = (uint16_t) bufferArray.at(1);
	uint16_t range = (uint16_t) bufferArray.at(2);

	uint32_t tempStartPixel = (( range << 8 ) + startAdres) * 128;

	for(int i = 0; i < 32; i++)
	{
		imageBuffer_cam1[tempStartPixel + i] = bufferArray.at(4 + i * 8); 
	}*/
}

void filled_up_data(boost::array<uint8_t, BUFFER_SIZE> bufferArray){

		uint16_t startAdres = (uint16_t) bufferArray.at(1);
		uint16_t range		= (uint16_t) bufferArray.at(2);

		uint32_t tempStartPixel = (( range << 8 ) + startAdres) * 32;
		
		for(int i = 0; i < 32 ; i++ ){	
				imageBuffer_cam1[tempStartPixel + i ]		= bufferArray[ OFFSET_STARTADRES + 2 + (i * 8)];
				imageBuffer_cam1[tempStartPixel + i	+ 1]	= bufferArray[ OFFSET_STARTADRES + 1 + (i * 8)];
				imageBuffer_cam1[tempStartPixel + i + 2]	= bufferArray[ OFFSET_STARTADRES +	   (i * 8)];

				imageBuffer_cam2[tempStartPixel + i ]		= bufferArray[ OFFSET_STARTADRES + 6 + (i * 8)];
				imageBuffer_cam2[tempStartPixel + i + 1]	= bufferArray[ OFFSET_STARTADRES + 5 + (i * 8)];
				imageBuffer_cam2[tempStartPixel + i + 2]	= bufferArray[ OFFSET_STARTADRES + 4 + (i * 8)];
		}
}

void equalized_data(void){
}

void rectified_data(void){
}

void correspondence(void){
}





