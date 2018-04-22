#ifndef NGB_IMAGE_DATA_H
#define NGB_IMAGE_DATA_H

#include "image_data.h"

#include <iostream>
#include <vector>

class NgbImageData : public ImageData
{
public:
    NgbImageData(const QFileInfo& i_path);

protected:
    virtual void fill_data(std::istream&);
    bool has_signature(std::istream& io_file, const std::vector<uchar>& i_signature);

protected:
    uchar m_default_color;
};


#endif // NGB_IMAGE_DATA_H
