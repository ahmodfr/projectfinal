#ifndef POWERPELLET_H
#define POWERPELLET_H
#include <QKeyEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsTextItem>
#include <QKeyEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include "lifestuff.h"
#include "bullet.h"
//#include "timer.h"
#include <QDebug>
#include <QTimer>


class powerpellet: public QObject, public QGraphicsPixmapItem


{
    Q_OBJECT
public:
    powerpellet(int row, int col);
    int countdown=10;

public slots:
    void timerupdate();

};

#endif // POWERPELLET_H
