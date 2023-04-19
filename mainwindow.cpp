#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "stylesheets.h"

//
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //ui->setupUi(this);

    /*****************************************************
     * Configure window
     */

    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("NoteKeeper"));

    this->resize(640, 400);


    /*****************************************************
     * Configure database
     */

    db = new Database;

    menuBar()->addMenu("File");
    //p_MenuBar = new QMenuBar(this);
    //p_QToolBar = new QToolBar(this);


    auto ctrlPanel = CreateCtrlPanel();

    /*****************************************************
     * Configure main Layout
     */
    p_MainLayout = new QVBoxLayout;
    p_MainLayout->addLayout(ctrlPanel, 1);

    QWidget *widget = new QWidget();
    widget->setLayout(p_MainLayout);
    setCentralWidget(widget);

    //this->layout()->addWidget(p_MainLayout->widget());
    //setLayout(p_verticalLayout);


    /*****************************************************
     * Create calendar
     */
    QGridLayout* calendar =  CreateCalendar();
    p_MainLayout->addLayout(calendar);


    /*****************************************************
     * Connecting
     */

    connect(b_Next, &QPushButton::clicked, this, &MainWindow::OnBtnNextClick);
    connect(b_Back, &QPushButton::clicked, this, &MainWindow::OnBtnBackClick);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QHBoxLayout* MainWindow::CreateCtrlPanel()
{
    /*****************************************************
     * Configure buttons
     */

    l_Date = new QLabel(Ctrl.GetMonthName(Ctrl.GetWorkMonth()) + " " + QString::number(Ctrl.GetWorkYear()));
    l_Date->setAlignment(Qt::AlignCenter);
    l_Date->setMaximumHeight(40);
    l_Date->setFixedWidth(400);
    //l_date->setStyleSheet(LABELDATE_STYLE);


    /*****************************************************
     * Configure buttons
     */

    b_Back = new QPushButton("<");

    b_Back->setMaximumHeight(40);
    b_Back->setMaximumWidth(60);
    b_Back->setShortcut(QKeySequence(Qt::Key_Left));
    b_Back->setToolTip("Go to the previous month, press ctrl to move to the previous year");
    b_Back->setStyleSheet(BUTTON_STYLE);


    b_Next = new QPushButton(">");

    b_Next->setMaximumWidth(60);
    b_Next->setMaximumHeight(40);
    b_Next->setShortcut(QKeySequence(Qt::Key_Right));
    b_Next->setToolTip("Go to the next month, press ctrl to move to the next year");
    b_Next->setStyleSheet(BUTTON_STYLE);


    /*****************************************************
     * Add elements in layout
     */

    QHBoxLayout *p_horizontalLayout = new QHBoxLayout;
    p_horizontalLayout->addWidget(b_Back, 1, Qt::AlignRight);
    p_horizontalLayout->addWidget(l_Date, 1, Qt::AlignCenter);
    p_horizontalLayout->addWidget(b_Next, 1, Qt::AlignLeft);

    return p_horizontalLayout;
}

QGridLayout* MainWindow::CreateCalendar()
{
    //Create 7x7 grid
    QGridLayout *grid_layout = new QGridLayout;

    // Create header
    for (int i = 0; i < CalendarCtrl::v_daysOfWeek.size(); i++)
    {
        FrameClickable *frame = new FrameClickable;
        frame->setMinimumHeight(50);//frame->setFixedHeight(50);
        frame->setMinimumWidth(125);

        QHBoxLayout *hl = new QHBoxLayout;
        hl->setAlignment(Qt::AlignCenter);

        QLabel* l_name = new QLabel(CalendarCtrl::GetDayOfWeekName(i));

        hl->addWidget(l_name);
        frame->setLayout(hl);
        frame->setObjectName("header");
        frame->setStyleSheet(CELL_STYLE);
        grid_layout->addWidget(frame, 0, i);
    }

    //create cells
    for (auto i = 0; i < 42; i++ )
    {
        FrameClickable *frame = new FrameClickable;
        frame->setMinimumHeight(75);
        frame->setMinimumWidth(125);

        QVBoxLayout *vl = new QVBoxLayout;
        vl->setAlignment(Qt::AlignTop | Qt::AlignLeft);

        QLabel* l_date = new QLabel(QString::number(i + 1));

        //text->setStyleSheet(TEXT_FIELD);

        vl->addWidget(l_date);
        frame->setLayout(vl);
        frame->setStyleSheet(CELL_STYLE);

        frame->setContextMenuPolicy(Qt::CustomContextMenu);
        //frame->setC
        connect(frame, &QFrame::customContextMenuRequested, this, [i, this](QPoint pos) {OnCustomMenuRequested (pos, i);});
        connect(frame, &FrameClickable::DoubleClick, this, [i, this](QMouseEvent* event) {OnAddNote(event->pos(), i);});

        v_Calendar.push_back(frame);

        grid_layout->addWidget(frame, i / 7 + 1, i % 7);
    }

    /*****************************************************
     * Print calendar
     */

    auto dates = Ctrl.GetWorkMonthDates();

    auto notes = db->GetNotes(dates);

    // colored adn insert labels
    for (int i = 0; i < dates.size(); i++)
    {
        if (dates[i].day == 0)
        {
            // hide row if we need only 5 rows
            v_Calendar[i]->hide();
            continue;
        }
        if (v_Calendar[i]->layout()->count() > 0)
        {
            auto dateLabel = v_Calendar[i]->layout()->itemAt(INDEX_DATE)->widget();
            dynamic_cast<QLabel*>(dateLabel)->setText(QString::number(dates[i].day));

            if (Ctrl.GetDateInt(dates[i]) < Ctrl.GetCurDateInt())
                v_Calendar[i]->setObjectName("past");
            else if (Ctrl.GetDateInt(dates[i]) > Ctrl.GetCurDateInt())
                v_Calendar[i]->setObjectName("future");
            else
                v_Calendar[i]->setObjectName("today");

            v_Calendar[i]->setStyleSheet(CELL_STYLE);

            if (!notes[i].isEmpty())
            {
                ElidedLabel* l_text = new ElidedLabel();
                QString text = notes[i];
                l_text->setText(text);
                v_Calendar[i]->layout()->addWidget(l_text);
            }
        }
    }

    return grid_layout;
}

void MainWindow::PrintCalendar (int month, int year)
{
    auto dates= Ctrl.GetWorkMonthDates();

    for (int i = 0; i < dates.size(); i++)
    {
        if (dates[i].day == 0)
        {
            // hide row if we need only 5 rows
            v_Calendar[i]->hide();
            continue;
        }
        else if (v_Calendar[i]->isHidden())
            v_Calendar[i]->show();

        if (v_Calendar[i]->layout()->count() > 0)
        {
            auto dateLabel = v_Calendar[i]->layout()->itemAt(INDEX_DATE)->widget();
            dynamic_cast<QLabel*>(dateLabel)->setText(QString::number(dates[i].day));

            if (Ctrl.GetDateInt(dates[i]) < Ctrl.GetCurDateInt())
                v_Calendar[i]->setObjectName("past");
            else if (Ctrl.GetDateInt(dates[i]) > Ctrl.GetCurDateInt())
                v_Calendar[i]->setObjectName("future");
            else
                v_Calendar[i]->setObjectName("today");

            v_Calendar[i]->setStyleSheet(CELL_STYLE);
        }
    }
}

void MainWindow::OnBtnNextClick()
{
    Ctrl.GoNextMonth();
    l_Date->setText(Ctrl.GetMonthName(Ctrl.GetWorkMonth()) + " " + QString::number(Ctrl.GetWorkYear()));
    ClearNotes();
    PrintCalendar();
}

void MainWindow::OnBtnBackClick()
{
    Ctrl.GoPrevMonth();
    l_Date->setText(Ctrl.GetMonthName(Ctrl.GetWorkMonth()) + " " + QString::number(Ctrl.GetWorkYear()));
    ClearNotes();
    PrintCalendar();
}

void MainWindow::OnCustomMenuRequested(QPoint pos, int numberOfCell)
{
    QMenu * menu = new QMenu(this);

    QAction * copyDateToClipboard = new QAction("Copy", this);

    connect(copyDateToClipboard, &QAction::triggered, this, [numberOfCell, this] () {OnCopyDateToClipborad(numberOfCell); });     // Обработчик вызова диалога редактирования

    menu->addAction(copyDateToClipboard);

    menu->popup(v_Calendar[numberOfCell]->mapToGlobal(pos));
}

void MainWindow::OnCopyDateToClipborad(int numberOfCell)
{
    QClipboard* clipboard = QApplication::clipboard();

    auto dates = Ctrl.GetWorkMonthDates();

    auto date = dates[numberOfCell];

    QString text = QString::number(date.year) + " " + Ctrl.GetMonthName(date.month) + " " + QString("%1%2").arg(date.day / 10).arg(date.day % 10) + " " + Ctrl.GetDayOfWeekName(date);

    clipboard->setText(text, QClipboard::Clipboard);

    if (clipboard->supportsSelection()) {
        clipboard->setText(text, QClipboard::Selection);
    }
}

void MainWindow::OnAddNote(QPoint pos, int numberOfCell)
{
    auto frame = v_Calendar[numberOfCell];

    auto dates = Ctrl.GetWorkMonthDates();
    auto date = dates[numberOfCell];

    NoteDlg* dlg = new NoteDlg(date);

    if (dlg->exec() == QDialog::Accepted)
    {
        QString str = dlg->GetText();

        db->InsertNote(date, str);

        if (!str.isEmpty() && frame->layout()->count() > 0)
        {
            auto layout = frame->layout();

            ElidedLabel* l_text = nullptr;

            if (layout->count() < 2)
            {
                l_text = new ElidedLabel(str);
                layout->addWidget(l_text);
            }
            else
            {
                l_text = dynamic_cast<ElidedLabel*>(layout->itemAt(INDEX_NOTE)->widget());
                l_text->setText(str);
            }

            //text->setStyleSheet(TEXT_FIELD);

        }
    }
}

void MainWindow::ClearNotes()
{
    for (auto day : v_Calendar)
    {
        if (day->layout()->count() > 1)
            delete day->layout()->itemAt(INDEX_NOTE)->widget();
    }

}

bool MainWindow::eventFilter(QObject* o, QEvent* e)
{
    if (e->type() == QEvent::MouseButtonDblClick)
    {
        QMouseEvent* m = (QMouseEvent*) e;
        return true;
    }

    return false;
}
