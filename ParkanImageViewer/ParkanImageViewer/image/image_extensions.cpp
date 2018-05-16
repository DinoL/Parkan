#include "image_extensions.h"

QStringList get_image_extensions()
{
    QStringList extensions{"*.DIB", "*.NGB", "*.F", "*.W"};
    extensions << get_animated_image_extensions();
    return extensions;
}

QStringList get_animated_image_extensions()
{
    QStringList extensions;
    for(QString ext : {"*.A", "*.V"})
    {
        for(int i = 0; i < 10; ++i)
        {
            extensions << (i == 0 ? ext : ext + QString::number(i));
        }
    }
    return extensions;
}
