#ifndef BBIRD_H
#define BBIRD_H

#include"gameitem.h"
#include"bird.h"
class BBird : public Bird
{
public:
    BBird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    virtual void ability();
};

#endif // BBIRD_H

