#include "PlayerSnake.h"
#include "ActionRunner.h"
#include "CommonMacro.h"
#include "MainScene.h"
#include "GamePanel.h"
#include "GameOverDialog.h"

USING_NS_CC;
using namespace std;

PlayerSnake::PlayerSnake(GamePanel *gamePanel)
: Snake(gamePanel)
, m_isSpeedUp(false)
{
	m_runner = ActionRunner::create();
	m_runner->retain();
}

PlayerSnake::~PlayerSnake()
{
	m_runner->clear();
	m_runner->release();
}

PlayerSnake *PlayerSnake::create(GamePanel *gamePanel)
{
	PlayerSnake *snake = new PlayerSnake(gamePanel);
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
	return true;
}

void PlayerSnake::onAngleChanged(int angle)
{
	m_destAngle = angle;
}

void PlayerSnake::onSpeedUp()
{
	if (m_isSpeedUp) return;

	m_runner->queueAction(CallFuncAction::withFunctor([=]()
	{
		m_speed = NORMAL_SPEED * 2.0f;
		m_isSpeedUp = true;
	}));
	m_runner->queueAction(DelayAction::withDelay(2.0f));
	m_runner->queueAction(CallFuncAction::withFunctor([=]()
	{
		m_speed = NORMAL_SPEED;
		m_isSpeedUp = false;
		SnakeController::controller()->speedUpOver();
	}));
}

void PlayerSnake::onGrow()
{
	addBody();
}

void PlayerSnake::onGodLike()
{

}

void PlayerSnake::onMove(cocos2d::CCPoint pos)
{
	m_gamePanel->setFocus(pos);
}

void PlayerSnake::onDead()
{
	auto dialog = GameOverDialog::create();
	MainScene::theScene()->showDialog(dialog);
}
