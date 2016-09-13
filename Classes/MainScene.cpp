#include "MainScene.h"
#include "GameLayer.h"
#include "UiLayer.h"
using namespace std;
USING_NS_CC;

bool MainScene::init()
{
	if (!CCScene::init())return false;
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	//��Ϸ��
	m_gameLayer = GameLayer::create();
	addChild(m_gameLayer);
	//ui��
	m_uiLayer = UiLayer::create();
	addChild(m_uiLayer);

    return true;
}

