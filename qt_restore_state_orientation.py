#!/usr/bin/env python

import sys
from python_qt_binding.QtCore import QSettings, Qt
from python_qt_binding.QtGui import QAction, QApplication, QDockWidget, QToolBar, QMainWindow

app = QApplication(sys.argv)

settings = QSettings(QSettings.IniFormat, QSettings.UserScope, 'test', 'test')

mw = QMainWindow()
mw.resize(800, 600)
mw.show()

tb = QToolBar()
tb.setObjectName('toolbar')
mw.addToolBar(tb)

count_dock_widgets = 0

def add_dock_widget(orientation):
    global count_dock_widgets
    count_dock_widgets += 1
    dw = QDockWidget('dockwidget%d' % count_dock_widgets, mw)
    dw.setObjectName('dockwidget%d' % count_dock_widgets)
    mw.addDockWidget(Qt.BottomDockWidgetArea, dw, orientation)

def add_horizontal(self):
    add_dock_widget(Qt.Horizontal)

def add_vertical(self):
    add_dock_widget(Qt.Vertical)

a1 = QAction('add h', tb)
a1.do = add_horizontal
a1.triggered.connect(a1.do)
tb.addAction(a1)

a2 = QAction('add v', tb)
a2.do = add_vertical
a2.triggered.connect(a2.do)
tb.addAction(a2)

def save(self):
    global mw, settings
    settings.setValue('state', mw.saveState())
    print('saved')

def restore(self):
    global mw, settings
    if settings.contains('state'):
        restored = mw.restoreState(settings.value('state'))
        if restored:
            print('restored')
        else:
            print('restore failed')

a3 = QAction('save', tb)
a3.do = save
a3.triggered.connect(a3.do)
tb.addAction(a3)

a4 = QAction('restore', tb)
a4.do = restore
a4.triggered.connect(a4.do)
tb.addAction(a4)

app.exec_()
