#include "JoyStick.h"
#include <cmath>
USING_NS_CC;
using namespace std;

void JoyStick::onEnter()
{
	CCNode::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void JoyStick::onExit()
{
	CCNode::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

bool JoyStick::init()
{
	m_bg = CCSprite::create("joy_stick/bg.png");
	m_bg->setPosition(ccp(100, 100));
	addChild(m_bg);

	m_slider = CCSprite::create("joy_stick/slider.png");
	addChild(m_slider);

	resetSlider();
	return true;
}

void JoyStick::resetSlider()
{
	m_slider->setPosition(m_bg->getPosition());
}

bool JoyStick::handleTouch(cocos2d::CCPoint pt)
{
	auto touchPos = convertToNodeSpace(pt);
	auto centerPos = m_bg->getPosition();
	auto radius = m_bg->getContentSize().height * 0.5f;
	if (ccpDistance(touchPos, centerPos) <= radius)
	{
		m_slider->setPosition(touchPos);
		return true;
	}
	return false;
}

bool JoyStick::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	auto pos = convertToNodeSpace(pTouch->getLocation());
	if(m_slider->boundingBox().containsPoint(pos))
	{
		return true;
	}
}

void JoyStick::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	auto curPos = convertToNodeSpace(pTouch->getLocation());
	auto prePos = convertToNodeSpace(pTouch->getPreviousLocation());

	auto centerPos = m_bg->getPosition();
	auto radius = m_bg->getContentSize().height * 0.5f;
	auto targetPos = ccpAdd(m_slider->getPosition(), ccpSub(curPos, prePos));
	
	float distance = ccpDistance(targetPos, centerPos);
	float dx = targetPos.x - centerPos.x;
	float dy = targetPos.y - centerPos.y;
	if (distance > radius)
	{
		targetPos.x = centerPos.x + dx * radius / distance;
		targetPos.y = centerPos.y + dy * radius / distance;
	}
	m_slider->setPosition(targetPos);
	if (m_handle)
	{
		CCPoint delta = ccp(dx, dy);
		m_handle(delta.normalize());
	}
}

void JoyStick::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	resetSlider();
}

void setHandle(std::function<void()>);