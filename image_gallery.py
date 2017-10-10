from PyQt5.QtWidgets import QLabel, QDialog, QGridLayout


class ImageGallery(QDialog):

    def __init__(self, parent=None):
        super(QDialog, self).__init__(parent)
        self.setWindowTitle('Image Gallery')
        self.setLayout(QGridLayout(self))

    def populate(self, images, height, images_per_row = 4):
        for pic_num, pixmap in enumerate(images):
            label = QLabel()
            label.setPixmap(pixmap.scaledToHeight(height))
            row, col = divmod(pic_num, images_per_row)
            self.layout().addWidget(label, row, col)