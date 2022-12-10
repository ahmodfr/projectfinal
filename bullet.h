#ifndef BULLET_H
#define BULLET_H

#include <QKeyEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

class bullet: public QObject, public QGraphicsPixmapItem
{
public:
    bullet(int row, int col);
};

#endif // BULLET_H
