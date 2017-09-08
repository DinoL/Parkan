from texture import Texture

class TextureDib(Texture):
    def __init__(self, path):
        super().__init__(path)
        print("Created DIB")

    def save(self, id, out_file, palette):
        """To be implemented in derived classes"""
        print("DIB save method call")