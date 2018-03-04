#include "texture_factory.h"

#include "texture.h"
#include "image_dib.h"
#include "image_ngb.h"
#include "image_ngb_complex.h"

std::unique_ptr<Image> TextureFactory::build_image(const QFileInfo& i_file_info)
{
    const QString ext = i_file_info.suffix();
    if(ext.toLower() == "dib")
    {
        return std::make_unique<Image>(ImageDib(i_file_info).get_image());
    }
    else if(ext.toLower() == "ngb")
    {
        return std::make_unique<Image>(ImageNgbComplex(i_file_info).get_image());
    }
    return std::make_unique<Image>(Texture(i_file_info).get_image());
}
