#ifndef WBIRD_H
#define WBIRD_H

#include"gameitem.h"
#include"bird.h"
#include <QLabel>
class WBird : public Bird
{
public:
    WBird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    virtual void ability();
};

#endif // WBIRD_H
