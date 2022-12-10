#include "powerpellet.h"
#include <QKeyEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include "lifestuff.h"
#include "bullet.h"
//#include "timer.h"
#include <QDebug>
#include <QTimer>


powerpellet::powerpellet(int row, int col)
{
    QPixmap image ("A:\\proj\\project-main\\project-main\\images\\fish.png");
    image=image.scaledToHeight(50);
    image=image.scaledToWidth(50);
    setPixmap(image);
    setPos(50 + col * 50, 50 + row * 50);




}

void powerpellet::timerupdate()
{
    QGraphicsTextItem *text = scene()->addText("Hello World");
    text->setPos(50 + 0 * 50, 50 + 0 * 50);



}



