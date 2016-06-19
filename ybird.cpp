#include"ybird.h"

YBird::YBird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):Bird(x,y,radius,timer,pixmap,world,scene)
{
}
void YBird::ability(){
    setLinearVelocity(b2Vec2(60, g_body->GetLinearVelocity().y));
}
