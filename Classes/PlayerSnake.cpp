#include "PlayerSnake.h"
#include "ActionRunner.h"
#include "CommonMacro.h"

USING_NS_CC;
using namespace std;

PlayerSnake::PlayerSnake()
: m_isSpeedUp(false)
{
	m_runner = ActionRunner::create();
	m_runner->retain();
}

PlayerSnake::~PlayerSnake()
{
	m_runner->clear();
	m_runner->release();
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
