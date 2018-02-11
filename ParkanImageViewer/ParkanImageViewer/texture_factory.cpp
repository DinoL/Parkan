#include "texture_factory.h"

#include "texture.h"
#include "image_dib.h"

std::unique_ptr<Image> TextureFactory::
build_image(const QFileInfo& i_file_info)
{
    const QString ext = i_file_info.suffix();
    if(ext.toLower() == "dib")
    {
        return std::unique_ptr<Image>(new ImageDib(i_file_info));
    }
    return std::unique_ptr<Image>(new Texture(i_file_info));
}
