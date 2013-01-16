#include <camera_incoming_data_handler.h>

Camera_Incoming_Data_Handler::Camera_Incoming_Data_Handler(QObject *parent) : QObject(parent)
{

}

void Camera_Incoming_Data_Handler::handleData(const uchar* data)
{
    if(DEBUG)
    {
        printRawData(data);
    }

    QByteArray buffer = QByteArray::fromRawData((char*)data, sizeof(data));
}

void Camera_Incoming_Data_Handler::printRawData( const uchar* data )
{
    QPcapEthernetPacket ether(data);
    qDebug() << "[Camera Data Handler] == Ethernet ==";
    qDebug() << "[Camera Data Handler] Source: " << ether.sourceHost();
    qDebug() << "[Camera Data Handler] Dest: " << ether.destHost();

    if (ether.isIpPacket()) {
        QPcapIpPacket ip = ether.toIpPacket();
        qDebug() << "[Camera Data Handler] == IP ==";
        qDebug() << "[Camera Data Handler] Source:" << ip.source();
        qDebug() << "[Camera Data Handler] Dest:" << ip.dest();

        if (ip.isUdpPacket()) {
            QPcapUdpPacket udp = ip.toUdpPacket();
            qDebug() << "[Camera Data Handler] == UDP ==";
            qDebug() << "[Camera Data Handler] Source Port:" << udp.sourcePort();
            qDebug() << "[Camera Data Handler] Dest Port:" << udp.destPort();

            if ( udp.dataLength() ) {
                qDebug() << "[Camera Data Handler] == Data ==";
                qDebug() << "[Camera Data Handler] " << udp.data();
            }
        }
        else
        {
            QPcapTcpPacket tcp = ip.toTcpPacket();
            qDebug() << "[Camera Data Handler] == UDP ==";
            qDebug() << "[Camera Data Handler] Source Port:" << tcp.sourcePort();
            qDebug() << "[Camera Data Handler] Dest Port:" << tcp.destPort();

            if ( tcp.dataLength() ) {
                qDebug() << "== Data ==";
                qDebug() << "[Camera Data Handler] " << tcp.data();
            }
        }
    }
    qDebug();
}
