#-------------------------------------------------
#
# Project created by QtCreator 2012-12-21T10:28:15
#
#-------------------------------------------------

QT       += core network

TARGET = Vision_Server
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
  #  packetReceiver.cpp \
    message_counter.cpp \
  #  graphics_manager.cpp \
    client_send_socket.cpp \
    client_receive_socket.cpp \
    client_packet.cpp \
    client_manager.cpp \
    client_image_data_queuer.cpp \
    client_data_sender.cpp \
    client_data_receiver.cpp \
    client_data_handler.cpp \
    client.cpp \
    camera_packet.cpp \
    camera_manager.cpp \
    camera_connection.cpp \
    qpcap/qpcap_qpcappacket.cpp \
    qpcap/qpcap_qpcap.cpp \
    camera_incoming_data_handler.cpp

HEADERS += \
  #  packet_receiver.h \
    message_counter.h \
  #  graphics_manager.h \
    client_server_protocol.h \
    client_send_socket.h \
    client_receive_socket.h \
    client_packet.h \
    client_manager.h \
    client_image_data_queuer.h \
    client_data_sender.h \
    client_data_receiver.h \
    client_data_handler.h \
    client.h \
    camera_packet.h \
    camera_manager.h \
    camera_connection.h \
    qpcap/qpcap_qpcapudppacket.h \
    qpcap/qpcap_qpcaptcppacket.h \
    qpcap/qpcap_qpcapippacket.h \
    qpcap/qpcap_qpcapethernetpacket.h \
    qpcap/qpcap_qpcap.h \
    camera_incoming_data_handler.h \
    const.h

LIBS += -L/usr/local/lib \
-lopencv_core \
-lopencv_imgproc \
-lopencv_highgui \
-lopencv_ml \
-lopencv_video \
-lopencv_features2d \
-lopencv_calib3d \
-lopencv_objdetect \
-lopencv_contrib \
-lopencv_legacy \
-lopencv_flann \
-lpcap
