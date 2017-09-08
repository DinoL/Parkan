from texture import Texture

class TextureNgb(Texture):
    def __init__(self, path):
        super().__init__(path)
        print("Created NGB")

    def save(self, id, out_file, palette):
        """To be implemented in derived classes"""
        print("NGB save method call")

    def get_header_and_texture(self):
        """To be implemented in derived classes"""
        print("NGB get_header_and_texture method call")

    def get_width_and_height(self):
        """To be implemented in derived classes"""
        print("NGB get_width_and_height method call")
