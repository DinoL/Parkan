from texture import Texture
from palette import Palette
import glob, os

class Folder:
    def __init__(self, name):
        self.name = name

    @staticmethod
    def get_texture_extensions():
        bases = ['A', 'V']
        singles = ['DIB', 'NGB', 'F', 'W']
        animated_files = [base + str(x) for base in bases for x in range(1, 10)]
        return bases + animated_files

    def get_texture_files(self):
        ext_list = self.get_texture_extensions()
        return [file for files_with_ext in map(lambda ext: glob.glob(os.path.join(self.name, "*." + ext)), ext_list) for file in files_with_ext]

    @staticmethod
    def get_file_stats(texture_path):
        texture = Texture(texture_path)
        header, _ = texture.get_header_and_texture()
        wd, ht = texture.get_width_and_height()
        print(texture_path, wd, ht, header[12], header[24], header[28], sep='\t')

    @staticmethod
    def get_output_filename(texture_path, palette_name):
        texture_folder, tex_name = os.path.split(texture_path)
        out_folder = os.path.join(texture_folder, "png")
        if not os.path.exists(out_folder):
            os.makedirs(out_folder)
        return os.path.join(out_folder, tex_name + "_" + palette_name + ".png")

    def process(self, palette_path):
        all_textures = self.get_texture_files()
        processed = 0
        if all_textures:
            for texture_path in all_textures:
                cur_tex = Texture(texture_path)
                palette = Palette(palette_path, shift=0)
                cur_tex.save(0, self.get_output_filename(texture_path, palette.get_name()), palette=palette)
                processed += 1
                print("{} out of {} processed, {}".format(processed, len(all_textures),
                                                          str(int(100 * processed / len(all_textures))) + "%"))