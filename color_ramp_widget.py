from PyQt5.QtGui import QColor, QPainter
from PyQt5.QtWidgets import QWidget


class ColorRampWidget(QWidget):
    def __init__(self, palette):
        super(ColorRampWidget, self).__init__()
        self.palette = palette
        self.initUI()

    def initUI(self):
        self.setGeometry(300, 300, 350, 350)
        self.setWindowTitle(self.palette.get_name())
        self.show()

    def paintEvent(self, e):
        qp = QPainter()
        qp.begin(self)
        self.draw_rectangles(qp)
        qp.end()

    def draw_rectangles(self, qp):
        cnt = self.palette.palette_colors_cnt
        wd = 20
        ht = 20
        col_per_row = 16
        hor_padding, vert_padding = 5, 5
        for col_id in range(cnt):
            row, column = divmod(col_id, col_per_row)
            b, g, r = self.palette.get_color_by_id(col_id)
            cur_col = QColor(r, g, b)
            qp.setBrush(cur_col)
            qp.drawRect(hor_padding + column * wd, vert_padding + row * ht, wd, ht)