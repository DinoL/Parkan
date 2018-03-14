#include "texture_factory.h"

#include "simple_image_data.h"
#include "dib_image_data.h"
#include "ngb_image_data.h"
#include "ngb_complex_image_data.h"

enum ImageType
{
    Simple = 0,
    DIB = 1,
    NGB = 2,
    ComplexNGB = 3,
    Count = 4
};

std::unique_ptr<ImageData> get_image_by_type(const QFileInfo& i_file_info, int i_image_type)
{
    switch(i_image_type)
    {
    case ImageType::Simple:
        return std::make_unique<SimpleImageData>(i_file_info);
    case ImageType::DIB:
        return std::make_unique<DibImageData>(i_file_info);
    case ImageType::NGB:
        return std::make_unique<NgbImageData>(i_file_info);
    case ImageType::ComplexNGB:
        return std::make_unique<NgbComplexImageData>(i_file_info);
    default:
        return nullptr;
    }
}

std::unique_ptr<Image> TextureFactory::build_image(const QFileInfo& i_file_info)
{
    for(int image_type = ImageType::Simple; image_type < ImageType::Count; ++image_type)
    {
        auto image_data = get_image_by_type(i_file_info, image_type);
        if(image_data && image_data->is_valid())
            return std::make_unique<Image>(image_data->get_image());
    }
    return nullptr;
}
