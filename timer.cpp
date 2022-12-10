#include "timer.h"
#include <QFont>

timer::timer(QGraphicsItem* parent): QGraphicsTextItem(parent)
{

    time=10;
     setPlainText(QString("Angry meow ends in " + QString::number(time)));
     setDefaultTextColor(Qt::black);
     setFont(QFont("times", 12));


}

void timer::countdown()
{


}

void timer::go()
{
    /*
    time=10;
    setPlainText(QString("Angry meow ends in " + QString::number(time)));
    setDefaultTextColor(Qt::black);
    setFont(QFont("times", 12));
    */
}
