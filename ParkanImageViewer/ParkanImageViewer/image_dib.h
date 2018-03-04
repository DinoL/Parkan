#ifndef IMAGE_DIB_H
#define IMAGE_DIB_H

#include "image_data.h"

class ImageDib : public ImageData
{
public:
    ImageDib(const QFileInfo& i_path);
};

#endif // IMAGE_DIB_H
