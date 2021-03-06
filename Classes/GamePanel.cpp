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
#include "RankingModel.h"
using namespace std;
USING_NS_CC;

GamePanel::GamePanel()
: m_runningUpdate(true)
{
	m_foodMgr = new FoodMgr(this);
}

GamePanel::~GamePanel()
{
	delete m_foodMgr;
}

void GamePanel::onEnter()
{
	BasePanel::onEnter();
	MsgNotifier::theNotifier()->addView(this);
}

void GamePanel::onExit()
{
	BasePanel::onExit();
	MsgNotifier::theNotifier()->removeView(this);
}

bool GamePanel::init()
{
	RankingModel::theModel()->reset();
	PlayerData::theData()->reset();
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	
	//������
	//auto bk = CCLayerColor::create(ccc4(120, 0, 0, 200));
	auto bk = CCLayerColor::create(ccc4(0, 0, 0, 200));
	addChild(bk);
	
	//������
	m_snakeField = CCNode::create();
	initGameBk();
	m_snakeField->setContentSize(CCSize(GAME_LAYER_WIDTH, GAME_LAYER_HEIGHT));
	m_snakeField->setAnchorPoint(ccp(0.5f, 0.5f));
	m_snakeField->setPosition(ccpMult(winSize, 0.5f));
	addChild(m_snakeField);
	m_snakeBatchNode = CCSpriteBatchNode::create("sprite_frames/snake_skin.png");
	m_snakeField->addChild(m_snakeBatchNode);

	//ui��
	m_uiLayer = UiLayer::create();
	addChild(m_uiLayer);
	initSnakes();
	setContentSize(winSize);

	//�������β�
	auto mask = CCSprite::create("main_menu/mask.png");
	mask->setPosition(ccpMult(winSize, 0.5f));
	addChild(mask);

	scheduleUpdate();
    return true;
}

void GamePanel::initGameBk()
{
	string gridPath = "game_scene/beijing.png";
	CCSpriteBatchNode* batchNode = CCSpriteBatchNode::create(gridPath.c_str());
	auto bk = CCSprite::create(gridPath.c_str());
	m_snakeField->addChild(batchNode);
	const float gridWidth = bk->getContentSize().width;
	const float gridHeight = bk->getContentSize().height;
	int xGrids = GAME_LAYER_WIDTH / gridWidth + 1;
	int yGrids = GAME_LAYER_HEIGHT / gridHeight + 1;
	for (int i = 0; i < yGrids; ++i)
	{
		for (int j = 0; j < xGrids; ++j)
		{
			CCSprite *spr = CCSprite::createWithTexture(batchNode->getTexture());
			spr->setAnchorPoint(ccp(0, 0));
			CCPoint pos;
			pos.x = gridWidth * j;
			pos.y = gridHeight * i;
			spr->setPosition(pos);
			batchNode->addChild(spr);
		}
	}
}

void GamePanel::onUpdateGameState(bool pause)
{
	m_runningUpdate = !pause;
}

void GamePanel::update(float dt)
{
	if (!m_runningUpdate) return;
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
	SnakeData data;
	data.length = INIT_SNAKE_LENGTH;
	data.skinId = 2;
	//data.length = 100; 
	addSnake(PlayerSnake::create(this, data));
	//return;
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
		//ע�⣺����ɾ��snake �᲻�ᵼ���ϲ�ı���������
		m_snakes.erase(iter);
	}
}

void GamePanel::addFood(cocos2d::ccColor3B color, cocos2d::CCPoint pos)
{
	if (pos.x <= 10) pos.x = 10;
	if (pos.x >= GAME_LAYER_WIDTH - 10) pos.x = GAME_LAYER_WIDTH - 10;
	if (pos.y <= 10) pos.y = 10;
	if (pos.y >= GAME_LAYER_HEIGHT - 10) pos.y = GAME_LAYER_HEIGHT - 10;
	
	auto food = new Food(color);
	food->getView()->setPosition(pos);
	m_snakeBatchNode->addChild(food->getView(), -10000);
	m_foodMgr->addFood(food);
}

void GamePanel::addFood(std::string path, cocos2d::CCPoint pos)
{
	if (pos.x <= 10) pos.x = 10;
	if (pos.x >= GAME_LAYER_WIDTH - 10) pos.x = GAME_LAYER_WIDTH - 10;
	if (pos.y <= 10) pos.y = 10;
	if (pos.y >= GAME_LAYER_HEIGHT - 10) pos.y = GAME_LAYER_HEIGHT - 10;

	auto food = new Food(path);
	food->getView()->setPosition(pos);
	m_snakeBatchNode->addChild(food->getView(), -9999);
	m_foodMgr->addFood(food);
}

void GamePanel::onBackKeyTouched()
{
	SoundMgr::theMgr()->playEffect(kEffectMusicButton);
	MainScene::theScene()->showPanel(kPanelIdMenuPanel);
}