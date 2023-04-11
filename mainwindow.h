#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QMenuBar>
#include <QToolBar>
#include <QGridLayout>
#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QClipboard>
#include <QTextBlock>
#include <QSpacerItem>

#include <QVector>
#include <QString>

#include "calendar.h"
#include "frameclickable.h"


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

    void OnCustomMenuRequested(QPoint pos, int numberOfCell);
    void OnCopyDateToClipborad(int numberOfCell);

    void OnAddNote(QPoint pos, int numberOfCell);

private:
    QHBoxLayout* CreateCtrlPanel();
    QGridLayout* CreateCalendar();

    bool eventFilter(QObject* o, QEvent* e);

private:
    Ui::MainWindow *ui;
    CalendarCtrl Ctrl;

    QMenuBar* p_MenuBar;
    QToolBar* p_QToolBar;

    QVector<FrameClickable*> v_Calendar;

    QLabel* l_Date;
    QPushButton *b_Back;
    QPushButton *b_Next;

    QVBoxLayout* p_MainLayout;
};



#endif // MAINWINDOW_H
