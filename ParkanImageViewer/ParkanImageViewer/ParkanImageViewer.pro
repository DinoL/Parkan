#-------------------------------------------------
#
# Project created by QtCreator 2017-10-10T23:08:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ParkanImageViewer
TEMPLATE = app


SOURCES += main.cpp\
        viewer_app.cpp \
    binary_file.cpp \
    palette.cpp \
    texture.cpp \
    color_ramp_widget.cpp \
    image_widget.cpp \
    binary_stream.cpp \
    input_binary_stream.cpp \
    output_binary_stream.cpp \
    interior.cpp \
    interior_exporter.cpp

HEADERS  += viewer_app.h \
    binary_file.h \
    palette.h \
    texture.h \
    color_ramp_widget.h \
    image_widget.h \
    binary_stream.h \
    input_binary_stream.h \
    output_binary_stream.h \
    interior.h \
    interior_exporter.h

FORMS    += viewer_app.ui

RESOURCES += \
    palettes.qrc
