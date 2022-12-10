#ifndef TIMER_H
#define TIMER_H

#include <QGraphicsTextItem>

class timer: public QGraphicsTextItem
{
public:
    timer(QGraphicsItem* parent=0);
    int time;
    void countdown();
    void go();
};

#endif // TIMER_H
