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
    geometry/face.cpp \
    geometry/geometry_3d.cpp \
    geometry/geometry_exporter.cpp \
    geometry/geometry_importer.cpp \
    geometry/interior.cpp \
    geometry/interior_file.cpp \
    geometry/obj_model.cpp \
    geometry/object_3d.cpp \
    geometry/serializable_geometry.cpp \
    image/animated_image.cpp \
    image/dib_image_data.cpp \
    image/image.cpp \
    image/image_data.cpp \
    image/image_description_guard.cpp \
    image/image_iterator.cpp \
    image/ngb_complex_image_data.cpp \
    image/ngb_image_data.cpp \
    image/ngb_simple_image_data.cpp \
    image/palette.cpp \
    image/simple_image_data.cpp \
    image/texture_exporter.cpp \
    image/texture_factory.cpp \
    ui/color_ramp_widget.cpp \
    ui/image_widget.cpp \
    ui/viewer_app.cpp \
    utils/binary_file.cpp \
    utils/binary_stream.cpp \
    utils/exceptions.cpp \
    utils/files_filter.cpp \
    utils/input_binary_stream.cpp \
    utils/io_utils.cpp \
    utils/output_binary_stream.cpp \
    utils/serializable.cpp \
    utils/short_string.cpp \
    utils/string_utils.cpp \
    utils/vector_2d.cpp \
    utils/vertex.cpp \
    image/frame_groupper.cpp

HEADERS  += geometry/face.h \
    geometry/geometry_3d.h \
    geometry/geometry_exporter.h \
    geometry/geometry_importer.h \
    geometry/interior.h \
    geometry/interior_file.h \
    geometry/obj_model.h \
    geometry/object_3d.h \
    geometry/serializable_geometry.h \
    image/animated_image.h \
    image/dib_image_data.h \
    image/image.h \
    image/image_data.h \
    image/image_description_guard.h \
    image/image_iterator.h \
    image/ngb_complex_image_data.h \
    image/ngb_image_data.h \
    image/ngb_simple_image_data.h \
    image/palette.h \
    image/simple_image_data.h \
    image/texture_exporter.h \
    image/texture_factory.h \
    ui/color_ramp_widget.h \
    ui/image_widget.h \
    ui/viewer_app.h \
    utils/binary_file.h \
    utils/binary_stream.h \
    utils/exceptions.h \
    utils/files_filter.h \
    utils/input_binary_stream.h \
    utils/io_utils.h \
    utils/output_binary_stream.h \
    utils/serializable.h \
    utils/short_string.h \
    utils/string_utils.h \
    utils/vector_2d.h \
    utils/vertex.h \
    image/frame_groupper.h


FORMS    += ui/viewer_app.ui

RESOURCES += \
    palettes.qrc \
    icons.qrc
