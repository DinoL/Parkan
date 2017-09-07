import numpy as np
import cv2
import glob, os

class Binary_file:
    def __init__(self, path):
        f = open(path, "r")
        self.seq = np.fromfile(f, dtype=np.uint8)

class Palette(Binary_file):
    def __init__(self, path):
        super().__init__(path)
        self.palette_colors_cnt = 256

        bytes_per_color = 4
        bytes_per_channels = 3
        colors_seq = [self.seq[i: i + bytes_per_channels] for i in
                      range(0, bytes_per_color * self.palette_colors_cnt, bytes_per_color)]
        self.data = np.array(colors_seq).reshape(1, self.palette_colors_cnt, 3)

    def get_color_by_id(self, col_id, shift = 0):
        return list(self.data[0][(col_id + self.palette_colors_cnt - shift) % self.palette_colors_cnt])

class Texture(Binary_file):
    def __init__(self, path):
        super().__init__(path)
        self.header_size = 32

    def save(self, id, out_file, palette):
        _, texture = self.get_header_and_texture()

        shift = 0
        pixs = [palette.get_color_by_id(col_id, shift=shift) for col_id in texture]

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

    def get_texture_extensions(self):
        return ['A', 'A4']

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
        file_name = os.path.splitext(tex_name)[0]
        out_folder = os.path.join(texture_folder, "png")
        if not os.path.exists(out_folder):
            os.makedirs(out_folder)
        return os.path.join(out_folder, file_name + ".png")

    def process(self):
        for texture_path in self.get_texture_files():
            cur_tex = Texture(texture_path)
            palette = Palette("PAL.PAL")
            cur_tex.save(0, self.get_output_filename(texture_path), palette=palette)

folder = Folder("Korob")
folder.process()

