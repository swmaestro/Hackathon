//
//  MainScene.cpp
//  Hackathon
//
//  Created by 강 건우 on 12. 12. 21..
//
//

#include "MainScene.h"

#include "NormalAttack.h"
#include "MissileAttack.h"
#include "LaserAttack.h"

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
    
    pNetwork = new Network;
    CCApplication::sharedApplication()->SetisOK(false);
    
    m_life = 100;
    m_score = 0;
    m_isGameOver = false;

    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    rotate = 0;
    
    pScore = CCLabelTTF::create("0", "MarkerFelt", 60);
    pScore->setColor(ccc3(0, 0, 0));
    
    pLife = CCLabelTTF::create("100", "MarkerFelt", 30);
    pLife->setPosition(ccp(120, 340));
    pLife->setColor(ccc3(255, 0, 0));
    
    platform = CCLayer::create();
    platform->setAnchorPoint(CCPoint(0.5, 0.5));
    platform->setPosition(CCPoint(winSize.width / 2, winSize.height / 4));
    addChild(platform);
    
    background = CCSprite::create("background.png");
    platform->addChild(background, 0);
    
    center = CCSprite::create("center.png");
    center->setPosition(CCPoint(0, 0));
    platform->addChild(center, 3);
    platform->addChild(pScore, 4);
    platform->addChild(pLife, 5);
    
    for (int i = 0; i < 4; ++i)
    {
        char t[20];
        sprintf(t, "slime%d.png", i + 1);
        slimeTex[i] = CCTextureCache::sharedTextureCache()->addImage(t);
    }
    slime = CCSprite::createWithTexture(slimeTex[0]);
    slime->setAnchorPoint(CCPoint(0.5, 0.2));
    slime->setPosition(CCPoint(0, 120));
    platform->addChild(slime, 4);
    
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    
    scheduleUpdate();
    
    pBackEffect = CCSprite::create("bigLeaf.png");
    pBackEffect->setAnchorPoint(ccp(0.5,0.5));
    pBackEffect->setScale(1.5);
    platform->addChild(pBackEffect, 1);
    
    pGameOver = CCSprite::create("gameOver.png");
    pGameOver->setPosition(ccp(0, 400));
    platform->addChild(pGameOver, 5);
    
    return true;
}

void MainScene::_sendRanking(const char *name, int score)
{
    const char *baseURL = "http://www.daram.pe.kr/soma/index.php?request=addRanking&ranker=%s&ranktime=0&rankscore=%d&requestWhen=0000";
    char url[256];
    sprintf(url, baseURL, name, score);
    
    CURL_DATA data;
    pNetwork->connectHttp(url, &data);
}

void MainScene::update(float dt)
{
    if(m_isGameOver)
    {
        if(CCApplication::sharedApplication()->isOK())
        {
            _sendRanking(CCApplication::sharedApplication()->GetUIAlertViewText(), m_score);
            CCDirector::sharedDirector()->popScene();
        }

        return;
    }
    
    center->setRotation(center->getRotation() - rotate * 50 * dt);
    pBackEffect->setRotation(center->getRotation());
    background->setRotation(background->getRotation() - rotate * 10 * dt);
    for (std::list<Attack *>::iterator i = attacks.begin(), next; i != attacks.end(); ++i)
        (*i)->rotate(rotate * 50 * dt * M_PI / 180);
    
    static float t = 0;
    t += dt;
    if (t > 0.05)
    {
        float r = CCRANDOM_0_1();

        Attack * attack;
        
        if (r < 0.95)
            attack = NormalAttack::create(),
            platform->addChild(attack, 1);
        else if (r < 0.975)
            attack = MissileAttack::create(),
            platform->addChild(attack, 5);
        else
            attack = LaserAttack::create(),
            platform->addChild(attack, 5);
        
        attacks.push_back(attack);
        t = 0;
    }
    
    for (std::list<Attack *>::iterator i = attacks.begin(), next; i != attacks.end(); ++i)
        if ((*i)->hit(slime))
        {
            static int hit = 0;
            printf("HIT!!!!%d\n", ++hit);
            CCTintTo * to = CCTintTo::create(0.125f, 255, 0, 0);
            CCTintTo * back = CCTintTo::create(0.125f, 255, 255, 255);
            CCAction * seq = CCSequence::create(to, back, NULL);

            if( m_life > 0 )    m_life-= 30;
            else
            {
                m_isGameOver = true;
                CCMoveTo *move = CCMoveTo::create(1.5f, ccp(0, 200));
                pGameOver->runAction(move);
                CCDelayTime *delay = CCDelayTime::create(3.f);
                CCCallFunc *call = CCCallFunc::create(this, callfunc_selector(MainScene::_gameOver));
                CCFiniteTimeAction *sequence = CCSequence::create(delay, call);
                runAction(sequence);
                //게임오버 문구 출력
            }
            
            m_score -= 200;
            
            char num[20];
            sprintf(num, "%d", m_score);
            pScore->setString(num);
            
            sprintf(num, "%d", m_life);
            pLife->setString(num);
            
            background->runAction(seq);
        }
    
    static float sl = 0;
    sl += dt * 30;
    if (sl >= 4)
        sl = 0;
    slime->setTexture(slimeTex[(int)sl]);
    
    for (std::list<Attack *>::iterator i = attacks.begin(), next; i != attacks.end(); i = next)
    {
        next = i;
        ++next;
        
        if (!(*i)->enable())
        {
            _particleEffect((*i)->getPosition());
            platform->removeChild(*i, true);
            attacks.remove(*i);
            
            if(m_life < 100)        ++m_life;
            else                    m_life = 100;

            ++m_score;
            
            char num[20];
            sprintf(num, "%d", m_score);
            pScore->setString(num);

            sprintf(num, "%d", m_life);
            pLife->setString(num);
        }
    }
}

void MainScene::_particleEffect(CCPoint position)
{
//    if( getChildByTag(10) )
//        removeChildByTag(10, true);
//    
//    m_pFlower = CCParticleFlower::create();
//    m_pFlower->setPosition(position);
//    m_pFlower->setAnchorPoint(ccp(0.5, 0.5));
//    
//    m_pFlower->setScale(1.f);
//    m_pFlower->setLifeVar(0);
//    m_pFlower->setLife(10);
//    m_pFlower->setSpeed(100);
//    m_pFlower->setSpeedVar(10);
//    m_pFlower->setEmissionRate(500);
//    
//    addChild(m_pFlower, 5, 10);
//    m_pFlower->setTexture( CCTextureCache::sharedTextureCache()->addImage("leaf.png"));
//    
//    CCCallFunc *call = CCCallFunc::create(this, callfunc_selector(MainScene::_particleEnd));
//    CCDelayTime *delay = CCDelayTime::create(0.1f);
//    CCFiniteTimeAction *sequence = CCSequence::create(delay, call);
//    runAction(sequence);
}

void MainScene::_particleEnd()
{
//    m_pFlower->stopSystem();
}

void MainScene::_gameOver(cocos2d::CCObject *pSender)
{
//    CCDirector::sharedDirector()->popScene();
    char scoreTxt[20];
    sprintf(scoreTxt, "점수 : %d", m_score);
    CCApplication::sharedApplication()->uialertView("게임 끝", scoreTxt);
}

void MainScene::draw()
{
    CCLayer::draw();
}

bool MainScene::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if(m_isGameOver) return true;
    
    if (pTouch->getLocation().x < CCDirector::sharedDirector()->getWinSize().width / 2)
        rotate = -1;
    else
        rotate = 1;
    
    return true;
}

void MainScene::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if(m_isGameOver) return;

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

void MainScene::_backEffect(cocos2d::CCObject *pSender)
{
    static bool isMinus = true;
    GLubyte opacity = pBackEffect->getOpacity();
    
    if(opacity == 255)      isMinus = true;
    else if(opacity == 0)   isMinus = false;
    
    pBackEffect->setOpacity(opacity +  17*(1 - 2*isMinus)*2 );
}
