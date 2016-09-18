#include "EnemySnake.h"
#include "CommonMacro.h"
#include "Snake.h"
#include "CommonUtil.h"
#include "GamePanel.h"
USING_NS_CC;
using namespace std;

EnemySnake::EnemySnake(GamePanel *gamePanel)
: Snake(gamePanel)
{

}

EnemySnake *EnemySnake::create(GamePanel *gamePanel)
{
	EnemySnake *snake = new EnemySnake(gamePanel);
	snake->init();
	snake->autorelease();
	return snake;
}

bool EnemySnake::init()
{
	return true;
}

void EnemySnake::onMove(cocos2d::CCPoint pos)
{
	const float detectSize = 50;

	if ((pos.x < detectSize && (90 < m_destAngle && m_destAngle < 270))
		|| (pos.x > GAME_LAYER_WIDTH - detectSize && (90 > m_destAngle || m_destAngle > 270)))
	{
		m_destAngle = 180 - m_destAngle;
	}
	else if (pos.y < detectSize && (m_destAngle > 180)
		|| (pos.y > GAME_LAYER_HEIGHT - detectSize && (m_destAngle < 180)))
	{
		m_destAngle = -m_destAngle;
	}

	m_destAngle = (m_destAngle + 360) % 360;
	detectCollision();
}

void EnemySnake::detectCollision()
{
	auto snakes = m_gamePanel->getSnakes();
	for (auto snake : snakes)
	{
		if (snake != this && snake->willCrash(m_body[0]->getPosition(), m_destAngle))
		{
			m_destAngle += CommonUtil::getRandomValue(90, 270);
			return;
		}
	}
}