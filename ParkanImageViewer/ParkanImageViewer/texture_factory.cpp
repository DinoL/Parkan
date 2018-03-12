#include "texture_factory.h"

#include "simple_image_data.h"
#include "dib_image_data.h"
#include "ngb_image_data.h"
#include "ngb_complex_image_data.h"

std::unique_ptr<Image> TextureFactory::build_image(const QFileInfo& i_file_info)
{
    std::unique_ptr<ImageData> data;

    data.reset(new SimpleImageData(i_file_info));
    if(data && data->is_valid())
    {
        return std::make_unique<Image>(data->get_image());
    }

    data.reset(new DibImageData(i_file_info));
    if(data && data->is_valid())
    {
        return std::make_unique<Image>(data->get_image());
    }

    data.reset(new NgbImageData(i_file_info));
    if(data && data->is_valid())
    {
        return std::make_unique<Image>(data->get_image());
    }

    data.reset(new NgbComplexImageData(i_file_info));
    if(data && data->is_valid())
    {
        return std::make_unique<Image>(data->get_image());
    }

    throw "Incorrect image opened!";
}
