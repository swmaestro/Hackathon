//
//  MissileAttack.h
//  Hackathon
//
//  Created by 강 건우 on 12. 12. 22..
//
//

#ifndef __Hackathon__MissileAttack__
#define __Hackathon__MissileAttack__

#include "Attack.h"

class MissileAttack : public Attack
{
public:
    //CREATE_FUNC(MissileAttack);
    bool init();
    
    void resetPosition();
    
    void update(float dt);
    
    virtual bool enable();
    //virtual bool hit(cocos2d::CCSprite * player);
    virtual void rotate(float r);
    
private:
    CCSprite * missile, * aim;
    
    float angle;
    float distance;
    
    bool isHit;
};


#endif /* defined(__Hackathon__MissileAttack__) */
