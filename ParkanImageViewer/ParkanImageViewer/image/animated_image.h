#ifndef ANIMATED_IMAGE_H
#define ANIMATED_IMAGE_H

#include "image.h"

#include <QFileInfoList>

class AnimatedImage
{
public:
    AnimatedImage(const QFileInfo& i_path);
    AnimatedImage(const QFileInfoList& i_frame_paths);

    const Image& next_image();
    const Image& current_image() const;

    void set_palette(const Palette& i_palette);

    bool is_valid() const;
    bool is_single_frame() const;

private:
    void init(const QFileInfoList& i_frame_paths);

    const Image& get_image(int i_frame) const;

private:
    std::vector<Image> m_frames;
    int m_frame = 0;
};

#endif // ANIMATED_IMAGE_H
