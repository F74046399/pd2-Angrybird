#include"wbird.h"
#include"mainwindow.h"

WBird::WBird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):Bird(x,y,radius,timer,pixmap,world,scene)
{
}
void WBird::ability()
{
   g_body->SetLinearVelocity(b2Vec2(-20,-20));
}
