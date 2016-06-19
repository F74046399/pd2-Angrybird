#include"bbird.h"

BBird::BBird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):Bird(x,y,radius,timer,pixmap,world,scene){
}
void BBird::ability(){
   g_body->SetLinearVelocity(b2Vec2(0,-20));

}
