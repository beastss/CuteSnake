#include "GamePanel.h"
#include "PlayerSnake.h"
#include "CommonMacro.h"
#include "UiLayer.h"
#include "EnemySnake.h"
using namespace std;
USING_NS_CC;

bool GamePanel::init()
{
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	
	//背景层
	auto bk = CCLayerColor::create(ccc4(120, 0, 0, 200));
	addChild(bk);
	//蛇区域
	m_snakeField = CCLayerColor::create(ccc4(120, 120, 120, 255));
	m_snakeField->setContentSize(CCSize(GAME_LAYER_WIDTH, GAME_LAYER_HEIGHT));
	m_snakeField->ignoreAnchorPointForPosition(false);
	m_snakeField->setPosition(ccpMult(winSize, 0.5f));
	addChild(m_snakeField);
	//ui层
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

	addSnake(PlayerSnake::create(this));
	addSnake(EnemySnake::create(this));
	addSnake(EnemySnake::create(this));
	addSnake(EnemySnake::create(this));
	addSnake(EnemySnake::create(this));
	addSnake(EnemySnake::create(this));
	addSnake(EnemySnake::create(this));
}

void GamePanel::addSnake(Snake *snake)
{
	m_snakeField->addChild(snake);
	m_snakes.push_back(snake);
}

void GamePanel::removeSnake(Snake *snake)
{
	m_snakeField->removeChild(snake);
	auto iter = find(m_snakes.begin(), m_snakes.end(), snake);
	if (iter != m_snakes.end())
	{
		//注意：这里删除snake 会不会导致上层的遍历出错？
		m_snakes.erase(iter);
	}
}