#include "PlayerSnake.h"
#include "ActionRunner.h"
#include "CommonMacro.h"
#include "MainScene.h"
#include "GamePanel.h"
#include "GameOverDialog.h"
#include "PlayerData.h"
#include "RebornDialog.h"

USING_NS_CC;
using namespace std;

PlayerSnake::PlayerSnake(GamePanel *gamePanel, int length)
: Snake(gamePanel, length)
, m_godLikeTime(0)
{
	m_runner = ActionRunner::create();
	m_runner->retain();
}

PlayerSnake::~PlayerSnake()
{
	m_runner->clear();
	m_runner->release();
}

PlayerSnake *PlayerSnake::create(GamePanel *gamePanel, int length)
{
	PlayerSnake *snake = new PlayerSnake(gamePanel, length);
	snake->init();
	snake->autorelease();
	return snake;
}

void PlayerSnake::onEnter()
{
	CCNode::onEnter();
	SnakeController::controller()->addView(this);
}

void PlayerSnake::onExit()
{
	CCNode::onExit();
	SnakeController::controller()->removeView(this);
}

bool PlayerSnake::init()
{
	auto size = CCSize(GAME_LAYER_WIDTH, GAME_LAYER_HEIGHT);
	getHead()->setPosition(ccpMult(size, 0.5f));

	return true;
}

void PlayerSnake::onAngleChanged(int angle)
{
	m_destAngle = angle;
}

void PlayerSnake::onSpeedUp(bool enable)
{
	if (enable)
	{
		m_speed = NORMAL_SPEED * 2.0f;
	}
	else
	{
		m_speed = NORMAL_SPEED;
	}
}

void PlayerSnake::onGrow()
{
	addBody();
}

void PlayerSnake::onGodLike()
{
	const int kTime = 3.0f;
	m_godLikeTime += kTime;
}

void PlayerSnake::onUpdate(float dt)
{
	if (m_godLikeTime > 0)
	{
		m_godLikeTime -= dt;
		if (m_godLikeTime <= 0)
		{
			m_godLikeTime = 0;
			setGodLikeState(false);
		}
		else
		{
			setGodLikeState(true);
		}
	}
}

void PlayerSnake::onEatFood()
{
	PlayerData::theData()->setLength(m_body.size());
	PlayerData::theData()->setScore(m_score);
	SnakeController::controller()->snakeDataChanged();
}

void PlayerSnake::onMove(cocos2d::CCPoint pos)
{
	m_gamePanel->setFocus(pos);
}

void PlayerSnake::onDead()
{
	auto dialog = RebornDialog::create(m_gamePanel);
	MainScene::theScene()->showDialog(dialog);
}
