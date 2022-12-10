#include "lose.h"
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QFile>
#include <QTextStream>
#include <QGraphicsPixmapItem>
lose::lose()
{
    QPixmap limage("A:\\proj\\project-main\\project-main\\images\\lose.png");
        limage = limage.scaledToWidth(500);
        limage =limage.scaledToHeight(500);
        setPixmap(limage);
}
