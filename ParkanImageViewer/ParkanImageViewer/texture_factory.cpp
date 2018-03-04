#include "texture_factory.h"

#include "simle_image_data.h"
#include "image_dib.h"
#include "image_ngb.h"
#include "image_ngb_complex.h"

std::unique_ptr<Image> TextureFactory::build_image(const QFileInfo& i_file_info)
{
    const QString ext = i_file_info.suffix();
    if(ext.toLower() == "dib")
    {
        return std::make_unique<Image>(DibImageData(i_file_info).get_image());
    }
    else if(ext.toLower() == "ngb")
    {
        return std::make_unique<Image>(NgbComplexImageData(i_file_info).get_image());
    }
    return std::make_unique<Image>(SimpleImageData(i_file_info).get_image());
}
