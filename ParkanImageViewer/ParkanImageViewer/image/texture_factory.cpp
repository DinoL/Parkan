#include "texture_factory.h"

#include "simple_image_data.h"
#include "dib_image_data.h"
#include "ngb_simple_image_data.h"
#include "ngb_complex_image_data.h"
#include "image_extensions.h"

#include "utils/exceptions.h"

enum ImageType
{
    Simple = 0,
    DIB = 1,
    SimpleNGB = 2,
    ComplexNGB = 3,
    Count = 4
};

std::unique_ptr<ImageData> get_image_by_type(const QFileInfo& i_file_info, int i_image_type)
{
    try
    {
        switch(i_image_type)
        {
        case ImageType::Simple:
            return std::make_unique<SimpleImageData>(i_file_info);
        case ImageType::DIB:
            return std::make_unique<DibImageData>(i_file_info);
        case ImageType::SimpleNGB:
            return std::make_unique<NgbSimpleImageData>(i_file_info);
        case ImageType::ComplexNGB:
            return std::make_unique<NgbComplexImageData>(i_file_info);
        default:
            return nullptr;
        }
    }
    catch(const ImageDataException&)
    {
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

QFileInfoList get_images(const QString& i_dir, bool i_recursive)
{
    const QStringList extensions = get_image_extensions();
    const QStringList file_masks = convert_to_file_masks(extensions);
    QFileInfoList all_images = get_files_from_dir_by_mask(i_dir, file_masks);

    if(i_recursive)
    {
        for(auto& sub_dir : QDir(i_dir).entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot))
        {
            QString sub_dir_path = sub_dir.absoluteFilePath();
            all_images += get_images(sub_dir_path, true);
        }
    }
    return all_images;
}

