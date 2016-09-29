#include "Food.h"
#include "CommonUtil.h"
#include "CommonMacro.h"
#include "CCFunctionAction.h"
USING_NS_CC;
using namespace std;

Food::Food(cocos2d::ccColor3B color)
: m_color(color)
{
	m_view = CCSprite::createWithSpriteFrameName("snake_food.png");
	m_enery = 1;
	m_view->setColor(m_color);
	m_view->setScale(0.5f);
}

Food::Food(std::string path)
{
	m_view = CCSprite::createWithSpriteFrameName(path.c_str());
	m_enery = 2;
	m_view->setScale(0.3f);
}

Food::~Food()
{

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