#ifndef FRAME_GROUPPER_H
#define FRAME_GROUPPER_H

#include "image_frame.h"

#include <QFileInfo>
#include <QString>

#include <vector>

class FrameGroupper
{
public:
    using FrameGroup = std::vector<ImageFrame>;

    QFileInfoList to_info_list(const FrameGroup& i_frames) const;

    std::vector<ImageFrame> convert_to_frames(const QFileInfoList& i_paths) const;

    std::vector<FrameGroup> split_by_groups(const QFileInfoList& i_paths) const;

private:
    bool add_group(std::vector<FrameGroup>& io_all_groups, FrameGroup& io_group) const;

    bool merge(FrameGroup& io_group, const ImageFrame& i_frame) const;

    bool frames_are_sequential(const ImageFrame& i_first, const ImageFrame& i_second) const;

};

#endif // FRAME_GROUPPER_H
