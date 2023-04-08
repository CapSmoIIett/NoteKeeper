#include "mainwindow.h"
#include "./ui_mainwindow.h"

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


    menuBar()->addMenu("File");
    //p_MenuBar = new QMenuBar(this);
    //p_QToolBar = new QToolBar(this);


    /*****************************************************
     * Configure buttons
     */

    QLabel* l_date = new QLabel("Date");
    l_date->setMaximumHeight(40);
    l_date->setFixedWidth(400);
    //l_date->setStyleSheet(LABELDATE_STYLE);


    /*****************************************************
     * Configure buttons
     */

    QPushButton *b_back = new QPushButton("<");

    b_back->setMaximumHeight(40);
    b_back->setMaximumWidth(60);
    b_back->setShortcut(QKeySequence(Qt::Key_Left));
    b_back->setToolTip("Go to the previous month, press ctrl to move to the previous year");


    QPushButton *b_next = new QPushButton(">");

    b_next->setMaximumWidth(60);
    b_next->setMaximumHeight(40);
    b_next->setShortcut(QKeySequence(Qt::Key_Right));
    b_next->setToolTip("Go to the next month, press ctrl to move to the next year");


    /*****************************************************
     * Add elements in layout
     */

    QHBoxLayout *hl = new QHBoxLayout;
    hl->addWidget(b_back, 1, Qt::AlignRight);
    hl->addWidget(l_date, 1, Qt::AlignCenter);
    hl->addWidget(b_next, 1, Qt::AlignLeft);
    //hl->addWidget(this->todobutton);


    QVBoxLayout* vl = new QVBoxLayout;
    vl->addLayout(hl, 1);

    QWidget *widget = new QWidget();
    widget->setLayout(vl);
    setCentralWidget(widget);

    //this->layout()->addWidget(vl->widget());
    //setLayout(vl);


    /*****************************************************
     * Create calendar
     */

    //Create 7x7 grid
    QGridLayout *grid_layout = new QGridLayout;

    QVector<QString> v_daysOfWeek = {
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday",
        "Saturday",
        "Sunday"
    };


    for (int i = 0; i < v_daysOfWeek.size(); i++)
    {
        QFrame *frame = new QFrame;
        frame->setMinimumHeight(50);//frame->setFixedHeight(50);
        frame->setLayout(hl);

        QHBoxLayout *hl = new QHBoxLayout;
        hl->setAlignment(Qt::AlignCenter);

        QLabel* l_name = new QLabel(v_daysOfWeek[i]);

        hl->addWidget(l_name);
        frame->setLayout(hl);
        grid_layout->addWidget(frame, 0, i);
    }

    for (auto i = 0; i < 35; i++ )
    {
        QFrame *frame = new QFrame;
        frame->setMinimumHeight(50);
        frame->setLayout(hl);

        QHBoxLayout *hl = new QHBoxLayout;
        hl->setAlignment(Qt::AlignCenter);

        QLabel* l_name = new QLabel(QString::number(i + 1));

        hl->addWidget(l_name);
        frame->setLayout(hl);
        grid_layout->addWidget(frame, i / 7 + 1, i % 7);
    }

    /*for (int j = 0; j < 7; j++) {
        QFrame *frame = new QFrame;
        QHBoxLayout *hl = new QHBoxLayout;
        hl->setAlignment(Qt::AlignCenter);
        frame->setFixedHeight(50);
        QLabel *wday_name = new QLabel("1");//DateUtil::numeric2literal_day_of_week(j+1).c_str());
        wday_name->setObjectName("header");
        frame->setObjectName("header");
        hl->addWidget(wday_name);
        //hl->setMargin(0);
        frame->setLayout(hl);
        //frame->setStyleSheet(CELL_STYLE);
        grid_layout->addWidget(frame, 0, j);
    }//*/

    vl->addLayout(grid_layout);

}

MainWindow::~MainWindow()
{
    delete ui;
}

