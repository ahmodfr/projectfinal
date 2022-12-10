#ifndef FRANKLIN_H
#define FRANKLIN_H

#include <QKeyEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include "lifestuff.h"
#include "enemy.h"
#include "bullet.h"
#include "win.h"
#include "home.h"
#include "lifestuff.h"
#include "powerpellet.h"




class rect: public QObject, public QGraphicsPixmapItem

{
    Q_OBJECT
public:
    int row, column;
    int data[12][12];
    rect(int boardData[12][12], bullet * b[4], Enemy *e[2], powerpellet *p[2], home *h[1], lifestuff *f[4], win *w[1], lose *l[1]);
    int life=3;
    bool angry=false;
    void killenemy();
    Enemy **e;
       bullet **b;
       home **h;
       lifestuff **f ;
       win **w;
       lose **l;
       powerpellet **p;
        int count = 0;
        bool winner = false;
        int counter =0;


public slots:
    void keyPressEvent(QKeyEvent* event);
    void holdpistol();
    void gobacktonormal();
    void angrymeow();
    float getdistance(Enemy*e);
    void hearts ();
};


#endif // FRANKLIN_H
