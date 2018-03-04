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
    interior_exporter.cpp \
    texture_exporter.cpp \
    obj_model.cpp \
    data_array.cpp \
    io_utils.cpp \
    image.cpp \
    texture_factory.cpp \
    image_dib.cpp \
    image_ngb.cpp \
    image_ngb_complex.cpp \
    image_data.cpp

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
    interior_exporter.h \
    texture_exporter.h \
    obj_model.h \
    data_array.h \
    io_utils.h \
    image.h \
    texture_factory.h \
    image_dib.h \
    image_ngb.h \
    image_ngb_complex.h \
    image_data.h


FORMS    += viewer_app.ui

RESOURCES += \
    palettes.qrc
