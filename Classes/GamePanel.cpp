#include "GamePanel.h"
#include "PlayerSnake.h"
#include "CommonMacro.h"
#include "UiLayer.h"
#include "EnemySnake.h"
#include "FoodMgr.h"
#include "Food.h"
#include <algorithm>
#include "PlayerData.h"
#include "MainScene.h"
#include "SoundMgr.h"
using namespace std;
USING_NS_CC;

GamePanel::GamePanel()
{
	m_foodMgr = new FoodMgr(this);
}

GamePanel::~GamePanel()
{
	delete m_foodMgr;
}

bool GamePanel::init()
{
	PlayerData::theData()->reset();
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	
	//背景层
	auto bk = CCLayerColor::create(ccc4(120, 0, 0, 200));
	addChild(bk);
	//蛇区域
	m_snakeField = CCNode::create();
	initGameBk();
	m_snakeField->setContentSize(CCSize(GAME_LAYER_WIDTH, GAME_LAYER_HEIGHT));
	m_snakeField->setAnchorPoint(ccp(0.5f, 0.5f));
	m_snakeField->setPosition(ccpMult(winSize, 0.5f));
	addChild(m_snakeField);
	m_snakeBatchNode = CCSpriteBatchNode::create("snake/circle.png");
	m_snakeField->addChild(m_snakeBatchNode);
	//ui层
	m_uiLayer = UiLayer::create();
	addChild(m_uiLayer);
	initSnakes();
	setContentSize(winSize);

	scheduleUpdate();
    return true;
}

void GamePanel::initGameBk()
{
	CCSpriteBatchNode* batchNode = CCSpriteBatchNode::create("game_scene/map_01.png");
	m_snakeField->addChild(batchNode);
	const float gridSize = 40;
	int xGrids = GAME_LAYER_WIDTH / gridSize;
	int yGrids = GAME_LAYER_HEIGHT / gridSize;
	for (int i = 0; i < yGrids; ++i)
	{
		for (int j = 0; j < xGrids; ++j)
		{
			CCSprite *spr = CCSprite::createWithTexture(batchNode->getTexture());
			spr->setAnchorPoint(ccp(0, 0));
			CCPoint pos;
			pos.x = gridSize * j;
			pos.y = gridSize * i;
			spr->setPosition(pos);
			batchNode->addChild(spr);
		}
	}
}

void GamePanel::update(float dt)
{
	for (size_t i = 0; i < m_snakes.size(); ++i)
	{
		m_snakes[i]->update(dt);
	}
	m_foodMgr->update(dt);
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
	addSnake(PlayerSnake::create(this));
	for (int i = 1; i < SNAKE_NUM; ++i)
	{
		addSnake(EnemySnake::create(this));
	}
}

void GamePanel::addSnake(Snake *snake)
{
	m_snakeField->addChild(snake, 1);
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

void GamePanel::addFood(cocos2d::ccColor3B color, bool isSnakeBody, cocos2d::CCPoint pos)
{
	if (pos.x <= 10) pos.x = 10;
	if (pos.x >= GAME_LAYER_WIDTH - 10) pos.x = GAME_LAYER_WIDTH - 10;
	if (pos.y <= 10) pos.y = 10;
	if (pos.y >= GAME_LAYER_HEIGHT - 10) pos.y = GAME_LAYER_HEIGHT - 10;
	
	auto food = new Food(color, isSnakeBody);
	food->getView()->setPosition(pos);
	m_snakeBatchNode->addChild(food->getView(), 0);

	m_foodMgr->addFood(food);
}

void GamePanel::onBackKeyTouched()
{
	SoundMgr::theMgr()->playEffect(kEffectMusicButton);
	MainScene::theScene()->showPanel(kPanelIdMenuPanel);
}