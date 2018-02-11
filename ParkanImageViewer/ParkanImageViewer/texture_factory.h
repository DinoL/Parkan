#ifndef TEXTURE_FACTORY_H
#define TEXTURE_FACTORY_H

#include "image.h"

#include <QFileInfo>

#include <memory>

class TextureFactory
{
public:
    static std::unique_ptr<Image> build_image(const QFileInfo& i_file_info);
};

#endif // TEXTURE_FACTORY_H
