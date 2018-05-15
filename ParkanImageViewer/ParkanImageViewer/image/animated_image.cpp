#include "animated_image.h"
#include "texture_factory.h"

#include <QRegExp>

QFileInfoList populate(const QFileInfo& i_path)
{
    const QString ext = i_path.suffix();
    int last_ch = ext.lastIndexOf(QRegExp("[\\w]"));
    if(last_ch == ext.size())
        return QFileInfoList{i_path};

    QString root_ext = ext.left(last_ch);
    QFileInfoList res;
    for(int i = 1; i < 10; ++i)
    {
        QString new_ext = root_ext + QString::number(i);
        QString new_file = i_path.baseName() + '.' + new_ext;
        QFileInfo new_info(i_path.absoluteDir(), new_file);
        if(new_info.exists())
            res << new_info;
    }
    return res;
}

AnimatedImage::AnimatedImage(const QFileInfo& i_path)
{
    const QFileInfoList files = populate(i_path);
    init(files);
}

AnimatedImage::AnimatedImage(const QFileInfoList& i_frame_paths)
{
    init(i_frame_paths);
}

const Image& AnimatedImage::get_image(int i_frame) const
{
    return m_frames[i_frame % m_frames.size()];
}

const Image& AnimatedImage::current_image() const
{
    return get_image(m_frame);
}

void AnimatedImage::set_palette(const Palette& i_palette)
{
    for(Image& frame : m_frames)
    {
        frame.set_palette(i_palette);
    }
}

const Image& AnimatedImage::next_image()
{
    ++m_frame;
    m_frame %= m_frames.size();
    return get_image(m_frame);
}

bool AnimatedImage::is_valid() const
{
    return !m_frames.empty();
}

void AnimatedImage::init(const QFileInfoList& i_frame_paths)
{
    for(const auto file : i_frame_paths)
    {
        if(const auto image = TextureFactory::build_image(file))
            m_frames.push_back(*image);
    }
}
