#ifndef BARRIER_H
#define BARRIER_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

#define BAR_DENSITY 20.0f
#define BAR_FRICTION 0.5f
#define BAR_RESTITUTION 0.4f

class Bar: public GameItem
{
public:
    Bar(float x,float y,float w,float h,QTimer *timer,QPixmap pixmap,b2World *world,QGraphicsScene *scene);

};

#endif // BARRIER_H
