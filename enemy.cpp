#include "enemy.h"

Enemy::Enemy(float x, float y, float radius,QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world)
{
    // Set pixmap
    g_pixmap.setPixmap(pixmap);
    g_size = QSize(radius*2,radius*2);

    // Create Body
    b2BodyDef bodydef;
    bodydef.type = b2_dynamicBody;
    bodydef.bullet = true;
    bodydef.position.Set(x,y);
    bodydef.userData = this;
    g_body = world->CreateBody(&bodydef);

    b2CircleShape bodyshape;
    bodyshape.m_radius = radius;

    b2FixtureDef fixturedef;
    fixturedef.shape = &bodyshape;
    fixturedef.density = ENEMY_DENSITY;
    fixturedef.friction = ENEMY_FRICTION;
    fixturedef.restitution = ENEMY_RESTITUTION;
    g_body->SetAngularDamping(3);
    g_body->CreateFixture(&fixturedef);

    // Bound timer
    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));


    scene->addItem(&g_pixmap);
}


/*b2Vec2 Enemy::getlinearvelocity()
{
    return g_body->GetLinearVelocity();
}*/
