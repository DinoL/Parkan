#ifndef TEXTURE_EXPORTER_H
#define TEXTURE_EXPORTER_H

#include "palette.h"
#include "simple_image_data.h"

#include <QFileInfo>
#include <QString>
#include <string>
#include <QDir>

std::string to_std_string(const std::string& i_str);
std::string to_std_string(const QString& i_str);
std::string to_std_string(const char* i_str);

class TextureExporter
{
public:
    template<typename Container>
    void export_textures(const Container& i_textures, const Palette& i_palette, const QDir& i_out_dir) const
    {
        for(const auto& path : i_textures)
        {
            const QString in_path(to_std_string(path).c_str());
            const QFileInfo info(in_path);
            const SimpleImageData raw_data(info);
            Image texture(raw_data.get_image());
            texture.set_palette(i_palette);

            const QString output_path = i_out_dir.absoluteFilePath(info.fileName() + ".png");
            texture.save(output_path);
        }
    }
};

#endif // TEXTURE_EXPORTER_H
