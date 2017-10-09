from PyQt5.QtWidgets import QApplication
from viewer_app import ViewerApp

if __name__ == '__main__':
    import sys

    app = QApplication(sys.argv)
    image_viewer = ViewerApp()
    image_viewer.show()
    sys.exit(app.exec_())
