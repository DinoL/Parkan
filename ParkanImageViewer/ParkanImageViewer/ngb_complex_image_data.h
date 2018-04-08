#ifndef NGB_COMPLEX_IMAGE_DATA_H
#define NGB_COMPLEX_IMAGE_DATA_H

#include "ngb_image_data.h"
#include "binary_stream.h"

class NgbComplexImageData : public NgbImageData
{
public:
    NgbComplexImageData(const QFileInfo& i_path);

protected:
    void fill_data(std::istream& io_file) override;
};


#endif // NGB_COMPLEX_IMAGE_DATA_H
