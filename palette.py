from binary_file import BinaryFile
import numpy as np
import cv2
import os.path, glob


class Palette(BinaryFile):
    def __init__(self, path):
        super().__init__(path)
        self.palette_colors_cnt = 256
        self.channels_cnt = 4
        self.used_channels_cnt = 3
        self.bytes_per_channel = 1
        self.name = os.path.basename(path)

        bytes_per_color = self.channels_cnt * self.bytes_per_channel
        bytes_per_used_channels = self.used_channels_cnt * self.bytes_per_channel
        self.data = [self.seq[i: i + bytes_per_used_channels] for i in
                     range(0, bytes_per_color * self.palette_colors_cnt, bytes_per_color)]

    def get_color_by_id(self, col_id):
        return self.data[col_id]

    def get_used_channels_cnt(self):
        return self.used_channels_cnt

    def get_name(self):
        return self.name

    def save(self, out_file):
        arr = [self.get_color_by_id(col_id) for col_id in range(self.palette_colors_cnt)]
        cv2.imwrite(out_file, np.array(arr).reshape(1, self.palette_colors_cnt, 3))

    def apply(self, texture):
        return [self.get_color_by_id(col_id) for col_id in texture]

    @staticmethod
    def get_palette_extensions():
        return ['PAL', 'COL']

    @staticmethod
    def get_palettes_folder():
        return 'palettes'

    @staticmethod
    def get_palette_files():
        ext_list = Palette.get_palette_extensions()
        return [file for files_with_ext in
                map(lambda ext: glob.glob(os.path.join(Palette.get_palettes_folder(), "*." + ext)), ext_list)
                for file in files_with_ext]

    @staticmethod
    def process_all_palettes():
        all_palettes = Palette.get_palette_files()
        for palette_path in all_palettes:
            cur_pal = Palette(palette_path)
            cur_pal.save(palette_path + '.png')

    @staticmethod
    def get_abs_path(rel_path):
        return os.path.join(Palette.get_palettes_folder(), rel_path)