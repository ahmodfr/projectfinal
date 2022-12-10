#include "win.h"
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QFile>
#include <QTextStream>
#include <QGraphicsPixmapItem>
win::win()
{
    QPixmap wimage("A:\\proj\\project-main\\project-main\\images\\win.png");
        wimage = wimage.scaledToWidth(500);
        wimage =wimage.scaledToHeight(500);
        setPixmap(wimage);
}
