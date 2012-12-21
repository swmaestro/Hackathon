//
//  NormalAttack.h
//  Hackathon
//
//  Created by 강 건우 on 12. 12. 21..
//
//

#ifndef __Hackathon__NormalAttack__
#define __Hackathon__NormalAttack__

#include "Attack.h"

class NormalAttack : public Attack
{
public:
    CREATE_FUNC(NormalAttack);
    bool init();
    
    void resetPosition();
    
    void update(float dt);
    
    virtual bool enable();
    virtual bool hit(cocos2d::CCSprite * player);
    virtual void rotate(float r);
    
private:
    CCSprite * sprite;
    
    float angle;
    float distance;
    float speed;
    
    bool isHit;
};

#endif /* defined(__Hackathon__NormalAttack__) */
