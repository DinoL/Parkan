#ifndef SIMPLE_ANIMATED_IMAGE_DATA_H
#define SIMPLE_ANIMATED_IMAGE_DATA_H

#include "simple_image_data.h"

#include <QFileInfoList>
#include <QRegExp>

class SimpleAnimatedImageData
{
public:
    SimpleAnimatedImageData(const QFileInfo& i_path);

    SimpleImageData next_image();

    bool is_valid() const;

private:
    SimpleImageData get_image(int i_frame) const;

private:
    std::vector<SimpleImageData> m_frames;
    int m_frame = 0;
};

#endif // SIMPLE_ANIMATED_IMAGE_DATA_H
