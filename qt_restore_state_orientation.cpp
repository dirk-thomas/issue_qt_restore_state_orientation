#include <iostream>

#include "qt_restore_state_orientation.h"


QDockWidget* createDockWidget(QWidget* parent)
{
    static uint count = 0;
    count++;
    QString name = "dockwidget_" + QString::number(count);
    QDockWidget* dw = new QDockWidget(name, parent);
    dw->setObjectName(name);
    return dw;
}


AddHorizontalAction::AddHorizontalAction(const QString& title, QWidget* parent)
    : QAction(title, parent)
{
    connect(this, SIGNAL(triggered()), this, SLOT(addHorizontal()));
}

void AddHorizontalAction::addHorizontal()
{
    QDockWidget* dw = createDockWidget(dynamic_cast<QMainWindow*>(parent()->parent()));
    dynamic_cast<QMainWindow*>(parent()->parent())->addDockWidget(Qt::BottomDockWidgetArea, dw, Qt::Horizontal);
}


AddVerticalAction::AddVerticalAction(const QString& title, QWidget* parent)
    : QAction(title, parent)
{
    connect(this, SIGNAL(triggered()), this, SLOT(addVertical()));
}

void AddVerticalAction::addVertical()
{
    QDockWidget* dw = createDockWidget(dynamic_cast<QMainWindow*>(parent()->parent()));
    dynamic_cast<QMainWindow*>(parent()->parent())->addDockWidget(Qt::BottomDockWidgetArea, dw, Qt::Vertical);
}


SaveStateAction::SaveStateAction(const QString& title, QWidget* parent, QSettings* settings)
    : QAction(title, parent)
    , settings(settings)
{
    connect(this, SIGNAL(triggered()), this, SLOT(saveState()));
}

void SaveStateAction::saveState()
{
    settings->setValue("state", dynamic_cast<QMainWindow*>(parent()->parent())->saveState());
    std::cout << "saved state" << std::endl;
}


RestoreStateAction::RestoreStateAction(const QString& title, QWidget* parent, QSettings* settings)
    : QAction(title, parent)
    , settings(settings)
{
    connect(this, SIGNAL(triggered()), this, SLOT(restoreState()));
}

void RestoreStateAction::restoreState()
{
    if (settings->contains("state"))
    {
        bool restored = dynamic_cast<QMainWindow*>(parent()->parent())->restoreState(settings->value("state").toByteArray());
        if (restored)
        {
            std::cout << "restored state" << std::endl;
        }
        else
        {
            std::cout << "restoring state failed" << std::endl;
        }
    }
    else
    {
        std::cout << "no saved state available" << std::endl;
    }
}
