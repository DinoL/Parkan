#ifndef TEXTURE_EXPORTER_H
#define TEXTURE_EXPORTER_H

#include "palette.h"
#include "simple_image_data.h"

#include "utils/string_utils.h"

#include <QFileInfo>
#include <QString>
#include <string>
#include <QDir>

class TextureExporter
{
public:
    void set_textures_dir(const QDir& i_dir)
    {
        m_textures_dir = i_dir;
    }

    template<typename Container>
    void export_textures(const Container& i_textures, const Palette& i_palette, const QDir& i_out_dir) const
    {
        if(!m_textures_dir.isReadable())
            return;

        std::cout << "Exporting textures to " << i_out_dir.path().toStdString() << std::endl;
        for(const auto& name : i_textures)
        {
            const QString texture_name(to_std_string(name).c_str());
            const QFileInfo info(m_textures_dir, texture_name);

            std::cout << "Exporting texture " << name << " (" << info.absoluteFilePath() << ")" << std::endl;

            const SimpleImageData raw_data(info);
            Image texture(raw_data.get_image());
            texture.set_palette(i_palette);

            const QString output_path = i_out_dir.absoluteFilePath(info.fileName() + ".png");
            texture.save(output_path);
        }
    }

private:
    QDir m_textures_dir;
};

#endif // TEXTURE_EXPORTER_H
