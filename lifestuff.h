#ifndef LIFESTUFF_H
#define LIFESTUFF_H

#include <QKeyEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>


class lifestuff: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    int lifes=3;
    lifestuff(int row, int col);
    void changeHeart(int row, int col);
int count = 0;
public slots:
};


#endif // LIFESTUFF_H
