#ifndef CEILING_H
#define CEILING_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

class Ceiling : public GameItem
{
public:
    Ceiling(float x, float y, float w, float h, b2World *world, QGraphicsScene *scene);
};

#endif // CEILING_H
