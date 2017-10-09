from texture_builder import TextureBuilder
from texture import Texture
from palette import Palette
import glob, os.path


class Folder:
    def __init__(self, name):
        self.name = name

    def get_texture_files(self):
        ext_list = TextureBuilder.get_texture_extensions()
        return [file for files_with_ext in
                map(lambda ext: glob.glob(os.path.join(Texture.get_textures_folder(), self.name, '*' + ext)), ext_list)
                for file in files_with_ext]

    @staticmethod
    def get_file_stats(texture_path):
        texture = TextureBuilder.get_texture(texture_path)
        header, _ = texture.get_header_and_body()
        wd, ht = texture.get_width_and_height()
        print(texture_path, wd, ht, header[12], header[24], header[28], sep='\t')

    @staticmethod
    def get_output_filename(texture_path, palette_name):
        texture_folder, tex_name = os.path.split(texture_path)
        out_folder = os.path.join(texture_folder, 'png')
        if not os.path.exists(out_folder):
            os.makedirs(out_folder)
        return os.path.join(out_folder, tex_name + '_' + palette_name + '.png')

    def process(self, palette):
        all_textures = self.get_texture_files()
        processed = 0
        if all_textures:
            for texture_path in all_textures:
                cur_tex = TextureBuilder.get_texture(texture_path)
                if cur_tex is None:
                    print('Could not create texture for path', texture_path)
                    continue
                cur_tex.save(self.get_output_filename(texture_path, palette.get_name()), palette=palette)
                processed += 1
                print('{} out of {} processed, {}'.format(processed, len(all_textures),
                                                          str(int(100 * processed / len(all_textures))) + '%'))
