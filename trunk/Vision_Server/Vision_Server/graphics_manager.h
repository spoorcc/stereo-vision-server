#ifndef GRAPHICS_MANAGER_H
#define GRAPHICS_MANAGER_H

#include <highgui.h>
#include <cv.h>
#include <vector>
#include <stdint.h>
#include <boost/thread.hpp>

class Graphics_Manager {
public:
	static std::vector<uint8_t> jpegImageBuffer;
	Graphics_Manager::Graphics_Manager(void);
	void Graphics_Manager::startGraphicsManager(void);
};

#endif /* GRAPHICS_MANAGER_H */