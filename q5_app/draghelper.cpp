#include "draghelper.h"

#include <QAbstractScrollArea>
#include <QMouseEvent>
#include <QScrollBar>

DragHelper::DragHelper(QAbstractScrollArea *a, QObject* parent)
    : QObject(parent)
    , area(a)
    , enabled(false)
{
    if(area != nullptr && area->viewport() != nullptr){
        area->viewport()->installEventFilter(this);
    }
}

bool DragHelper::eventFilter(QObject *obj, QEvent *event){
    QMouseEvent *mevent = static_cast<QMouseEvent*>(event);
    if(enabled && area != nullptr && area->viewport() != nullptr){
        switch(event->type()){
        case QEvent::MouseButtonPress:
            if(mevent->buttons().testFlag(Qt::LeftButton)){
                dragPos = mevent->pos();
                saved_cursor = area->viewport()->cursor();
                area->viewport()->setCursor(Qt::ClosedHandCursor);
                return true;
            }
        break;
        case QEvent::MouseButtonRelease:
            if(!mevent->buttons().testFlag(Qt::LeftButton)){
                dragPos = QPoint();
                area->viewport()->setCursor(saved_cursor);
                return true;
            }
        break;
        case QEvent::MouseMove:
            if(mevent->buttons().testFlag(Qt::LeftButton)){
                auto dx = mevent->pos().x() - dragPos.x();
                auto dy = mevent->pos().y() - dragPos.y();
                dragPos= mevent->pos();
                area->horizontalScrollBar()->setValue(area->horizontalScrollBar()->value()-dx);
                area->verticalScrollBar()->setValue(area->verticalScrollBar()->value()-dy);;
                return true;
            }
        break;
        default:
            return QObject::eventFilter(obj, event);
        break;
        }
    }
    return QObject::eventFilter(obj, event);
}
