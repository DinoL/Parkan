#ifndef IMAGE_NGB_COMPLEX_H
#define IMAGE_NGB_COMPLEX_H


#include "image_data.h"

class ImageNgbComplex : public ImageData
{
public:
    ImageNgbComplex(const QFileInfo& i_path);

private:
    uchar m_default_color;
};


#endif // IMAGE_NGB_COMPLEX_H
