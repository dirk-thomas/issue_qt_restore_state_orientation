#include <QtCore/QSettings>

#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QLabel>
#include <QtGui/QToolBar>
#include <QtGui/QMainWindow>

#include "qt_restore_state_orientation.h"

/*
 * Steps to reproduce issue:
 * - start application
 * - click "add horizontal"
 * - click "add horizontal"
 * - click "add vertical"
 * - click "add horizontal"
 * ... the layout will look like this:
 *     11 22 44
 *     33333 44
 * - click "save state"
 * - close application
 *
 * - start application
 * - click "add vertical" 5 times
 * ... the layout will look like this:
 *     11 
 *     22
 *     33
 *     44
 *     55
 * - click "restore state"
 * ... the layout will look like this:
 *     11 22 44 55
 *     33333 44 55
 *
 * BUT since 5 was not known before I would expect its orientation
 * (vertical) to not change by the restoreState invocation
 * ... the layout should look like this:
 *     11 22 44
 *     33333 44
 *     55555555
 */
int main(int argc, char** argv)
{
    QApplication* app = new QApplication(argc, argv);
    QSettings* settings = new QSettings(QSettings::IniFormat, QSettings::UserScope, "qt_restore_state_orientation", "qt_restore_state_orientation");
    QMainWindow* mw = new QMainWindow();
    mw->resize(800, 600);

    mw->setCentralWidget(new QLabel("foo"));

    QToolBar* tb = new QToolBar();
    tb->setObjectName("toolbar");
    mw->addToolBar(tb);

    QAction* aha = new AddHorizontalAction("add horizontal", tb);
    tb->addAction(aha);
    QAction* ava = new AddVerticalAction("add vertical", tb);
    tb->addAction(ava);

    QAction* ss = new SaveStateAction("save state", tb, settings);
    tb->addAction(ss);
    QAction* rs = new RestoreStateAction("restore state", tb, settings);
    tb->addAction(rs);

    mw->show();

    app->exec();
}
