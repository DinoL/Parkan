#include "frame_groupper.h"

#include <algorithm>

QFileInfoList FrameGroupper::to_info_list(const FrameGroupper::FrameGroup& i_frames) const
{
    QFileInfoList paths;
    for(const auto& frame : i_frames)
    {
        paths.push_back(frame.path());
    }
    return paths;
}

std::vector<ImageFrame> FrameGroupper::convert_to_frames(const QFileInfoList& i_paths) const
{
    std::vector<ImageFrame> result;
    std::transform(i_paths.begin(), i_paths.end(), std::back_inserter(result),
                   [](const QFileInfo& i_path){ return ImageFrame(i_path); });
    return result;
}

std::vector<FrameGroupper::FrameGroup> FrameGroupper::split_by_groups(const QFileInfoList& i_paths) const
{
    if(i_paths.empty())
        return {};

    std::vector<ImageFrame> frames = convert_to_frames(i_paths);

    if(i_paths.size() == 1)
    {
        return { frames };
    }

    std::vector<FrameGroup> all_groups;

    FrameGroup cur_group;
    for(const auto& frame : frames)
    {
        if(!merge(cur_group, frame))
        {
            add_group(all_groups, cur_group);
            cur_group = { frame };
        }
    }
    add_group(all_groups, cur_group);

    return all_groups;
}

bool FrameGroupper::add_group(std::vector<FrameGroupper::FrameGroup>& io_all_groups, FrameGroupper::FrameGroup& io_group) const
{
    if(io_group.empty())
        return false;

    if(io_group.size() > 1)
    {
        auto by_number = [](const ImageFrame& i_lhs, const ImageFrame& i_rhs)
        {
            return i_lhs.number() < i_rhs.number();
        };

        // sort group by frame number
        std::sort(io_group.begin(), io_group.end(), by_number);
    }

    io_all_groups.push_back(io_group);
    return true;
}

bool FrameGroupper::merge(FrameGroupper::FrameGroup& io_group, const ImageFrame& i_frame) const
{
    if(io_group.empty() || !frames_are_in_one_group(io_group.back(), i_frame))
        return false;

    io_group.push_back(i_frame);
    return true;
}

bool FrameGroupper::frames_are_in_one_group(const ImageFrame& i_first, const ImageFrame& i_second) const
{
    return i_first.name() == i_second.name();
}
