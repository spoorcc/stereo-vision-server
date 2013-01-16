#include "graphics_manager.h"

Graphics_Manager::Graphics_Manager(QObject *parent) : QObject(parent)
{
    imageByteArrayDeque.resize(MAX_IMAGE_BUFFERS);

    fillBufferWithTestImage("/home/nick/stereo-vision-server/fpga.bmp", 0);
    fillBufferWithTestImage("/home/nick/stereo-vision-server/testimage.jpg", 1);
}

void Graphics_Manager::fillBuffer(QByteArray* buffer, int bufferId)
{
    if(bufferId < MAX_IMAGE_BUFFERS)
    {
        imageByteArrayDeque[bufferId] = buffer;
    }
}

QByteArray* Graphics_Manager::getBuffer(int bufferId)
{
    qDebug() << "[Graphics_Manager] Get Buffer + " << bufferId;
    qDebug() << "[Graphics_Manager] Buffer: " << imageByteArrayDeque.at(bufferId);

    if(bufferId < MAX_IMAGE_BUFFERS)
    {
        return imageByteArrayDeque[bufferId];
    }

    return NULL;
}

void Graphics_Manager::fillBufferWithTestImage(QString fileName, int bufferId)
{
    if(bufferId < MAX_IMAGE_BUFFERS)
    {
        //Load test image
        QImage image(fileName);
        image.convertToFormat(QImage::Format_RGB888);
        image.scaled(640, 480, Qt::KeepAspectRatio);

        //Buffer and save the QByteArray
        QByteArray* testArray = new QByteArray();
        QBuffer imgBuffer(testArray);
        imgBuffer.open(QIODevice::WriteOnly);

        image.save(&imgBuffer, "BMP");
        //image.save(&imgBuffer, "JPEG");

        imageByteArrayDeque[bufferId] = testArray;
        qDebug() << "[Graphics Manager] Loaded image " << imageByteArrayDeque[bufferId] << "Size: " << imageByteArrayDeque[bufferId]->size();

    }
}
