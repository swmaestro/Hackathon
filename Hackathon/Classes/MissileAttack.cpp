//
//  MissileAttack.cpp
//  Hackathon
//
//  Created by 강 건우 on 12. 12. 22..
//
//

#include "MissileAttack.h"

bool MissileAttack::init()
{
    if (!Attack::init())
        return false;
    
    missile = CCSprite::create("missile.png");
    addChild(missile);
    
    aim = CCSprite::create("leaf.png");
    addChild(aim);
    
    isHit = false;
    
    angle = 0;
    distance = 1600;
    
    resetPosition();
    scheduleUpdate();
    
    return true;
}

void MissileAttack::resetPosition()
{
    CCPoint p(0, distance);
    
    CCAffineTransform transform = CCAffineTransformRotate(CCAffineTransformIdentity, angle);
    p = CCPointApplyAffineTransform(p, transform);
    missile->setRotation(-angle / M_PI * 180);
    missile->setPosition(p);
    
    p = CCPoint(0, 120);
    
    transform = CCAffineTransformRotate(CCAffineTransformIdentity, angle);
    p = CCPointApplyAffineTransform(p, transform);
    aim->setRotation(-angle / M_PI * 180);
    aim->setPosition(p);
}

void MissileAttack::update(float dt)
{
    distance -= dt * 800;
    
    resetPosition();
}

bool MissileAttack::enable()
{
    if (distance < 120)
        return false;
    
    return true;
}

void MissileAttack::rotate(float r)
{
    angle += r;
    
    resetPosition();
}

bool MissileAttack::hit(cocos2d::CCSprite *player)
{
    return false;
}