#include "simple_animated_image_data.h"


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

SimpleAnimatedImageData::SimpleAnimatedImageData(const QFileInfo& i_path)
{
    const QFileInfoList files = populate(i_path);
    for(const auto file : files)
    {
        SimpleImageData image_data(file);
        m_frames.push_back(image_data);
    }
}

SimpleImageData SimpleAnimatedImageData::get_image(int i_frame) const
{
    return m_frames[i_frame % m_frames.size()];
}

SimpleImageData SimpleAnimatedImageData::next_image()
{
    ++m_frame;
    m_frame %= m_frames.size();
    return get_image(m_frame);
}

bool SimpleAnimatedImageData::is_valid() const
{
    return !m_frames.empty();
}
