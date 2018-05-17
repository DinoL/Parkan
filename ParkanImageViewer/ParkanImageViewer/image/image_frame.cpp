#include "image_frame.h"

#include "image_extensions.h"

#include <QRegularExpression>

struct NameNumberSplitter
{
    NameNumberSplitter(const QString& i_str)
    {
        if(i_str.isEmpty())
            return;

        const int first_digit = i_str.lastIndexOf(QRegularExpression("\\D")) + 1;
        if(first_digit >= i_str.size())
        {
            name = i_str;
            return;
        }

        const QString numeric_part = i_str.right(i_str.size() - first_digit);
        bool has_number = false;
        int temp = numeric_part.toInt(&has_number, 10);
        if(has_number)
        {
            name = i_str.left(first_digit);
            number = temp;
        }
        else
        {
            name = i_str;
        }
    }

    QString name = "";
    int number = 0;
};

ImageFrame::ImageFrame(const QFileInfo& i_path) :
    m_path(i_path)
{
    const QString ext = i_path.suffix();

    if(get_animated_image_extensions().contains(ext))
    {
        // this image can be animated only by extension, numbers in filename denote different images
        const NameNumberSplitter split(ext);
        m_number = split.number;
        m_name = i_path.baseName() + '.' + split.name;
    }
    else
    {
        // extension does not contain number, so try filename
        const NameNumberSplitter split(i_path.baseName());
        m_number = split.number;
        m_name = split.name + '.' + ext;
    }
}

QFileInfo ImageFrame::path() const
{
    return m_path;
}

QString ImageFrame::name() const
{
    return m_name;
}

int ImageFrame::number() const
{
    return m_number;
}
