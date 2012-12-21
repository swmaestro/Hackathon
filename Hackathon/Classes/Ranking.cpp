//
//  Ranking.cpp
//  Hackathon
//
//  Created by 박 진 on 12. 12. 21..
//
//

#include "Ranking.h"
#include "rapidxml.hpp"

using namespace cocos2d;
using namespace rapidxml;
using namespace std;

Ranking::Ranking(Network *pNetwork)
{
    for(int i=0; i<9; ++i)
    {
        m_pPlayerName[i]        = NULL;
        m_pPlayerScore[i]       = NULL;
    }
    
    m_pBackground = NULL;

    for(int i=0; i<RANKING_ICON_MAX; ++i)
        m_pRankTex[i] = NULL;
    
    m_pNetwork = new Network;
}

Ranking::~Ranking()
{
    delete m_pNetwork;
}

bool Ranking::init()
{
    if( (GameScene::init() == NULL) )
        return false;
    
    char iconPath[128];
    m_pBackground = new CCSprite;
    
    for(int i=0; i<RANKING_ICON_MAX; ++i)
    {
        if(i == RANKING_ICON_S) sprintf(iconPath, "RankS.png");
        else                    sprintf(iconPath, "Rank%c.png", i+'A');
        
        m_pRankTex[i]
        = CCTextureCache::sharedTextureCache()->addImage(iconPath);
    }

    m_pBackground->initWithFile("ranking.png");
    m_pBackground->setAnchorPoint(ccp(0,0));
    m_pBackground->setPosition(ccp(0,0));
    addChild(m_pBackground);
    
    std::vector<RANK_DATA> vData;
    if(_GetRankData(vData) == false)
        return false;
    
    for(int i=0; i<vData.size(); ++i)
    {
        m_pPlayerScore[i]   = new CCLabelTTF;
        m_pPlayerName[i]    = new CCLabelTTF;
        
        m_pPlayerName[i]->initWithString(vData[i].name.data(), "MarkerFelt", 18);
        m_pPlayerScore[i]->initWithString(vData[i].score.data(), "MarkerFelt", 18);
        
        m_pPlayerName[i]->setAnchorPoint(ccp(0,0));
        m_pPlayerScore[i]->setAnchorPoint(ccp(0,0));
        
        m_pPlayerScore[i]->setPosition(ccp(180, 360 - i * 40));
        m_pPlayerName[i]->setPosition(ccp(70,   360 - i * 40));
        
        addChild(m_pPlayerName[i]);
        addChild(m_pPlayerScore[i]);
    }
    
    return true;
}

bool Ranking::_GetRankData(std::vector<RANK_DATA> &vData)
{
    const char *url = "http://www.daram.pe.kr/soma/index.php?request=getRanking";
    
    CURL_DATA xmlData;
    m_pNetwork->connectHttp(url, &xmlData);

    xml_document<char> xmlDoc;
    xmlDoc.parse<0>(const_cast<char*>(xmlData.pContent));
    
    xml_node<char> *pRoot = xmlDoc.first_node()->first_node()->next_sibling()->first_node();
        
    if( strcmp(xmlDoc.first_node()->first_node()->value(), "SUCCEED") != 0 )
        return false;
    
    for(xml_node<char> *pNode = pRoot; pNode != NULL; pNode = pNode->next_sibling())
    {
        RANK_DATA data;
        xml_node<char> *pContent = pNode->first_node();
        
        data.name = pContent->value();
        pContent = pContent->next_sibling()->next_sibling();
        data.score = pContent->value();
        
        vData.push_back(data);
    }
    
    return true;
}
