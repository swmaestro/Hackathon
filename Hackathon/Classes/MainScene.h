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
#include "Network.h"

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
    
    Network *pNetwork;
    CCLayer * platform;
    CCSprite * background, * center, * slime;
    CCTexture2D * slimeTex[4];
    
    std::list<Attack *> attacks;
    CCSprite *pBackEffect;
    cocos2d::CCParticleFlower*    m_pFlower;
    
private:
    cocos2d::CCLabelTTF           *pScore;
    cocos2d::CCLabelTTF           *pLife;
    cocos2d::CCSprite             *pGameOver;
    
private:
    int     m_life;
    int     m_score;
    bool    m_isGameOver;
    
public:
    void _sendRanking(const char *name, int score);
    void _gameOver(cocos2d::CCObject *pSender);
    void _backEffect(cocos2d::CCObject *pSender);
    
    void _particleEffect(cocos2d::CCPoint position);
    void _particleEnd();
};

#endif /* defined(__Hackathon__MainScene__) */
