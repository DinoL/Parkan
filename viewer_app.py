from palette import Palette
from texture_builder import TextureBuilder
from texture import Texture
from palette import Palette
import os.path
from functools import partial

from PyQt5.QtCore import QDir
from PyQt5.QtGui import QImage, QPalette, QPixmap
from PyQt5.QtWidgets import (QAction, QFileDialog, QLabel,
        QMainWindow, QMenu, QScrollArea, QSizePolicy)
from color_ramp_widget import ColorRampWidget


class ViewerApp(QMainWindow):
    def __init__(self):
        super(ViewerApp, self).__init__()

        self.name = 'Parkan Image Viewer'

        self.scale_factor = 0.0
        self.scale_step = 0.25
        self.min_zoom = 0.333
        self.max_zoom = 3

        self.init_window_elements()

        self.setWindowTitle(self.name)
        self.resize(500, 400)
        self.palette = None
        self.last_image = None
        self.palette_window = None

    def init_window_elements(self):
        self.create_image_label()
        self.create_scroll_area()
        self.create_actions()
        self.create_menus()

    def create_scroll_area(self):
        scroll_area = QScrollArea()
        scroll_area.setBackgroundRole(QPalette.Dark)
        if not self.image_label:
            raise 'Image label not initialized!'

        scroll_area.setWidget(self.image_label)
        self.setCentralWidget(scroll_area)
        self.scroll_area = scroll_area

    def create_image_label(self):
        label = QLabel()
        label.setBackgroundRole(QPalette.Base)
        label.setSizePolicy(QSizePolicy.Ignored, QSizePolicy.Ignored)
        label.setScaledContents(True)
        self.image_label = label

    def open(self):
        file_name, _ = QFileDialog.getOpenFileName(self, 'Open image', os.path.join(QDir.currentPath(), Texture.get_textures_folder()))
        if file_name and self.palette:
            self.last_image = TextureBuilder().get_texture(file_name)
            self.scale_factor = 1.0
            self.update_image()
            self.update_actions()

    def choose_palette(self, palette_file):
        if palette_file:
            self.palette = Palette(palette_file)
            self.update_image()
            self.update_actions()
            self.palette_window = ColorRampWidget(self.palette)

    def update_image(self):
        if not self.last_image:
            return

        image_data = self.last_image.get_pixels(self.palette)
        ht, wd, channels = image_data.shape
        image = QImage(image_data, wd, ht, channels * wd, QImage.Format_RGB888)
        if not image.isNull():
            image = image.rgbSwapped()
            self.image_label.setPixmap(QPixmap.fromImage(image))
            self.fit_to_window_act.setEnabled(True)
            if not self.fit_to_window_act.isChecked():
                self.image_label.adjustSize()

    def zoom_in(self):
        self.scale_image(1 + self.scale_step)

    def zoom_out(self):
        self.scale_image(1 / (1 + self.scale_step))

    def normal_size(self):
        self.image_label.adjustSize()
        self.scale_factor = 1.0

    def fit_to_window(self):
        fit_to_window = self.fit_to_window_act.isChecked()
        self.scroll_area.setWidgetResizable(fit_to_window)
        if not fit_to_window:
            self.normal_size()

        self.update_actions()

    def create_choose_palette_action(self, palette_file):
        return QAction(os.path.basename(palette_file), self,
                       enabled=True, triggered=partial(self.choose_palette, palette_file))

    def create_actions(self):
        self.open_act = QAction('&Open image...', self, shortcut='Ctrl+O',
                                enabled=False, triggered=self.open)

        self.choose_palette_act_dict = {os.path.basename(palette_file): self.create_choose_palette_action(palette_file)
                                        for palette_file in Palette.get_palette_files()}

        self.exit_act = QAction('E&xit', self, shortcut='Ctrl+Q',
                                triggered=self.close)

        self.zoom_in_act = QAction('Zoom &In ({}%)'.format(int(100*self.scale_step)), self, shortcut='Ctrl++',
                                   enabled=False, triggered=self.zoom_in)

        self.zoom_out_act = QAction('Zoom &Out ({}%)'.format(int(100*self.scale_step)), self, shortcut='Ctrl+-',
                                    enabled=False, triggered=self.zoom_out)

        self.normal_size_act = QAction('&Normal Size', self, shortcut='Ctrl+N',
                                       enabled=False, triggered=self.normal_size)

        self.fit_to_window_act = QAction('&Fit to Window', self, enabled=False,
                                         checkable=True, shortcut='Ctrl+F', triggered=self.fit_to_window)

        self.save_single_image_act = QAction('&Save image', self, enabled=False,
                                             shortcut='Ctrl+S', triggered=self.save_single_image)

    def create_menus(self):
        self.fileMenu = QMenu("&File", self)
        self.fileMenu.addAction(self.open_act)
        self.fileMenu.addAction(self.save_single_image_act)

        choose_palette_menu = self.fileMenu.addMenu('&Choose Palette')
        for palette_file, choose_palette_action in self.choose_palette_act_dict.items():
            choose_palette_menu.addAction(choose_palette_action)

        self.fileMenu.addSeparator()
        self.fileMenu.addAction(self.exit_act)

        self.viewMenu = QMenu("&View", self)
        self.viewMenu.addAction(self.zoom_in_act)
        self.viewMenu.addAction(self.zoom_out_act)
        self.viewMenu.addAction(self.normal_size_act)
        self.viewMenu.addSeparator()
        self.viewMenu.addAction(self.fit_to_window_act)

        self.menuBar().addMenu(self.fileMenu)
        self.menuBar().addMenu(self.viewMenu)

    def update_actions(self):
        self.open_act.setEnabled(self.palette is not None)
        self.zoom_in_act.setEnabled(not self.fit_to_window_act.isChecked())
        self.zoom_out_act.setEnabled(not self.fit_to_window_act.isChecked())
        self.normal_size_act.setEnabled(not self.fit_to_window_act.isChecked())
        self.save_single_image_act.setEnabled(self.last_image is not None)

    def save_single_image(self):
        if not self.last_image or not self.palette:
            return

        file_name, _ = QFileDialog.getSaveFileName(self, 'Save image',
                                                   os.path.join(QDir.currentPath(), Texture.get_textures_folder()),
                                                   filter='*.png;;*.bmp')
        if not file_name:
            return

        self.last_image.save(file_name, self.palette)

    def scale_image(self, factor):
        self.scale_factor *= factor
        self.image_label.resize(self.scale_factor * self.image_label.pixmap().size())

        self.adjust_scroll_bar(self.scroll_area.horizontalScrollBar(), factor)
        self.adjust_scroll_bar(self.scroll_area.verticalScrollBar(), factor)

        self.zoom_in_act.setEnabled(self.scale_factor < self.max_zoom)
        self.zoom_out_act.setEnabled(self.scale_factor > self.min_zoom)

    def adjust_scroll_bar(self, scroll_bar, factor):
        scroll_bar.setValue(int(factor * scroll_bar.value()
                                + ((factor - 1) * scroll_bar.pageStep() / 2)))
