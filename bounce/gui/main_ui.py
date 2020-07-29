from PySide2 import QtWidgets

from .components import render_view
from .constants import *


class BounceMainWindow(QtWidgets.QMainWindow):
    def __init__(self):
        super(BounceMainWindow, self).__init__()
        self.setStyleSheet(STYLESHEET)
        self.setup_ui()

    def setup_ui(self):
        self.main_splitter = QtWidgets.QSplitter(self)
        self.setCentralWidget(self.main_splitter)

        self.viewport = QtWidgets.QOpenGLWidget(self)
        self.main_splitter.addWidget(self.viewport)

        self.render_view = render_view.RenderView(self)
        self.main_splitter.addWidget(self.render_view)

        self.render_options_widget = QtWidgets.QListView()
        self.main_splitter.addWidget(self.render_options_widget)

        self.setMenuBar(QtWidgets.QMenuBar(self))
        self.setup_main_menus()

    def setup_main_menus(self):
        self.files_menu = QtWidgets.QMenu("Files", self)
        self.files_menu.addAction("New")
        self.files_menu.addAction("Open")
        self.files_menu.addAction("Open Recent")
        self.files_menu.addSeparator()
        self.files_menu.addAction("Save")
        self.files_menu.addAction("Save As")

        self.menuBar().addMenu(self.files_menu)