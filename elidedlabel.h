#ifndef ELIDEDLABEL_H
#define ELIDEDLABEL_H

#include <QLabel>
#include <QPainter>
#include <QPaintEvent>

class ElidedLabel : public QLabel
{
    Q_OBJECT

public:
    explicit ElidedLabel(const QString& text = "", QWidget *parent = nullptr);

    void setText(const QString &text);
    const QString & text() const { return content; }

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QString content;
};

#endif // ELIDEDLABEL_H
