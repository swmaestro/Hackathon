//
//  NormalAttack.cpp
//  Hackathon
//
//  Created by 강 건우 on 12. 12. 21..
//
//

#include "NormalAttack.h"

bool NormalAttack::init()
{
    if (!Attack::init())
        return false;
    
    isHit = false;
    
    sprite = CCSprite::create("dropper.png");
    addChild(sprite);
    
    angle = CCRANDOM_0_1() * 2 * M_PI;
    distance = 400;
    speed = 150 + CCRANDOM_0_1() * 50;
    
    resetPosition();
    scheduleUpdate();
    
    return true;
}

void NormalAttack::resetPosition()
{
    CCPoint p(0, distance);
    CCAffineTransform transform = CCAffineTransformRotate(CCAffineTransformIdentity, angle);
    p = CCPointApplyAffineTransform(p, transform);
    sprite->setRotation(-angle / M_PI * 180);
    sprite->setPosition(p);
}

void NormalAttack::update(float dt)
{
    distance -= dt * speed;
    
    resetPosition();
}

bool NormalAttack::enable()
{
    if (distance < 120)
        return false;
    
    return true;
}

bool NormalAttack::hit(CCSprite * player)
{
    if (isHit)
        return false;
    
    CCPoint p1, p2;
    p1 = sprite->getPosition();
    p2 = player->getPosition();

    float dist = sqrtf(powf(p1.x - p2.x, 2) + powf(p1.y - p2.y, 2));
    
    if (dist < player->getContentSize().width / 4 + sprite->getContentSize().width / 4)
        return isHit = true;
    
    return false;
}

void NormalAttack::rotate(float r)
{
    angle += r;
    
    resetPosition();
}