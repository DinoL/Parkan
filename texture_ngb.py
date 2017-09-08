from texture import Texture

class TextureNgb(Texture):
    def __init__(self, path):
        super().__init__(path)
        self.header_size = 16

    def save(self, id, out_file, palette):
        """To be implemented in derived classes"""
        print("NGB save method call")

    def get_header_and_texture(self):
        return self.seq[:self.header_size], self.seq[self.header_size:]

    def get_width_and_height(self):
        wd = self.seq[4] - self.seq[0] + 1
        ht = self.seq[6] - self.seq[2] + 1
        return wd, ht
