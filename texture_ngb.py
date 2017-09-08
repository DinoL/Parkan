from texture import Texture

class TextureNgb(Texture):
    def __init__(self, path):
        super().__init__(path)
        print("Created NGB")

    def save(self, id, out_file, palette):
        """To be implemented in derived classes"""
        print("NGB save method call")