//
//  Ranking.h
//  Hackathon
//
//  Created by 박 진 on 12. 12. 21..
//
//

#pragma once

#include "GameScene.h"
#include "Network.h"
#include <string>
#include <vector>

enum RANKING_ICON
{
    RANKING_ICON_A,
    RANKING_ICON_B,
    RANKING_ICON_C,
    RANKING_ICON_D,
    RANKING_ICON_E,
    RANKING_ICON_F,
    RANKING_ICON_S,
    RANKING_ICON_MAX
};

struct RANK_DATA
{
    std::string name;
    std::string score;
};

class Ranking : public GameScene
{
private:
    cocos2d::CCSprite               *m_pBackground;
    cocos2d::CCTexture2D            *m_pRankTex[RANKING_ICON_MAX];
    
    cocos2d::CCLabelTTF             *m_pPlayerName[9];
    cocos2d::CCLabelTTF             *m_pPlayerScore[9];
    
    Network                         *m_pNetwork;
    
public:
    Ranking(Network *pNetwork);
    ~Ranking();
    
public:
    bool init();
    
private:
    bool _GetRankData(std::vector<RANK_DATA> &vData);
};