#include "frameclickable.h"

FrameClickable::FrameClickable()
{

}

void FrameClickable::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->type() == QMouseEvent::MouseButtonDblClick)
    {
        DoubleClick(event);
    }

    return QFrame::mouseDoubleClickEvent(event);
}
