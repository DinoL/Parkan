#ifndef IMAGE_DIB_H
#define IMAGE_DIB_H

#include "image.h"

class ImageDib : public Image
{
public:
    ImageDib(const QFileInfo& i_path);
};

#endif // IMAGE_DIB_H
