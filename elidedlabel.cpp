#include "elidedlabel.h"


ElidedLabel::ElidedLabel(const QString& text,QWidget *parent)
    : QLabel(parent),
      content(text)
{
}

void ElidedLabel::setText(const QString &newText)
{
    content = newText;
    update();
}

void ElidedLabel::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);

    QPainter painter(this);
    QFontMetrics fontMetrics = painter.fontMetrics();

    QString elidedLine = fontMetrics.elidedText(content, Qt::ElideRight, event->rect().width());
    painter.drawText(QPoint(0, fontMetrics.ascent()), elidedLine);
}
