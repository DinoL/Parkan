#ifndef NGB_SIMPLE_IMAGE_DATA_H
#define NGB_SIMPLE_IMAGE_DATA_H

#include "ngb_image_data.h"

class NgbSimpleImageData : public NgbImageData
{
public:
    NgbSimpleImageData(const QFileInfo& i_path);

protected:
    void fill_data(std::wistream& io_file) override;
};

#endif // NGB_SIMPLE_IMAGE_DATA_H
