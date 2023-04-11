#ifndef FRAMECLICKABLE_H
#define FRAMECLICKABLE_H

#include <QFrame>
#include <QMouseEvent>

class FrameClickable : public QFrame
{
    Q_OBJECT
public:
    FrameClickable();
    void mouseDoubleClickEvent(QMouseEvent *event) override;

protected:
signals:
    void DoubleClick(QMouseEvent *event);
};

#endif // FRAMECLICKABLE_H
