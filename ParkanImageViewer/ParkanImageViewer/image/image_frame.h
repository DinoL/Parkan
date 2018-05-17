#ifndef IMAGE_FRAME_H
#define IMAGE_FRAME_H

#include <QFileInfo>
#include <QString>

class ImageFrame
{
public:
    ImageFrame(const QFileInfo& i_path);

    QFileInfo path() const;

    QString name() const;

    int number() const;

    bool operator<(const ImageFrame& i_other) const;

private:
    QFileInfo m_path;
    QString m_name;
    int m_number;
};
#endif // IMAGE_FRAME_H
