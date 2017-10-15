#ifndef TEXTURE_H
#define TEXTURE_H

#include "binary_file.h"
#include <palette.h>
#include <Eigen/Core>

using namespace Eigen;

class Texture : public BinaryFile
{
public:
    using ColorMatrix = Matrix<QColor, Dynamic, Dynamic>;
    using ColorIdMatrix = MatrixXi;

    Texture(const QFileInfo& i_path);

    ColorMatrix get_pixels(const Palette& i_palette);

    void save(const QString& i_out_file, const Palette& i_palette);

    ColorIdMatrix get_texture() const;

    void get_header_and_body() const;

    void get_width_and_height() const;

    static bool has_signature(const BinaryFile& i_binary);
};

#endif // TEXTURE_H
