//
//  LaserAttack.h
//  Hackathon
//
//  Created by 강 건우 on 12. 12. 22..
//
//

#ifndef __Hackathon__LaserAttack__
#define __Hackathon__LaserAttack__

#include "Attack.h"

class LaserAttack : public Attack
{
public:
    CREATE_FUNC(LaserAttack);
    bool init();
    
    void resetPosition();
    
    void update(float dt);
    
    virtual bool enable();
    virtual bool hit(cocos2d::CCSprite * player);
    virtual void rotate(float r);
    
private:
    CCSprite * laser;
    float angle, distance, time;
    bool isHit;
};

#endif /* defined(__Hackathon__LaserAttack__) */
