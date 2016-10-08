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

PlayerSnake::PlayerSnake(GamePanel *gamePanel, const SnakeData &data)
: Snake(gamePanel, data)
, m_godLikeTime(0)
, m_speedUpTime(0)
{
	m_runner = ActionRunner::create();
	m_runner->retain();
}

PlayerSnake::~PlayerSnake()
{
	m_runner->clear();
	m_runner->release();
}

PlayerSnake *PlayerSnake::create(GamePanel *gamePanel, const SnakeData &data)
{
	PlayerSnake *snake = new PlayerSnake(gamePanel, data);
	snake->init();
	snake->autorelease();
	return snake;
}

void PlayerSnake::onEnter()
{
	Snake::onEnter();
	SnakeController::controller()->addView(this);
}

void PlayerSnake::onExit()
{
	Snake::onExit();
	SnakeController::controller()->removeView(this);
}

bool PlayerSnake::init()
{
	auto size = CCSize(GAME_LAYER_WIDTH, GAME_LAYER_HEIGHT);
	initBodyPos(ccpMult(size, 0.5f));

	if (m_data.name.empty())
	{
		m_data.name = PlayerData::theData()->getName();
	}
	m_nameLabel->setString(m_data.name.c_str());
	return true;
}

void PlayerSnake::onAngleChanged(int angle)
{
	m_destAngle = angle;
}

void PlayerSnake::onSpeedUp(bool enable)
{
	m_isSpeedUp = false;
	if (!enable)
	{
		m_speed = NORMAL_SPEED;
	}
	else if (m_body.size() > INIT_SNAKE_LENGTH)
	{
		m_speed = NORMAL_SPEED * 2.0f;
		m_isSpeedUp = true;
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

	if (m_isSpeedUp)
	{
		m_speedUpTime += dt;
		if (m_speedUpTime >= 3.0f)
		{
			removeBody();
			m_speedUpTime = 0;
		}
		m_isSpeedUp = m_body.size() > INIT_SNAKE_LENGTH;//当加速过程中，蛇长度达到最小，不能加速
		if (!m_isSpeedUp)
		{
			m_speed = NORMAL_SPEED;
		}
	}
}

void PlayerSnake::onEatFood()
{
	PlayerData::theData()->setData(m_data);
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
