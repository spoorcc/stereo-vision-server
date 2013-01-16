#include "graphics_manager.h"

Graphics_Manager::Graphics_Manager(QObject *parent) : QObject(parent)
{
    imageBuffer.reserve(MAX_IMAGE_BUFFERS);
    fillBufferWithTestImage(0);
}

void Graphics_Manager::fillBuffer(QByteArray* buffer, int bufferId)
{
    if(bufferId < MAX_IMAGE_BUFFERS)
    {
        imageBuffer.replace(bufferId, buffer);
    }
}

QByteArray* Graphics_Manager::getBuffer(uint bufferId)
{
    if(bufferId < MAX_IMAGE_BUFFERS)
    {
        return imageBuffer.at(bufferId);
    }

    return NULL;
}

void Graphics_Manager::fillBufferWithTestImage(int bufferId)
{
    if(bufferId < MAX_IMAGE_BUFFERS)
    {
        //Load test image
        QImage image("/home/nick/stereo-vision-server/testimage.jpg");
        image.convertToFormat(QImage::Format_RGB888);
        image.scaled(640, 480, Qt::KeepAspectRatio);

        //Buffer and save the QByteArray
        QBuffer imgBuffer(imageBuffer.at(bufferId));
        imgBuffer.open(QIODevice::WriteOnly);
        image.save(&imgBuffer, "JPEG");
    }
}
