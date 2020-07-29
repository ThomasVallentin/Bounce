from PySide2 import QtWidgets


class RenderItem(QtWidgets.QGraphicsPixmapItem):
    def __init__(self, ):
        super(RenderItem, self).__init__()


class RenderScene(QtWidgets.QGraphicsScene):
    def __init__(self, parent=None):
        super(RenderScene, self).__init__(parent=parent)


class RenderView(QtWidgets.QGraphicsView):
    def __init__(self, parent=None):
        super(RenderView, self).__init__(parent=parent)
        scene = RenderScene()
        self.setScene(scene)

        self.setSceneRect(0,0, 500, 500)