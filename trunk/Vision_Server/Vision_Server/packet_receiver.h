#include <conio.h>
#include <stdio.h>
#include <stdint.h>
#include <string>
#include <sstream>
#include <highgui.h>
#include <cv.h>
#include <boost/array.hpp>

#define BUFFER_SIZE		260
#define FILL_UP_PIXEL_SIZE 921600
using namespace std;
using namespace boost;

extern uint8_t imageBuffer_cam1[FILL_UP_PIXEL_SIZE];
extern uint8_t imageBuffer_cam2[FILL_UP_PIXEL_SIZE];
extern uint8_t imageBuffer_cam3[FILL_UP_PIXEL_SIZE];
extern uint8_t imageBuffer_cam4[FILL_UP_PIXEL_SIZE];
extern uint8_t imageBuffer_cam5[FILL_UP_PIXEL_SIZE];
extern uint8_t imageBuffer_cam6[FILL_UP_PIXEL_SIZE];
extern uint8_t imageBuffer_cam7[FILL_UP_PIXEL_SIZE];
extern uint8_t imageBuffer_cam8[FILL_UP_PIXEL_SIZE];

void maikeImage(uint8_t bufferArray[FILL_UP_PIXEL_SIZE]);
void cam_config(void);
void proces_config(void);
void callib_data(void);
void raw_rgb_data(boost::array<uint8_t, BUFFER_SIZE> bufferArray );
void filled_up_data(boost::array<uint8_t, BUFFER_SIZE> bufferArray);
void equalized_data(void);
void rectified_data(void);
void correspondence(void);