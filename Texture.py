from binary_file import Binary_file
import numpy as np
import cv2

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