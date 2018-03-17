#include "files_filter.h"

QFileInfoList get_files_from_dir_by_mask(const QString& i_dir, const QStringList& i_file_masks)
{
    return QDir(i_dir).entryInfoList(i_file_masks);
}

QFileInfoList get_files_from_dir_by_mask(const QString& i_dir, const QString& i_file_mask)
{
    return QDir(i_dir).entryInfoList(QStringList() << i_file_mask);
}
