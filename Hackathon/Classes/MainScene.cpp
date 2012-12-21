//
//  MainScene.cpp
//  Hackathon
//
//  Created by 강 건우 on 12. 12. 21..
//
//

#include "MainScene.h"
#include "NormalAttack.h"

using namespace cocos2d;

CCScene* MainScene::scene()
{
    CCScene *scene = CCScene::create();
    MainScene *layer = MainScene::create();
    scene->addChild(layer);
    
    return scene;
}

bool MainScene::init()
{
    if (!CCLayer::init())
        return false;
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    rotate = 0;
    
    platform = CCLayer::create();
    platform->setAnchorPoint(CCPoint(0.5, 0.5));
    platform->setPosition(CCPoint(winSize.width / 2, winSize.height / 4));
    addChild(platform);
    
    center = CCSprite::create("center.png");
    center->setPosition(CCPoint(0, 0));
    platform->addChild(center);
    
    for (int i = 0; i < 4; ++i)
    {
        char t[20];
        sprintf(t, "slime%d.png", i + 1);
        slimeTex[i] = CCTextureCache::sharedTextureCache()->addImage(t);
    }
    slime = CCSprite::createWithTexture(slimeTex[0]);
    slime->setAnchorPoint(CCPoint(0.5, 0.2));
    slime->setPosition(CCPoint(0, 120));
    platform->addChild(slime);
    
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    
    scheduleUpdate();

    return true;
}

void MainScene::update(float dt)
{
    center->setRotation(center->getRotation() - rotate * 50 * dt);
    for (std::list<Attack *>::iterator i = attacks.begin(), next; i != attacks.end(); ++i)
        (*i)->rotate(rotate * 50 * dt * M_PI / 180);
    
    static float t = 0;
    t += dt;
    if (t > 0.25)
    {
        NormalAttack * attack = NormalAttack::create();
        attacks.push_back(attack);
        platform->addChild(attack);
        t = 0;
    }
    
    for (std::list<Attack *>::iterator i = attacks.begin(), next; i != attacks.end(); ++i)
        if ((*i)->hit(slime))
        {
            static int hit = 0;
            printf("HIT!!!!%d\n", ++hit);
        }
    
    static float sl = 0;
    sl += dt;
    if (sl >= 4)
        sl = 0;
    slime->setTexture(slimeTex[(int)sl]);
    
    for (std::list<Attack *>::iterator i = attacks.begin(), next; i != attacks.end(); i = next)
    {
        next = i;
        ++next;
        
        if (!(*i)->enable())
        {
            platform->removeChild(*i, true);
            attacks.remove(*i);
        }
    }
}

void MainScene::draw()
{
    CCLayer::draw();
}

bool MainScene::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (pTouch->getLocation().x < CCDirector::sharedDirector()->getWinSize().width / 2)
        rotate = -1;
    else
        rotate = 1;
    
    return true;
}

void MainScene::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (pTouch->getLocation().x < CCDirector::sharedDirector()->getWinSize().width / 2)
        rotate = -1;
    else
        rotate = 1;
}

void MainScene::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    rotate = 0;
}

void MainScene::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    rotate = 0;
}