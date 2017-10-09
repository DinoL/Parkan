class ChannelsConverter:
    @staticmethod
    def convert_bgr_to_rgb(texture):
        for line in texture:
            for pix in line:
                pix[0], pix[2] = pix[2], pix[0]
        return texture