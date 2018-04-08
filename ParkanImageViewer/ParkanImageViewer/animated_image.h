#ifndef ANIMATED_IMAGE_H
#define ANIMATED_IMAGE_H

#include "image.h"

#include <QFileInfoList>

class AnimatedImage
{
public:
    AnimatedImage(const QFileInfo& i_path);

    Image next_image();

    bool is_valid() const;

private:
    Image get_image(int i_frame) const;

private:
    std::vector<Image> m_frames;
    int m_frame = 0;
};

#endif // ANIMATED_IMAGE_H
