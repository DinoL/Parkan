from binary_file import Binary_file
import numpy as np
import cv2

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