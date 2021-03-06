#ifndef TEXTURE_FACTORY_H
#define TEXTURE_FACTORY_H

#include "image.h"

#include "utils/files_filter.h"

#include <QStringList>
#include <QFileInfoList>

#include <memory>

class TextureFactory
{
public:
    static std::unique_ptr<Image> build_image(const QFileInfo& i_file_info);
};

QStringList get_animated_image_extensions();
QStringList get_image_extensions();

QFileInfoList get_images(const QString& i_dir, bool i_recursive = false);

#endif // TEXTURE_FACTORY_H
