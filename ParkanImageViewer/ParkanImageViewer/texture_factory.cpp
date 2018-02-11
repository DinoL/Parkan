#include "texture_factory.h"

#include "texture.h"

std::unique_ptr<Image> TextureFactory::
build_image(const QFileInfo& i_file_info)
{
    return std::unique_ptr<Image>(new Texture(i_file_info));
}
