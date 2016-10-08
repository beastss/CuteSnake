#include "EnemySnake.h"
#include "CommonMacro.h"
#include "Snake.h"
#include "CommonUtil.h"
#include "GamePanel.h"
#include "RankingModel.h"
USING_NS_CC;
using namespace std;

EnemySnake::EnemySnake(GamePanel *gamePanel)
: Snake(gamePanel)
{

}

void EnemySnake::onExit()
{
	Snake::onExit();
	RankingModel::theModel()->removeRank(m_data.name);
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
	CCPoint pos;
	pos.x = CommonUtil::getRandomValue(0, GAME_LAYER_WIDTH);
	pos.y = CommonUtil::getRandomValue(0, GAME_LAYER_HEIGHT);
	initBodyPos(pos);

	if (m_data.name.empty())
	{
		m_data.name = RankingModel::theModel()->applyName();
	}
	m_nameLabel->setString(m_data.name.c_str());
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


void EnemySnake::onDead()
{
	auto snake = EnemySnake::create(m_gamePanel);
	m_gamePanel->addSnake(snake);
}

void EnemySnake::detectCollision()
{
	auto snakes = m_gamePanel->getSnakes();
	for (auto snake : snakes)
	{
		if (snake != this && snake->willCrash(getHead()->getPosition(), m_destAngle))
		{
			m_destAngle += CommonUtil::getRandomValue(90, 270);
			return;
		}
	}
}