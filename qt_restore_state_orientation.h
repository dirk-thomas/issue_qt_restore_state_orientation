#include <QtCore/QSettings>

#include <QtGui/QAction>
#include <QtGui/QDockWidget>
#include <QtGui/QMainWindow>


QDockWidget* createDockWidget(QWidget* parent);


class AddHorizontalAction : public QAction
{
    Q_OBJECT
public:
    AddHorizontalAction(const QString& title, QWidget* parent);
public slots:
    void addHorizontal();
};


class AddVerticalAction : public QAction
{
    Q_OBJECT
public:
    AddVerticalAction(const QString& title, QWidget* parent);
public slots:
    void addVertical();
};


class SaveStateAction : public QAction
{
    Q_OBJECT
public:
    SaveStateAction(const QString& title, QWidget* parent, QSettings* settings);
public slots:
    void saveState();
private:
    QSettings* settings;
};


class RestoreStateAction : public QAction
{
    Q_OBJECT
public:
    RestoreStateAction(const QString& title, QWidget* parent, QSettings* settings);
public slots:
    void restoreState();
private:
    QSettings* settings;
};
