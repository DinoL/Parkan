#ifndef SIMPLE_IMAGE_DATA_H
#define SIMPLE_IMAGE_DATA_H

#include "image_data.h"

class SimpleImageData : public ImageData
{
public:
    SimpleImageData(const QFileInfo& i_path);
};

#endif // SIMPLE_IMAGE_DATA_H
