#include "frameclickable.h"

FrameClickable::FrameClickable()
{

}

void FrameClickable::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->type() == QMouseEvent::MouseButtonDblClick)
    {
        emit DoubleClick(event);
    }

    return QFrame::mouseDoubleClickEvent(event);
}
