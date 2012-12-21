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
    
    aim = CCSprite::create("aim.png");
    aim->setColor(ccc3(255, 0, 0));
    aim->setScale(1.5f);
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
    {
        CCPoint p(0, -10);
        CCAffineTransform transform = CCAffineTransformRotate(CCAffineTransformIdentity, angle);
        p = CCPointApplyAffineTransform(p, transform);
        CCMoveBy * move = CCMoveBy::create(0.1f, p);
        CCActionInterval * rev = move->reverse();
        CCAction * seq = CCSequence::create(move, rev, NULL);
        getParent()->runAction(seq);
        return false;
    }
    
    return true;
}

void MissileAttack::rotate(float r)
{
    angle += r;
    
    resetPosition();
}

bool MissileAttack::hit(cocos2d::CCSprite *player)
{
    if (isHit)
        return false;
    
    CCPoint p1(0, distance - missile->getContentSize().height / 2);
    CCAffineTransform transform = CCAffineTransformRotate(CCAffineTransformIdentity, angle);
    p1 = CCPointApplyAffineTransform(p1, transform);
    
    CCPoint p2 = player->getPosition();
    
    float dist = sqrtf(powf(p1.x - p2.x, 2) + powf(p1.y - p2.y, 2));
    
    if (dist < player->getContentSize().width / 2)
        return isHit = true;
    
    return false;
}