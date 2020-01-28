STYLESHEET = """
QWidget{
    background-color: #353535;
    color: #aaaaaa;
    border: none;
    border-radius: 2px;
}

QMenu::item:selected {
    background: rgba(100, 100, 100, 150);
}

QMenuBar::item {
    background: transparent;
}

QMenuBar::item:selected {
    background: #707070;
    color: #cccccc;
}

QMenuBar::item:pressed {
    background: #aaaaaa;
    color: #eeeeee;
}

/* --  SCROLL BAR  -------------------------------------------------------------------------------------------------- */

QScrollBar {
    border: 1px solid #404040;
    border-radius: 4px;
    background-color: #202020;
}
QScrollBar:horizontal {
    height: 16px;
    margin: 2px 16px 2px 16px;
}
QScrollBar:vertical {
    width: 16px;
    margin: 16px 2px 16px 2px;
}

QScrollBar::handle {
    background-color: #757575;
    border: 1px solid #323232;
    border-radius: 4px;
    min-width: 8px;
    min-height: 8px;
}
QScrollBar::handle:hover {
    background-color: #909090;
}
QScrollBar::handle:pressed {
    border: 1px solid #151515;
}

QScrollBar::add-line:horizontal {
    margin: 0px 5px 0px 0px;
    height: 8px;
    width: 8px;
    border-image: url("ressources/icons/chevron-right.png");
    subcontrol-position: right;
    subcontrol-origin: margin;
}
QScrollBar::add-line:horizontal:hover, QScrollBar::add-line:horizontal:pressed {
    border-image: url("ressources/icons/chevron-right-pressed.png");
}
QScrollBar::add-line:vertical {
    margin: 5px 0px 0px 0px;
    height: 8px;
    width: 8px;
    border-image: url("ressources/icons/chevron-up.png");
    subcontrol-position: top;
    subcontrol-origin: margin;
}
QScrollBar::add-line:vertical:hover, QScrollBar::add-line:vertical:pressed {
    border-image: url("ressources/icons/chevron-up-pressed.png");
}
QScrollBar::sub-line:horizontal {
    margin: 0px 0px 0px 5px;
    height: 8px;
    width: 8px;
    border-image: url("ressources/icons/chevron-left.png");
    subcontrol-position: left;
    subcontrol-origin: margin;
}

QScrollBar::sub-line:horizontal:hover, QScrollBar::sub-line:horizontal:pressed {
    border-image: url("ressources/icons/chevron-left-pressed.png");
}
QScrollBar::sub-line:vertical {
    margin: 0px 0px 5px 0px;
    height: 8px;
    width: 8px;
    border-image: url("ressources/icons/chevron-down.png");
    subcontrol-position: bottom;
    subcontrol-origin: margin;
}
QScrollBar::sub-line:vertical:hover, QScrollBar::sub-line:vertical:pressed {
    border-image: url("ressources/icons/chevron-down-pressed.png");
}

QScrollBar::add-page, QScrollBar::sub-page {
    background: none;
}


/* --  SPLITTER  ---------------------------------------------------------------------------------------------------- */

QSplitter{
    border: 1px solid #202020;
}
QSplitter::handle {
    background-color: rgba(0,0,0, 45);
    border-radius: 3px;
    spacing: 0px;
    padding: 1px;
    margin: 5px 2px 5px 2px;
}

QSplitter::handle:horizontal{
    width:5px;
    image: url("ressources/icons/splitter-handle.png");
}
QSplitter::handle:horizontal:pressed{
    image: url("ressources/icons/splitter-handle-pressed.png");
}


"""
