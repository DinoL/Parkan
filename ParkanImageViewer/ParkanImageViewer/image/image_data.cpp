#include "image_data.h"

#include "utils/exceptions.h"

ImageData::ImageData(const QFileInfo& i_path) :
    m_path(i_path)
{}

ImageData::~ImageData()
{}

qint32 ImageData::width() const
{
    return m_width;
}

qint32 ImageData::height() const
{
    return m_height;
}

bool ImageData::is_valid() const
{
    return m_width > 0 && m_height > 0 && m_data.size() >= m_width * m_height;
}

Image ImageData::get_image() const
{
    if(!is_valid())
    {
        throw DecodeImageDataException("Cannot create image from data");
    }

    const QImage image = data_to_image(m_data, {m_width, m_height});
    return Image(image, m_path);
}

QImage ImageData::data_to_image(const QByteArray& i_data, QSize i_size)
{
    const int width = i_size.width();
    const int height = i_size.height();
    if(i_data.size() != width * height)
    {
        throw DecodeImageDataException(QString("Cannot create image from data: sizes mismatch"
                                       "%1 != %2").arg(i_data.size(), width * height));
    }

    QImage image(width, height, QImage::QImage::Format_Indexed8);
    for(qint32 y = 0; y < height; ++y)
    {
        auto* row = image.scanLine(y);
        for(qint32 x = 0; x < width; ++x)
        {
            row[x] = i_data[x + width * y];
        }
    }
    return image;


}

int ImageData::point_to_index(int x, int y, int width)
{
    return x + y * width;
}
