//
//  MainScene.h
//  Hackathon
//
//  Created by 강 건우 on 12. 12. 21..
//
//

#ifndef __Hackathon__MainScene__
#define __Hackathon__MainScene__

#include "cocos2d.h"
#include "Attack.h"

#include <list>

using namespace cocos2d;

class MainScene : public CCLayer
{
public:
    CREATE_FUNC(MainScene);
    static CCScene* scene();
    
    virtual bool init();
    virtual void update(float dt);
    virtual void draw();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
private:
    int rotate;
    
    CCLayer * platform;
    CCSprite * background, * center, * slime;
    CCTexture2D * slimeTex[4];
    
    std::list<Attack *> attacks;
    CCSprite *pBackEffect;
};

#endif /* defined(__Hackathon__MainScene__) */
