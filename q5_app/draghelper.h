#pragma once

#include <QObject>
#include <QPoint>
#include <QCursor>

class QAbstractScrollArea;

class DragHelper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled)

public:
    DragHelper(QAbstractScrollArea *area, QObject* parent=nullptr);
    virtual ~DragHelper(){}

    bool isEnabled()const{
        return enabled;
    }
    void setEnabled(bool e){
        enabled = e;
    }

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private:
    QAbstractScrollArea *area;
    QPoint dragPos;
    bool enabled;
    QCursor saved_cursor;
};

