#include "barrier.h"

Bar::Bar(float x, float y, float w, float h,QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world)
{
    g_pixmap.setPixmap(pixmap);
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
    g_size=QSize(w,h);

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x,y);
    bodyDef.bullet = true;
    bodyDef.userData=this;
    g_body = world->CreateBody(&bodyDef);
    b2PolygonShape bodyshape;
    bodyshape.SetAsBox(w/2,h/2);

    b2FixtureDef fixturedef;
    fixturedef.shape = &bodyshape;
    fixturedef.density = BAR_DENSITY;
    fixturedef.friction = BAR_FRICTION;
    fixturedef.restitution = BAR_RESTITUTION;

    g_body->SetAngularDamping(3);
    g_body->CreateFixture(&fixturedef);

    // Bound timer
    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));

    scene->addItem(&g_pixmap);
}
