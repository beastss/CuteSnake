#include "GamePanel.h"
#include "PlayerSnake.h"
#include "CommonMacro.h"
#include "UiLayer.h"
using namespace std;
USING_NS_CC;

bool GamePanel::init()
{
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	
	//±³¾°²ã
	auto bk = CCLayerColor::create(ccc4(120, 0, 0, 200));
	addChild(bk);
	//ÉßÇøÓò
	m_snakeField = CCLayerColor::create(ccc4(120, 120, 120, 255));
	m_snakeField->setContentSize(CCSize(GAME_LAYER_WIDTH, GAME_LAYER_HEIGHT));
	m_snakeField->ignoreAnchorPointForPosition(false);
	m_snakeField->setPosition(ccpMult(winSize, 0.5f));
	addChild(m_snakeField);
	//ui²ã
	m_uiLayer = UiLayer::create();
	addChild(m_uiLayer);
	initSnakes();
	setContentSize(winSize);
    return true;
}

void GamePanel::setFocus(cocos2d::CCPoint pos)
{
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint newPos;
	newPos.x = winSize.width * 0.5f - pos.x + GAME_LAYER_WIDTH * 0.5f;
	newPos.y = winSize.height * 0.5f - pos.y + GAME_LAYER_HEIGHT * 0.5f;
	
	m_snakeField->setPosition(newPos);
}

void GamePanel::initSnakes()
{
	m_snakeField->removeAllChildren();
	auto playerSnake = PlayerSnake::create(this);
	m_snakeField->addChild(playerSnake);
}