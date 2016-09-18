#include "Snake.h"
#include "UiLayout.h"
#include "CommonMacro.h"
#include <cmath>
#include "SnakeColor.h"
#include "..\CoolSatrs\Classes\CommonUtil.h"
USING_NS_CC;
using namespace std;

Snake::Snake(GamePanel *gamePanel)
: m_gamePanel(gamePanel)
, m_length(5)
, m_speed(NORMAL_SPEED)
, m_angle(0)
, m_destAngle(0)
{
	m_color = RANDOM_COLOR;
	m_destAngle = CommonUtil::getRandomValue(0, 359);
	m_angle = m_destAngle;
	initSnake();
}

void Snake::initSnake()
{
	m_head = UiLayout::create("layout/snake_head.xml");
	addChild(m_head);
	m_head->setAnchorPoint(ccp(0.5f, -0.2f));
	auto face = dynamic_cast<CCSprite*>(m_head->getChildById(1));
	//face->initWithFile("snake/dsf.png");
	face->setColor(m_color);
	auto leftEyeBall = dynamic_cast<CCSprite*>(m_head->getChildById(3));
	leftEyeBall->setColor(ccc3(0, 0, 0));
	auto RightEyeBall = dynamic_cast<CCSprite*>(m_head->getChildById(5));
	RightEyeBall->setColor(ccc3(0, 0, 0));
	m_body.push_back(m_head);

	auto size = CCSize(GAME_LAYER_WIDTH, GAME_LAYER_HEIGHT);
	m_head->setPosition(ccpMult(size, 0.5f));

	for (int i = 0; i < m_length; ++i)
	{
		addBody();
	}
	scheduleUpdate();
}

void Snake::addBody()
{
	CCSprite *body = CCSprite::create("snake/circle.png");
	addChild(body);
	body->setColor(m_color);
	body->setPosition(m_body.back()->getPosition());
	m_body.push_back(body);
}

void Snake::update(float dt)
{
	int angleOffset = m_destAngle - m_angle;
	if (abs(angleOffset) < 5)
	{
		m_angle = m_destAngle;
	}
	else if ((0 < angleOffset && angleOffset < 180) || angleOffset < -180)
	{
		m_angle += 500 * dt;//逆时针
	}
	else
	{
		m_angle -= 500 * dt;//顺时针
	}

	m_angle = (m_angle + 360) % 360;
	m_head->setRotation(90 - m_angle);//头部选中
	//CCLOG("m_angle: %d", m_angle);
	
	CCPoint offset;
	offset.x = cos(m_angle * M_PI / 180) *dt * m_speed;
	offset.y = sin(m_angle * M_PI / 180) *dt * m_speed;
	auto pos = ccpAdd(m_body[0]->getPosition(), offset);
	m_body[0]->setPosition(pos);
	m_path.push_back(pos);
	onMove(pos);

	const int kOffset = 10;//相邻两个body的距离
	for (size_t i = 1; i < m_body.size(); ++i)
	{
		if (m_path.size() > i * kOffset)
		{
			m_body[i]->setPosition(m_path[i * kOffset]);
		}
		else
		{
			break;
		}
	}
	int extra = m_path.size() - (m_body.size() - 1 )* kOffset;
	if (extra > 0)
	{
		vector<CCPoint> temp;
		temp.swap(m_path);
		m_path.assign(temp.begin() + extra, temp.end());

	}
	//CCLOG("m_path.size(): %d", m_path.size());
	
	if (checkCrash())
	{
		runDeadAction();
	}
}

bool Snake::checkCrash()
{
	auto pos = m_body[0]->getPosition();
	if (pos.x < 0 || pos.x > GAME_LAYER_WIDTH || pos.y < 0 || pos.y > GAME_LAYER_HEIGHT)
	{
		return true;
	}
	return false;
}

void Snake::runDeadAction()
{
	onDead();
	removeFromParent();
}