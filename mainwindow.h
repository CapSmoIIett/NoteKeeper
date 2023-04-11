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

#include "calendar.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void PrintCalendar (int month = 0, int year = 0);

public slots:
    void OnBtnNextClick();
    void OnBtnBackClick();

private:
    QHBoxLayout* CreateCtrlPanel();
    QGridLayout* CreateCalendar();

private slots:
    void OnCustomMenuRequested();


private:
    Ui::MainWindow *ui;
    CalendarCtrl Ctrl;

    QMenuBar* p_MenuBar;
    QToolBar* p_QToolBar;

    QVector<QFrame*> v_Calendar;

    QLabel* l_Date;
    QPushButton *b_Back;
    QPushButton *b_Next;

    QVBoxLayout* p_MainLayout;
};



#endif // MAINWINDOW_H
