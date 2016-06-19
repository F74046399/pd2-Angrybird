#ifndef YBIRD_H
#define YBIRD_H

#include"gameitem.h"
#include"bird.h"
class YBird : public Bird
{
public:
    YBird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    virtual void ability();
};


#endif // YBIRD_H
