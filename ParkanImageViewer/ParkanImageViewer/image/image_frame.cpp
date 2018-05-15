#include "image_frame.h"

#include <QRegularExpression>

ImageFrame::ImageFrame(const QFileInfo& i_path) :
    m_path(i_path)
{
    const QString ext = i_path.suffix();
    int number;
    if(extract_number(ext, number))
    {
        m_number = number;
        const int first_digit = ext.lastIndexOf(QRegularExpression("\\D")) + 1;
        m_name = i_path.baseName() + '.' + ext.left(first_digit);
        return;
    }

    const QString filename = i_path.baseName();
    if(extract_number(filename, number))
    {
        m_number = number;
        const int first_digit = filename.lastIndexOf(QRegularExpression("\\D")) + 1;
        m_name = filename.left(first_digit) + '.' + ext;
        return;
    }

    m_number = 0;
    m_name = i_path.fileName();
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

bool ImageFrame::extract_number(const QString& i_str, int& o_number) const
{
    if(i_str.isEmpty())
        return false;

    const int first_digit = i_str.lastIndexOf(QRegularExpression("\\D")) + 1;
    if(first_digit >= i_str.size())
        return false;

    const QString numeric_part = i_str.right(i_str.size() - first_digit);
    bool has_number = false;
    o_number = numeric_part.toInt(&has_number, 10);
    return has_number;
}
