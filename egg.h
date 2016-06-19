#ifndef EGG_H
#define EGG_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

#define EGG_DENSITY 10.0f
#define EGG_FRICTION 0.2f
#define EGG_RESTITUTION 0.5f

class Egg : public GameItem
{
public:
    Egg(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void setLinearVelocity(b2Vec2 velocity);

};

#endif // EGG_H
