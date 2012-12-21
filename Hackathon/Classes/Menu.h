//
//  Menu.h
//  Hackathon
//
//  Created by 박 진 on 12. 12. 22..
//
//

#pragma once

#include "GameScene.h"
#include "Ranking.h"

class Menu : public GameScene
{
private:
    cocos2d::CCSprite           *m_pBackground;

    cocos2d::CCMenu             *m_pMenu;
    cocos2d::CCMenuItemImage    *m_pMenuItem[3];
    
private:
    Ranking                     *m_pRankingPage;
    
public:
    Menu();
    ~Menu();
    
public:
    bool init();
    
public:
    void _btStart(cocos2d::CCObject *pSender);
    void _btRanking(cocos2d::CCObject *pSender);
    void _btCredit(cocos2d::CCObject *pSender);
    void _btRankingBack(cocos2d::CCObject *pSender);
};