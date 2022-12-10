#include "home.h"

home::home()
{
    QPixmap homeimage("A:\\proj\\project-main\\project-main\\images\\B01.png");
        homeimage = homeimage.scaledToWidth(50);
        homeimage = homeimage.scaledToHeight(50);
        setPixmap(homeimage);

}
