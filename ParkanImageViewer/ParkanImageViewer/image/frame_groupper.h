#ifndef FRAME_GROUPPER_H
#define FRAME_GROUPPER_H

#include <QFileInfo>
#include <QDir>
#include <QString>

#include <vector>

class FrameGroupper
{
public:
    FrameGroupper();

    using FrameGroup = QFileInfoList;

    std::vector<FrameGroup> split_by_groups(const QFileInfoList& i_paths) const
    {
        std::vector<FrameGroup> all_groups;

        FrameGroup cur_group = {};

        for(const auto& path : i_paths)
        {
            if(!merge(cur_group, path))
            {
                if(!cur_group.isEmpty())
                    all_groups.push_back(cur_group);

                cur_group = { path };
            }
        }
        if(!cur_group.empty())
            all_groups.push_back(cur_group);

        return all_groups;

    }

private:
    bool merge(FrameGroup& io_group, const QFileInfo& i_path) const
    {
        if(io_group.empty() || !paths_are_sequential(io_group.back(), i_path))
            return false;

        io_group.push_back(i_path);
        return true;
    }

    bool paths_are_sequential(const QFileInfo& i_first, const QFileInfo& i_second) const
    {
        if(i_first.absoluteDir().absolutePath() != i_second.absoluteDir().absolutePath())
            return false;

        const auto first_ext = i_first.suffix();
        const auto second_ext = i_second.suffix();

        if(first_ext == second_ext)
        {
            return names_are_sequential(i_first.baseName(), i_second.baseName());
        }
        else
        {
            return names_are_sequential(first_ext, second_ext);
        }
    }

    bool names_are_sequential(const QString& i_first, const QString& i_second) const
    {
        int i = 0;
        while(i < i_first.size() && i < i_second.size())
        {
            if(i_first[i] != i_second[i])
                break;

            ++i;
        }

        if (i == i_first.size() || i == i_second.size())
            return false;

        const QString first_end = i_first.right(i_first.size() - i);
        const QString second_end = i_second.right(i_second.size() - i);

        bool first_is_numeric, second_is_numeric;
        const int first_id = first_end.toInt(&first_is_numeric, 10);
        const int second_id = second_end.toInt(&second_is_numeric, 10);
        if(!first_is_numeric || !second_is_numeric)
            return false;

        return second_id == first_id + 1;
    }

};

#endif // FRAME_GROUPPER_H
