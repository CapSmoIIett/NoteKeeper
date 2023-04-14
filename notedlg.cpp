#include "notedlg.h"

NoteDlg::NoteDlg(Date date)
{
    this->resize(150, 300);

    //if (this->objectName().isEmpty())
    this->setObjectName("Note " + QString("%1%2").arg(date.day / 10).arg(date.day % 10) +
        "." + CalendarCtrl::GetMonthName(date.month) + QString::number(date.year));


    QVBoxLayout* vl = new QVBoxLayout(this);
    QHBoxLayout* hl = new QHBoxLayout();

    p_ButtonOk = new QPushButton("OK");
    p_ButtonCancel = new QPushButton("Cancle");
    p_TextBlock = new QTextEdit();

    hl->addWidget(p_ButtonCancel);
    hl->addWidget(p_ButtonOk);

    vl->addWidget(p_TextBlock);
    vl->addLayout(hl);


    connect(p_ButtonOk, &QPushButton::clicked, this, &NoteDlg::accept);
    connect(p_ButtonCancel, &QPushButton::clicked, this, &NoteDlg::reject);

}

void NoteDlg::SetText(QString str)
{
    p_TextBlock->setText(str);
}

QString NoteDlg::GetText()
{
    return p_TextBlock->toPlainText();
}
