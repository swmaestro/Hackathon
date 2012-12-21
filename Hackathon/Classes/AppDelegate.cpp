//
//  HackathonAppDelegate.cpp
//  Hackathon
//
//  Created by 강 건우 on 12. 12. 21..
//  Copyright __MyCompanyName__ 2012년. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "MainScene.h"

#include "Ranking.h"

USING_NS_CC;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    srand(time(NULL));
    
    // create a scene. it's an autorelease object
    Ranking *pRanking = new Ranking();
    pRanking->init();
  
    CCScene *pScene = pRanking->GetScene();
    
//    CCScene *pScene = MainScene::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->pause();

    // if you use SimpleAudioEngine, it must be paused
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->resume();
    
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
