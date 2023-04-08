#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QMenuBar>
#include <QToolBar>
#include <QGridLayout>
#include <QFrame>
#include <QLabel>
#include <QPushButton>

#include <QVector>
#include <QString>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QMenuBar* p_MenuBar;
    QToolBar* p_QToolBar;
};
#endif // MAINWINDOW_H
