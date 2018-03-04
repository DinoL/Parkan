#ifndef DIB_IMAGE_DATA_H
#define DIB_IMAGE_DATA_H

#include "image_data.h"

class DibImageData : public ImageData
{
public:
    DibImageData(const QFileInfo& i_path);
};

#endif // DIB_IMAGE_DATA_H
