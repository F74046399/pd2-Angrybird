#include"ceiling.h"

Ceiling::Ceiling(float x, float y, float w, float h, b2World *world, QGraphicsScene *scene):GameItem(world)
{
    b2BodyDef bodyDef;
    bodyDef.position.Set(x,y);
    bodyDef.userData=this;
    g_body = world->CreateBody(&bodyDef);

    b2PolygonShape bodyBox;
    bodyBox.SetAsBox(w,h);
    g_body->CreateFixture(&bodyBox,9.0f);

    scene->addItem(&g_pixmap);
    paint();


}
