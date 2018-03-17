#include "files_filter.h"

QFileInfoList get_files_from_dir_by_mask(const QString& i_dir_name, const QStringList& i_file_masks)
{
    return QDir(i_dir_name).entryInfoList(i_file_masks);
}

QFileInfoList get_files_from_dir_by_mask(const QString& i_dir_name, const QString& i_file_mask)
{
    return QDir(i_dir_name).entryInfoList(QStringList() << i_file_mask);
}
