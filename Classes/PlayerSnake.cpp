#include "PlayerSnake.h"

USING_NS_CC;
using namespace std;

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

}
