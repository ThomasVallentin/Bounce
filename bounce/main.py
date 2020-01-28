import sys
from PySide2 import QtWidgets

from gui import main_ui


def main(argv=sys.argv[1:]):
    app = QtWidgets.QApplication(argv)
    ui = main_ui.BounceMainWindow()
    ui.show()
    return app.exec_()


if __name__ == '__main__':
    main()
