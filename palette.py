from binary_file import Binary_file
import utils
import numpy as np
import cv2
import os.path

class Palette(Binary_file):
    def __init__(self, name, shift = 0):
        path = os.path.join(utils.get_palettes_folder(), name)
        super().__init__(path)
        self.shift = shift
        self.palette_colors_cnt = 256
        self.channels_cnt = 4
        self.used_channels_cnt = 3
        self.bytes_per_channel = 1
        self.name = os.path.basename(path)

        bytes_per_color = self.channels_cnt * self.bytes_per_channel
        bytes_per_used_channels = self.used_channels_cnt * self.bytes_per_channel
        colors_seq = [self.seq[i: i + bytes_per_used_channels] for i in
                      range(0, bytes_per_color * self.palette_colors_cnt, bytes_per_color)]
        self.data = np.array(colors_seq).reshape(1, self.palette_colors_cnt, self.used_channels_cnt)

    def get_shifted_id(self, col_id):
        return (col_id + self.palette_colors_cnt - self.shift) % self.palette_colors_cnt

    def get_color_by_id(self, col_id):
        return list(self.data[0][self.get_shifted_id(col_id)])

    def get_used_channels_cnt(self):
        return self.used_channels_cnt

    def get_name(self):
        return self.name

    def save(self, out_file):
        cv2.imwrite(out_file, self.data)

    @staticmethod
    def get_palette_extensions():
        return ['PAL', 'COL']