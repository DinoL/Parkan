#ifndef FILES_FILTER_H
#define FILES_FILTER_H

#include <QDir>
#include <QFileInfo>
#include <QStringList>

QStringList convert_to_file_masks(const QStringList& i_extensions);

QFileInfoList get_files_from_dir_by_mask(const QString& i_dir, const QStringList& i_file_masks);

QFileInfoList get_files_from_dir_by_mask(const QString& i_dir, const QString& i_file_mask);

#endif // FILES_FILTER_H
