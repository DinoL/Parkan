#ifndef NGB_IMAGE_DATA_H
#define NGB_IMAGE_DATA_H

#include "image_data.h"

class NgbImageData : public ImageData
{
public:
    NgbImageData(const QFileInfo& i_path);

private:
    uchar m_default_color;
};


#endif // NGB_IMAGE_DATA_H
