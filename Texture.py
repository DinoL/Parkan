import numpy as np
import cv2
import glob, os

class Binary_file:
    def __init__(self, path):
        f = open(path, "r")
        self.seq = np.fromfile(f, dtype=np.uint8)

class Palette(Binary_file):
    def __init__(self, path, shift = 0):
        super().__init__(path)
        self.shift = shift
        self.palette_colors_cnt = 256

        bytes_per_color = 4
        bytes_per_channels = 3
        colors_seq = [self.seq[i: i + bytes_per_channels] for i in
                      range(0, bytes_per_color * self.palette_colors_cnt, bytes_per_color)]
        self.data = np.array(colors_seq).reshape(1, self.palette_colors_cnt, 3)

    def get_shifted_id(self, col_id):
        return (col_id + self.palette_colors_cnt - self.shift) % self.palette_colors_cnt

    def get_color_by_id(self, col_id):
        return list(self.data[0][self.get_shifted_id(col_id)])

    def save(self, out_file):
        cv2.imwrite(out_file, self.data)

class Texture(Binary_file):
    def __init__(self, path):
        super().__init__(path)
        self.header_size = 32

    def save(self, id, out_file, palette):
        _, texture = self.get_header_and_texture()

        pixs = [palette.get_color_by_id(col_id) for col_id in texture]

        wd, ht = self.get_width_and_height()

        cur = 0
        cur_id = 0
        while cur < len(pixs):
            if cur_id == id:
                arr = np.array(pixs[cur: cur + ht * wd]).reshape(ht, wd, 3)
                cv2.imwrite(out_file, arr)
                break
            cur_id += 1
            cur += wd * ht
            wd, ht = wd // 2, ht // 2

    def get_header_and_texture(self):
        return self.seq[:self.header_size], self.seq[self.header_size:]

    @staticmethod
    def bytes_seq_to_int(bytes_seq):
        sum = 0
        for i in range(len(bytes_seq)):
            sum += bytes_seq[i] * (256 ** i)
        return sum

    def get_width_and_height(self):
        header, _ = self.get_header_and_texture()
        return map(self.bytes_seq_to_int, (header[4:8], header[8:12]))

class Folder:
    def __init__(self, name):
        self.name = name

    @staticmethod
    def get_texture_extensions():
        bases = ['A', 'V', 'F', 'W']
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
    def get_output_filename(texture_path):
        texture_folder, tex_name = os.path.split(texture_path)
        out_folder = os.path.join(texture_folder, "png")
        if not os.path.exists(out_folder):
            os.makedirs(out_folder)
        return os.path.join(out_folder, tex_name + ".png")

    def process(self):
        all_textures = self.get_texture_files()
        processed = 0
        if all_textures:
            for texture_path in all_textures:
                cur_tex = Texture(texture_path)
                palette = Palette("PAL.PAL")
                cur_tex.save(0, self.get_output_filename(texture_path), palette=palette)
                processed += 1
                print("{} out of {} processed, {}".format(processed, len(all_textures),
                                                          str(int(100 * processed / len(all_textures))) + "%"))

Folder("TEXTURES.LIB.dir").process()
Palette("PAL.PAL").save("palette.png")

