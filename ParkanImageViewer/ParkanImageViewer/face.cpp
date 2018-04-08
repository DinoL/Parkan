#include "face.h"

#include "short_string.h"

InputBinaryStream& operator>>(InputBinaryStream& s, Face& f)
{
    int cnt;
    s >> cnt;
    f.pts.resize(cnt);
    for(FacePoint& p : f.pts)
    {
        s >> p.id;
    }
    for(FacePoint& p : f.pts)
    {
        s >> p.uv;
    }
    for(FacePoint& p : f.pts)
    {
        s >> p.k;
    }
    ShortString str;
    s >> str;
    f.texture = str.to_string().toStdString();
    return s;
}

OutputBinaryStream& operator<<(OutputBinaryStream& s, const Face& f)
{
    for(const FacePoint& p : f.pts)
    {
        s << p.id;
    }
    return s;
}

std::ostream& operator<<(std::ostream& s, const Face& f)
{
    s << "Face(";
    for(const FacePoint& p : f.pts)
    {
        s << p.id << ' ';
    }
    s << ") ";
    return s;
}

std::istream& operator>>(std::istream& s, Face& f)
{
    int cnt;
    s >> cnt;
    f.pts.resize(cnt);
    for(FacePoint& p : f.pts)
    {
        s >> p.id;
    }
    for(FacePoint& p : f.pts)
    {
        s >> p.uv;
    }
    for(FacePoint& p : f.pts)
    {
        s >> p.k;
    }
    s >> f.texture;
    return s;
}
