#ifndef NOTEDLG_H
#define NOTEDLG_H

#include <QDialog>
#include <QTextBlock>
#include <QPushButton>
#include <QBoxLayout>
#include <QTextEdit>

#include "calendar.h"

class NoteDlg : public QDialog
{
    Q_OBJECT
public:
    NoteDlg(Date date);

    void SetText(QString str);
    QString GetText();

public slots:

private:
    QPushButton* p_ButtonOk;
    QPushButton* p_ButtonCancel;

    QTextEdit* p_TextBlock;

};

#endif // NOTEDLG_H
