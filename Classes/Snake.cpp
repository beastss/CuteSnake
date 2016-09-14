#include "Snake.h"
#include "UiLayout.h"
#include "CommonMacro.h"
#include <cmath>
USING_NS_CC;
using namespace std;

Snake::Snake()
: m_length(5)
, m_color(LIGHT_PINK)
, m_speed(100)
, m_angle(0)
, m_destAngle(0)
{
	initSnake();
	for (int i = 0; i < m_length; ++i)
	{
		addBody();
	}
}

void Snake::initSnake()
{
	m_head = UiLayout::create("layout/snake_head.xml");
	addChild(m_head);
	m_head->setAnchorPoint(ccp(0.5f, 0));
	auto face = dynamic_cast<CCSprite*>(m_head->getChildById(1));
	//face->initWithFile("snake/dsf.png");
	//face->setColor(m_color);
	auto leftEyeBall = dynamic_cast<CCSprite*>(m_head->getChildById(3));
	leftEyeBall->setColor(BLACK);
	auto RightEyeBall = dynamic_cast<CCSprite*>(m_head->getChildById(5));
	RightEyeBall->setColor(BLACK);
	m_body.push_back(m_head);

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
	const float kNodeDistance = 16;
	
	int angleOffset = m_angle - m_destAngle;
	if (abs(angleOffset) < 10)
	{
		m_angle = m_destAngle;
	}
	else if (sin(angleOffset) > 0)
	{
		m_angle -= 500 * dt;//ÄæÊ±Õë
	}
	else
	{
		m_angle += 500 * dt;//Ë³Ê±Õë
	}
	m_angle = (m_angle + 360)% 360;
	/*
	else if ((0 < (angleOffset) && (angleOffset < 180)) || (angleOffset < -180))
	{
		m_angle -= 500 * dt;//ÄæÊ±Õë
	}
	else
	{
		m_angle += 500 * dt;//Ë³Ê±Õë
	}
	*/

	m_head->setRotation(90 - m_angle);
	
	CCPoint offset;
	offset.x = cos(m_angle * M_PI / 180) *dt * m_speed;
	offset.y = sin(m_angle * M_PI / 180) *dt * m_speed;
	m_body[0]->setPosition(ccpAdd(m_body[0]->getPosition(), offset));

	for (size_t i = 1; i < m_body.size(); ++i)
	{
		auto pos = m_body[i - 1]->getPosition();
		auto curPos = m_body[i]->getPosition();
		auto distance = ccpDistance(pos, curPos);
		//if (distance >= kNodeDistance)
		if (true)
		{
			float dx = pos.x - curPos.x;
			float dy = pos.y - curPos.y;
			auto newPos = curPos;
			newPos.x += (distance - kNodeDistance) / distance * dx;
			newPos.y += (distance - kNodeDistance) / distance * dy;
			m_body[i]->setPosition(newPos);
		}
		else
		{
			break;
		}
	}
}