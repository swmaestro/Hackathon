//
//  LaserAttack.cpp
//  Hackathon
//
//  Created by 강 건우 on 12. 12. 22..
//
//

#include "LaserAttack.h"

bool LaserAttack::init()
{
    if (!Attack::init())
        return false;
    
    laser = CCSprite::create("fork.png");
    addChild(laser);
    
    isHit = false;
    
    angle = CCRANDOM_0_1() * 2 * M_PI;
    distance = 400;
    time = 0;
    
    resetPosition();
    scheduleUpdate();
    
    return true;
}

void LaserAttack::resetPosition()
{
    CCPoint p(0, distance);
    
    CCAffineTransform transform = CCAffineTransformRotate(CCAffineTransformIdentity, angle);
    p = CCPointApplyAffineTransform(p, transform);
    laser->setRotation(-angle / M_PI * 180);
    laser->setOpacity((2 - (time > 2 ? 2 : time)) / 2 * 255);
    laser->setPosition(p);
}

void LaserAttack::update(float dt)
{
    if (distance >= 120)
        distance -= dt * 100;
    else if (time < 2)
        time += dt;
    
    resetPosition();
}

bool LaserAttack::enable()
{
    if (distance < 120 && time >= 2)
        return false;
    
    return true;
}

void LaserAttack::rotate(float r)
{
    angle += r;
    
    resetPosition();
}

bool LaserAttack::hit(cocos2d::CCSprite *player)
{
    return false;
}