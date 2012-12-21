//
//  Attack.h
//  Hackathon
//
//  Created by 강 건우 on 12. 12. 21..
//
//

#ifndef __Hackathon__Attack__
#define __Hackathon__Attack__

#include "cocos2d.h"

using namespace cocos2d;

class Attack : public cocos2d::CCLayer
{
public:
    virtual bool enable() = 0;
    virtual bool hit(cocos2d::CCSprite * player) = 0;
    virtual void rotate(float r) = 0;
};

#endif /* defined(__Hackathon__Attack__) */
