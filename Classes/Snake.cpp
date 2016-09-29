#include "Snake.h"
#include "UiLayout.h"
#include <cmath>
#include "SnakeColor.h"
#include "CommonUtil.h"
#include "GamePanel.h"
#include "Food.h"
#include "RankingModel.h"
USING_NS_CC;
using namespace std;

Snake::Snake(GamePanel *gamePanel, const SnakeData &data)
: m_gamePanel(gamePanel)
, m_speed(NORMAL_SPEED)
, m_angle(0)
, m_destAngle(0)
, m_growEnergy(0)
, m_isGodlike(false)
, m_data(data)
{
	m_destAngle = CommonUtil::getRandomValue(0, 359);
	m_angle = m_destAngle;
	initSnake();
}

void Snake::onExit()
{
	CCNode::onExit();
	RankingModel::theModel()->removeRank(m_data.name);
	for (auto body : m_body)
	{
		body->removeFromParent();
	}
}

void Snake::initSnake()
{
	/*
	auto layout = UiLayout::create("layout/snake_head.xml");
	addChild(layout);
	layout->setAnchorPoint(ccp(0.5f, 0.4f));
	auto face = dynamic_cast<CCSprite*>(layout->getChildById(1));
	//face->initWithFile("snake/dsf.png");
	face->setColor(m_data.color);
	auto leftEyeBall = dynamic_cast<CCSprite*>(layout->getChildById(3));
	leftEyeBall->setColor(ccc3(0, 0, 0));
	auto RightEyeBall = dynamic_cast<CCSprite*>(layout->getChildById(5));
	RightEyeBall->setColor(ccc3(0, 0, 0));
	*/
	
	addHead();
	addTail();
	for (int i = 1; i < m_data.length - 1; ++i)
	{
		addBody();
	}
	
}

void Snake::addHead()
{
	auto path = SnakeSkinRes::SnakeResData()->getHeadRes(m_data.skinId);
	auto head = CCSprite::createWithSpriteFrameName(SnakeSkinRes::SnakeResData()->getHeadRes(m_data.skinId).c_str());
	m_gamePanel->getSnakeBatch()->addChild(head);

	m_nameLabel = CCLabelTTF::create("", "Arial", 17);
	m_nameLabel->setColor(ccc3(0, 0, 0));
	addChild(m_nameLabel, 1);
	m_body.push_back(head);
}

void Snake::addBody()
{
	/*
	CCSprite *body = CCSprite::createWithTexture(m_batchNode->getTexture());
	body->setScale(1.5f);
	m_batchNode->addChild(body);
	body->setColor(m_data.color);
	body->setPosition(m_body.back()->getPosition());
	m_body.push_back(body);
	*/
	int pos = m_body.size() + 1;
	auto path = SnakeSkinRes::SnakeResData()->getBodyRes(m_data.skinId, pos);
	CCSprite *body = CCSprite::createWithSpriteFrameName(SnakeSkinRes::SnakeResData()->getBodyRes(m_data.skinId, pos).c_str());
	m_gamePanel->getSnakeBatch()->addChild(body, -pos);
	body->setPosition(m_body.back()->getPosition());
	m_body.insert(m_body.begin() + m_body.size() - 1, body);
}

void Snake::addTail()
{
	auto path = SnakeSkinRes::SnakeResData()->getTailRes(m_data.skinId);
	auto tail = CCSprite::createWithSpriteFrameName(SnakeSkinRes::SnakeResData()->getTailRes(m_data.skinId).c_str());
	m_gamePanel->getSnakeBatch()->addChild(tail);
	m_body.push_back(tail);
}

void Snake::initBodyPos(cocos2d::CCPoint pos)
{
	for (auto body : m_body)
	{
		body->setPosition(pos);
	}
}

void Snake::update(float dt)
{
	//更新蛇长度
	m_data.length = m_body.size();
	//移动方向
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
	getHead()->setRotation(90 - m_angle);//头部选中
	auto tail2Pos = m_body[m_body.size() - 2]->getPosition();
	auto tail1Pos = m_body[m_body.size() - 1]->getPosition();
	int rotation = CommonUtil::getRotation(tail2Pos, tail1Pos);
	getTail()->setRotation(180 - rotation);
	//CCLOG("m_angle: %d", m_angle);
	
	CCPoint offset;
	offset.x = cos(m_angle * M_PI / 180) *dt * m_speed;
	offset.y = sin(m_angle * M_PI / 180) *dt * m_speed;
	auto pos = ccpAdd(getHead()->getPosition(), offset);
	getHead()->setPosition(pos);
	m_nameLabel->setPosition(ccpAdd(pos, ccp(0, 30)));
	m_path.push_front(pos);
	onMove(pos);

	const int kOffset = 8;//相邻两个body的距离
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
	if (m_isGodlike)//如果无敌，不检测与其他蛇碰撞
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
	pt.x = CommonUtil::getRandomValue(0, 10);
	pt.y = CommonUtil::getRandomValue(0, 10);
	return pt;
}

void Snake::crash()
{
	onDead();
	for (size_t i = 0; i < m_body.size(); ++i)
	{
		auto body = m_body[i];
		auto pos = body->getPosition();
		auto path = SnakeSkinRes::SnakeResData()->getBodyRes(m_data.skinId, i + 1);
		m_gamePanel->addFood(path, ccpAdd(pos, getRandomPt()));
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
	return abs(pos.x - pt.x) < 42 && abs(pos.y - pt.y) < 44;
}

void Snake::eatFood(int energy)
{
	RankingModel::theModel()->updateScore(m_data.name, m_data.score);
	m_data.score += energy * 10;
	int const kEnergyToGrow = 10;
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