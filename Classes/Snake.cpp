#include "Snake.h"
#include "UiLayout.h"
#include "CommonMacro.h"
#include <cmath>
#include "SnakeColor.h"
#include "CommonUtil.h"
#include "GamePanel.h"
#include "Food.h"
USING_NS_CC;
using namespace std;

Snake::Snake(GamePanel *gamePanel)
: m_gamePanel(gamePanel)
, m_speed(NORMAL_SPEED)
, m_angle(0)
, m_destAngle(0)
, m_growEnergy(0)
, m_isGodlike(false)
, m_score(0)
{
	m_color = RANDOM_COLOR;
	m_destAngle = CommonUtil::getRandomValue(0, 359);
	m_angle = m_destAngle;
	initSnake();
}

void Snake::initSnake()
{
	auto layout = UiLayout::create("layout/snake_head.xml");
	addChild(layout);
	layout->setAnchorPoint(ccp(0.5f, 0.4f));
	auto face = dynamic_cast<CCSprite*>(layout->getChildById(1));
	//face->initWithFile("snake/dsf.png");
	face->setColor(m_color);
	auto leftEyeBall = dynamic_cast<CCSprite*>(layout->getChildById(3));
	leftEyeBall->setColor(ccc3(0, 0, 0));
	auto RightEyeBall = dynamic_cast<CCSprite*>(layout->getChildById(5));
	RightEyeBall->setColor(ccc3(0, 0, 0));
	m_body.push_back(layout);

	for (int i = 1; i < INIT_SNAKE_LENGTH; ++i)
	{
		addBody();
	}
}

void Snake::addBody()
{
	CCSprite *body = CCSprite::create("snake/circle.png");
	body->setScale(1.5f);
	addChild(body);
	body->setColor(m_color);
	body->setPosition(m_body[m_body.size() - 1]->getPosition());
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
		m_angle += 500 * dt;//��ʱ��
	}
	else
	{
		m_angle -= 500 * dt;//˳ʱ��
	}

	m_angle = (m_angle + 360) % 360;
	getHead()->setRotation(90 - m_angle);//ͷ��ѡ��
	//CCLOG("m_angle: %d", m_angle);
	
	CCPoint offset;
	offset.x = cos(m_angle * M_PI / 180) *dt * m_speed;
	offset.y = sin(m_angle * M_PI / 180) *dt * m_speed;
	auto pos = ccpAdd(getHead()->getPosition(), offset);
	getHead()->setPosition(pos);
	m_path.push_front(pos);
	onMove(pos);

	const int kOffset = 5;//��������body�ľ���
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
		deque<CCPoint> temp;
		temp.swap(m_path);
		m_path.assign(temp.begin(), temp.end() - extra);

	}
	//CCLOG("m_path.size(): %d", m_path.size());
	onUpdate(dt);
	if (checkCrash())
	{
		crash();
	}

}

void Snake::setGodLikeState(bool open)
{
	m_isGodlike = open;
	for (auto body : m_body)
	{
		auto self = dynamic_cast<CCSprite *>(body);
		if (self)
		{
			self->setOpacity(open ? 128 : 255);
		}

		auto children = body->getChildren();
		CCObject* pObj;
		CCARRAY_FOREACH(children, pObj)
		{
			CCSprite* pNode = dynamic_cast<CCSprite*>(pObj);
			if (pNode)
			{
				pNode->setOpacity(open ? 128 : 255);
			}
		}
	}
}

bool Snake::checkCrash()
{
	auto pos = getHead()->getPosition();
	if (pos.x < 0 || pos.x > GAME_LAYER_WIDTH || pos.y < 0 || pos.y > GAME_LAYER_HEIGHT)
	{
		return true;
	}
	if (m_isGodlike)//����޵У����������������ײ
	{
		return false;
	}

	auto snakes = m_gamePanel->getSnakes();
	for (auto snake : snakes)
	{
		if (snake != this && snake->isCrash(getHead()->getPosition()))
		{
			return true;
		}
	}
	return false;
}

static CCPoint getRandomPt()
{
	CCPoint pt;
	pt.x = CommonUtil::getRandomValue(0, 5);
	pt.y = CommonUtil::getRandomValue(0, 5);
	return pt;
}

void Snake::crash()
{
	onDead();
	for (auto body : m_body)
	{
		auto pos = body->getPosition();
		auto food = Food::create(m_color, true);
		food->setPosition(ccpAdd(pos, getRandomPt()));
		m_gamePanel->addFood(food);
		food = Food::create(m_color, true);
		food->setPosition(ccpAdd(pos, getRandomPt()));
		m_gamePanel->addFood(food);
	}

	m_gamePanel->removeSnake(this);
	CCLOG("Snake::crash!!!!");
}

bool Snake::willCrash(cocos2d::CCPoint pt, int destAngle)
{
	for (size_t i = 0; i < m_body.size(); ++i)
	{
		int angle = 0;
		float dy = m_body[i]->getPosition().y - pt.y;
		float dx = m_body[i]->getPosition().x - pt.x;
		if (abs(dx) > 200 || abs(dy) > 200) return false;
		if (dx == 0)
		{
			if (dy > 0) angle = 90;
			else angle = -90;
		}
		else
		{
			angle = atan(dy / dx) * 180 / M_PI;
			if (dx < 0) angle += 180;
		}

		angle = (angle + 360) % 360;
		if (abs(angle - destAngle) < 10)
		{
			return true;
		}
	}
	return false;
}

bool Snake::isCrash(cocos2d::CCPoint pt)
{
	for (auto body : m_body)
	{
		auto pos = body->getPosition();
		auto dis = ccpDistance(pos, pt);
		if (dis < 40)
		{
			return true;
		}
	}
	return false;
}

bool Snake::canEatFood(CCPoint pt)
{
	auto pos = getHead()->getPosition();
	return abs(pos.x - pt.x) < 32 && abs(pos.y - pt.y) < 32;
}

void Snake::eatFood(int energy)
{
	m_score += energy * 10;
	int const kEnergyToGrow = 5;
	m_growEnergy += energy;
	if (m_growEnergy >= kEnergyToGrow)
	{
		int num = m_growEnergy / kEnergyToGrow;
		m_growEnergy = m_growEnergy % kEnergyToGrow;
		for (int i = 0; i < num; ++i)
		{
			addBody();
		}
	}
	onEatFood();
}