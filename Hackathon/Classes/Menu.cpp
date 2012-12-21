//
//  Menu.cpp
//  Hackathon
//
//  Created by 박 진 on 12. 12. 22..
//
//

#include "Menu.h"
#include "MainScene.h"


using namespace cocos2d;

Menu::Menu()
{
    
}

Menu::~Menu()
{
    
}

bool Menu::init()
{
    if( (GameScene::init() == NULL) )
        return false;
    
    m_pBackground = CCSprite::create("menu.png");
    m_pBackground->setAnchorPoint(ccp(0,0));
    m_pBackground->setPosition(ccp(0,0));
    addChild(m_pBackground);
    
    m_pMenuItem[0] = CCMenuItemImage::create("startButton.png", "startButton.png", this, menu_selector(Menu::_btStart));
    m_pMenuItem[0]->setPosition(ccp(0, 50));
    
    m_pMenuItem[1] = CCMenuItemImage::create("rankingButton.png", "rankingButton.png", this, menu_selector(Menu::_btRanking));
    m_pMenuItem[1]->setPosition(ccp(0,-30));
    
    m_pMenuItem[2] = CCMenuItemImage::create("creditButton.png", "creditButton.png", this, menu_selector(Menu::_btCredit));
    m_pMenuItem[2]->setPosition(ccp(0, -110));
    
    m_pMenu = CCMenu::create(m_pMenuItem[0], m_pMenuItem[1], m_pMenuItem[2], NULL);
    
    addChild(m_pMenu);
    
    return true;
}

void Menu::_btStart(cocos2d::CCObject *pSender)
{
    CCScene *pScene = MainScene::scene();
    CCDirector::sharedDirector()->pushScene(pScene);
}

void Menu::_btRanking(cocos2d::CCObject *pSender)
{
    m_pRankingPage = new Ranking;
    m_pRankingPage->init(this->GetScene(), menu_selector(Menu::_btRankingBack));
    CCDirector::sharedDirector()->pushScene(m_pRankingPage->GetScene());
}

void Menu::_btCredit(cocos2d::CCObject *pSender)
{
    
}

void Menu::_btRankingBack(cocos2d::CCObject *pSender)
{
    CCDirector::sharedDirector()->popScene();
}
