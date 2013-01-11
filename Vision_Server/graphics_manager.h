#ifndef GRAPHICS_MANAGER_H_
#define GRAPHICS_MANAGER_H_

#include <QThread>
#include <opencv/highgui.h>
#include <opencv/cv.h>
#include <vector>
#include <stdint.h>

class Graphics_Manager : public QObject
{
	Q_OBJECT
public:
	explicit Graphics_Manager(QObject *parent = 0);
public slots:
	void requestImage();
signals:
	void requestedImage(std::vector<uint8_t> jpegImageBuffer);
private:
	void run();
	std::vector<uint8_t> jpegImageBuffer;
};

#endif /* GRAPHICS_MANAGER_H_ */
