#ifndef NGB_COMPLEX_IMAGE_DATA_H
#define NGB_COMPLEX_IMAGE_DATA_H


#include "image_data.h"

class NgbComplexImageData : public ImageData
{
public:
    NgbComplexImageData(const QFileInfo& i_path);

private:
    uchar m_default_color;
};


#endif // NGB_COMPLEX_IMAGE_DATA_H
