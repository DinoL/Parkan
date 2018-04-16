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
    color_ramp_widget.cpp \
    image_widget.cpp \
    binary_stream.cpp \
    input_binary_stream.cpp \
    output_binary_stream.cpp \
    interior.cpp \
    texture_exporter.cpp \
    obj_model.cpp \
    io_utils.cpp \
    image.cpp \
    texture_factory.cpp \
    image_data.cpp \
    simple_image_data.cpp \
    dib_image_data.cpp \
    nbg_image_data.cpp \
    ngb_complex_image_data.cpp \
    image_description_guard.cpp \
    files_filter.cpp \
    image_iterator.cpp \
    animated_image.cpp \
    ngb_simple_image_data.cpp \
    object_3d.cpp \
    vertex.cpp \
    face.cpp \
    vector_2d.cpp \
    short_string.cpp \
    string_utils.cpp \
    exceptions.cpp \
    geometry_3d.cpp \
    interior_file.cpp \
    geometry_exporter.cpp

HEADERS  += viewer_app.h \
    binary_file.h \
    palette.h \
    color_ramp_widget.h \
    image_widget.h \
    binary_stream.h \
    input_binary_stream.h \
    output_binary_stream.h \
    interior.h \
    texture_exporter.h \
    obj_model.h \
    io_utils.h \
    image.h \
    texture_factory.h \
    image_data.h \
    simple_image_data.h \
    dib_image_data.h \
    ngb_image_data.h \
    ngb_complex_image_data.h \
    image_description_guard.h \
    files_filter.h \
    image_iterator.h \
    animated_image.h \
    ngb_simple_image_data.h \
    object_3d.h \
    vertex.h \
    face.h \
    vector_2d.h \
    short_string.h \
    string_utils.h \
    exceptions.h \
    geometry_3d.h \
    interior_file.h \
    geometry_exporter.h


FORMS    += viewer_app.ui

RESOURCES += \
    palettes.qrc
