#include "Food.h"
#include "CommonUtil.h"
#include "CommonMacro.h"
#include "CCFunctionAction.h"
USING_NS_CC;
using namespace std;

Food::Food(cocos2d::ccColor3B color, bool isSnakeBody)
: m_color(color)
, m_isSnakeBody(isSnakeBody)
{
	init();
}

Food::~Food()
{

}

void Food::init()
{
	m_view = CCSprite::create("snake/circle.png");
	if (m_isSnakeBody)
	{
		m_enery = 2;
	}
	else
	{
		m_enery = 1;
		m_view->setScale(0.5f);
	}
	m_view->setColor(m_color);
	
}

void Food::onEaten(CCPoint pt)
{
	auto move = CCMoveTo::create(0.3f, pt);
	auto func = CCFunctionAction::create([=]()
	{
		m_view->removeFromParent();
		delete this;
	});
	auto seq = CCSequence::create(move, func, NULL);
	m_view->runAction(seq);
}