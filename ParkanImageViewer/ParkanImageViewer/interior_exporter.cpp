#include "interior_exporter.h"

#include "io_utils.h"
#include "texture_exporter.h"
#include "palette.h"
#include "obj_model.h"

#include <QFileInfo>
#include <QDir>
#include <QString>

#include <set>
#include <fstream>


bool InteriorExporter::export_interior(const QString& i_from, const QString& i_to) const
{
    InteriorExporter::ExportFormat format = auto_detect_format(i_to);
    return export_interior(i_from, i_to, format);
}

bool InteriorExporter::export_interior(const QString& i_from,
                                       const QString& i_to,
                                       InteriorExporter::ExportFormat i_format) const
{
    switch(i_format)
    {
    case ExportFormat::Text:
        return export_as_text(i_from, i_to);
    case ExportFormat::Obj:
        return export_as_obj(i_from, i_to);
    case ExportFormat::TexturedObj:
        return export_as_textured_obj(i_from, i_to);
    default:
        return false;
    }
}

bool InteriorExporter::export_all_used_textures(const QFileInfoList& i_all_interiors, const QString& i_to) const
{
    if(i_all_interiors.empty())
        return false;

    std::set<QString> texture_names;

    for(const auto& interior_file : i_all_interiors)
    {
        const QString file_path = interior_file.absoluteFilePath();
        std::cout << "Parsing interior file " << file_path.toStdString() << std::endl;
        const auto old_size = texture_names.size();

        InteriorFile interior;
        if(!import_interior(file_path, interior))
        {
            std::cout << "Could not load interior" << std::endl;
            continue;
        }

        const auto new_names = interior.all_texture_names();
        texture_names.insert(new_names.begin(), new_names.end());

        const auto new_size = texture_names.size();
        std::cout << "Found " << new_size - old_size << " new textures" << std::endl;
    }

    if(texture_names.empty())
        return false;

    std::ofstream out(i_to.toStdString());
    for(const auto& name : texture_names)
    {
        out << name << std::endl;
    }
    return true;
}

QFileInfo replace_dir_and_extension(const QFileInfo& i_filepath, const QDir& i_new_dir, const QString& i_new_ext)
{
    return QFileInfo(i_new_dir, i_filepath.baseName() + i_new_ext);
}

bool InteriorExporter::export_all_interiors(const QFileInfoList& i_all_interiors, const QDir& i_out_directory) const
{
    bool success = true;
    for(const auto& interior_file : i_all_interiors)
    {
        const QFileInfo output_file = replace_dir_and_extension(interior_file, i_out_directory, ".obj");
        success &= export_interior(interior_file.absoluteFilePath(),
                                   output_file.absoluteFilePath(),
                                   ExportFormat::TexturedObj);
    }
    return success;
}

bool InteriorExporter::import_interior(const QString& i_from, InteriorFile& o_interior) const
{
    if(i_from.isEmpty())
        return false;

    std::ifstream file(i_from.toStdString(), std::ios::binary);
    if(!file.good())
        return false;

    InputBinaryStream bis(file);
    bis >> o_interior;
    return true;
}

bool InteriorExporter::import_3d_object(const QString& i_from, Object3d& o_object) const
{
    if(i_from.isEmpty())
        return false;

    std::ifstream file(i_from.toStdString());
    if(!file.good())
        return false;

    o_object.read(file);
    return true;
}

bool InteriorExporter::export_as_text(const QString& i_from, const QString& i_to) const
{
    std::cout << "Exporting as text to " << i_to.toStdString() << std::endl;
    if(i_to.isEmpty())
        return false;

    InteriorFile interior;
    if(!import_interior(i_from, interior))
        return false;

    std::ofstream out_file(i_to.toStdString());
    out_file << interior;
    return true;
}

bool InteriorExporter::export_as_obj(const QString& i_from, const QString& i_to) const
{
    std::cout << "Exporting as obj to " << i_to.toStdString() << std::endl;
    if(i_to.isEmpty())
        return false;

    InteriorFile interior;
    if(!import_interior(i_from, interior))
        return false;

    return export_as_obj(interior, i_to);
}

bool InteriorExporter::export_as_obj(const InteriorFile& i_interior, const QString& i_to) const
{
    if(i_to.isEmpty())
        return false;

    std::ofstream out_file(i_to.toStdString());
    for(const auto& vx : i_interior.vertices.vec)
    {
        out_file << "v " << vx.x << " " << vx.y << " " << vx.z << std::endl;
    }
    for(const auto& poly : i_interior.vertical_polygons.vec)
    {
        out_file << "f ";
        for(int i = 0; i < 4; ++i)
        {
            out_file << poly.ps[i].id + 1 << " ";
        }
        out_file << std::endl;
    }
    for(const auto& poly : i_interior.horizontal_polygons.vec)
    {
        out_file << "f ";
        for(int i = 0; i < 4; ++i)
        {
            out_file << poly.ps[i].id + 1 << " ";
        }
        out_file << std::endl;
    }
    std::cout << "Successfully exported to " << i_to.toStdString() << std::endl;
    return true;
}

bool InteriorExporter::export_as_textured_obj(const QString& i_from, const QString& i_to) const
{
    std::cout << "Exporting as textured obj to " << i_to.toStdString() << std::endl;
    if(i_to.isEmpty())
        return false;

    QString ext = QFileInfo(i_from).suffix().toUpper();
    if(ext == "BIN")
    {
        InteriorFile interior;
        if(!import_interior(i_from, interior))
            return false;

        return export_model_as_textured_obj(interior, i_to);
    }
    if(ext == "3D")
    {
        Object3d object;
        if(!import_3d_object(i_from, object))
            return false;

        return export_model_as_textured_obj(object, i_to);
    }
    return false;
}

template<typename Model>
bool InteriorExporter::export_model_as_textured_obj(const Model& i_model, const QString& i_to) const
{
    if(i_to.isEmpty())
        return false;

    QFileInfo file_info(i_to);
    QString obj_file_name = file_info.baseName();
    QDir obj_file_dir = file_info.dir();

    const auto all_textures = i_model.all_texture_names();

    const Palette palette = Palette::get_palette_by_name(Model::get_textures_palette_name());
    TextureExporter().export_textures(all_textures, palette, obj_file_dir);

    ObjModel model(i_model);
    const auto mtl_file = obj_file_dir.absoluteFilePath(obj_file_name + ".mtl").toStdString();

    model.save(i_to.toStdString(), mtl_file);

    std::cout << "Successfully exported to " << i_to.toStdString() << " MTL " << mtl_file << std::endl;
    return true;
}

InteriorExporter::ExportFormat InteriorExporter::auto_detect_format(const QString& i_file_name) const
{
    return QFileInfo(i_file_name).suffix() == "obj" ?
                InteriorExporter::ExportFormat::TexturedObj :
                InteriorExporter::ExportFormat::Text;
}

QFileInfoList get_interior_files(const QString& i_dir)
{
    return get_files_from_dir_by_mask(i_dir, "*.BIN");
}

template bool InteriorExporter::export_model_as_textured_obj(const InteriorFile&, const QString&) const;
template bool InteriorExporter::export_model_as_textured_obj(const Object3d&, const QString&) const;
