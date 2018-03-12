#include "texture_factory.h"

#include "simple_image_data.h"
#include "dib_image_data.h"
#include "ngb_image_data.h"
#include "ngb_complex_image_data.h"

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
