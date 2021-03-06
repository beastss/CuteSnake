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
, m_isSpeedUp(false)
, m_scale(0.5f)
{
	m_destAngle = CommonUtil::getRandomValue(0, 359);
	m_angle = m_destAngle;
	initSnake();
}

void Snake::onExit()
{
	CCNode::onExit();
	for (auto body : m_body)
	{
		body->removeFromParent();
	}
}

void Snake::initSnake()
{
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
	head->setScale(m_scale);
	m_gamePanel->getSnakeBatch()->addChild(head);

	m_nameLabel = CCLabelTTF::create("", "Arial", 17);
	m_nameLabel->setColor(ccc3(0, 0, 0));
	addChild(m_nameLabel, 1);
	m_body.push_back(head);
}

void Snake::addBody()
{
	int pos = m_body.size() + 1;
	auto path = SnakeSkinRes::SnakeResData()->getBodyRes(m_data.skinId, pos);
	CCSprite *body = CCSprite::createWithSpriteFrameName(SnakeSkinRes::SnakeResData()->getBodyRes(m_data.skinId, pos).c_str());
	body->setScale(m_scale);
	m_gamePanel->getSnakeBatch()->addChild(body, -pos);
	body->setPosition(m_body.back()->getPosition());
	m_body.insert(m_body.begin() + m_body.size() - 1, body);
}

void Snake::addTail()
{
	auto path = SnakeSkinRes::SnakeResData()->getTailRes(m_data.skinId);
	auto tail = CCSprite::createWithSpriteFrameName(SnakeSkinRes::SnakeResData()->getTailRes(m_data.skinId).c_str());
	tail->setScale(m_scale);
	m_gamePanel->getSnakeBatch()->addChild(tail, -9999);
	m_body.push_back(tail);
}

void Snake::removeBody()
{
	if (m_body.size() <= 2) return; //只剩下头和尾
	//m_body[m_body->size() - 1]
	m_body[m_body.size() - 2]->removeFromParent();
	m_body.erase(m_body.begin() + m_body.size() - 2);
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
	for (auto body : m_body)
	{
		m_scale = min((m_body.size() / 50.0f), 1.0f) * 0.3f + 0.4f;
		body->setScale(m_scale);
	}

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
	//旋转头，身体
	m_angle = (m_angle + 360) % 360;
	//CCLOG("m_angle: %d", m_angle);
	getHead()->setRotation(90 - m_angle);//头部选中
	for (size_t i = 1; i < m_body.size(); ++i)
	{
		auto pos1 = m_body[i - 1]->getPosition();
		auto pos2 = m_body[i]->getPosition();
		int rotation = CommonUtil::getRotation(pos1, pos2);
		m_body[i]->setRotation(270 - rotation);
	}
	
	//更新头部坐标
	CCPoint offset;
	offset.x = cos(m_angle * M_PI / 180) *dt * m_speed;
	offset.y = sin(m_angle * M_PI / 180) *dt * m_speed;
	auto pos = ccpAdd(getHead()->getPosition(), offset);
	getHead()->setPosition(pos);
	m_nameLabel->setPosition(ccpAdd(pos, ccp(0, 40)));
	m_path.push_front(make_pair(pos, 0));
	onMove(pos);

	for (size_t i = 1; i < m_path.size(); ++i)
	{
		m_path[i].second += dt * m_speed;
	}
	//遍历所有蛇节点，在指定长度上更新位置
	const float kDistance = 30 * m_scale;
	int curIndex = 1;
	for (size_t bodyIndex = 1; bodyIndex < m_body.size(); ++bodyIndex)
	{
		for (int i = curIndex; i < m_path.size(); ++i)
		{
			auto length = m_path[i].second;
			curIndex = i;
			if (length >= kDistance * bodyIndex)
			{
				auto prevPos = m_path[i - 1].first;
				auto myPos = m_path[i].first;
				int dx = myPos.x - prevPos.x;
				int dy = myPos.y - prevPos.y;
				auto distance = ccpDistance(prevPos, myPos);
				auto newPos = ccpAdd(prevPos, ccpMult(ccp(dx, dy), (kDistance * bodyIndex - m_path[i - 1].second) / distance));
				m_body[bodyIndex]->setPosition(newPos);
				break;
			}
		}
	}

	int newSize = m_path.size();
	for (int i = 1; i < m_path.size(); ++i)
	{
		if (m_path[i].second > kDistance *(m_body.size() - 1))
		{
			newSize = i + 1;
			break;
		}
	}
	
	m_path.resize(newSize);
	CCLOG("m_path.size(): %d", m_path.size());

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