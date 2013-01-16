#ifndef GRAPHICS_MANAGER_H_
#define GRAPHICS_MANAGER_H_

#include <QObject>
#include <QByteArray>
#include <QList>
#include <QImage>
#include <QBuffer>
#include <opencv/highgui.h>
#include <opencv/cv.h>

#define MAX_IMAGE_BUFFERS 20

class Graphics_Manager : public QObject
{
	Q_OBJECT
public:
	explicit Graphics_Manager(QObject *parent = 0);
    void fillBuffer(QByteArray* buffer, int bufferId);
    QByteArray* getBuffer(uint bufferId);
    void fillBufferWithTestImage(int bufferId);
private:
    QList<QByteArray*> imageBuffer;
};

#endif /* GRAPHICS_MANAGER_H_ */
