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
#include <QTextEdit>

#include <QVector>
#include <QString>

#include "calendar.h"
#include "frameclickable.h"
#include "notedlg.h"
#include "database.h"
#include "elidedlabel.h"

#define INDEX_DATE 0
#define INDEX_NOTE 1

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

    void ClearNotes();

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

    Database* db;

};



#endif // MAINWINDOW_H
