#ifndef NGB_IMAGE_DATA_H
#define NGB_IMAGE_DATA_H

#include "image_data.h"

#include <QRect>

#include <iostream>
#include <vector>

class NgbImageData : public ImageData
{
public:
    NgbImageData(const QFileInfo& i_path);

protected:
    virtual void fill_data(std::istream&);
    bool has_signature(std::istream& io_file, const std::vector<uchar>& i_signature);

    QByteArray overlay_with_background() const;

protected:
    uchar m_default_color;
    QRect m_boundary;
};


#endif // NGB_IMAGE_DATA_H
