#include "Food.h"
#include "CommonUtil.h"
#include "CommonMacro.h"
#include "CCFunctionAction.h"
USING_NS_CC;
using namespace std;

Food *Food::create(cocos2d::CCPoint pos, cocos2d::ccColor3B color)
{
	auto food = new Food(pos, color);
	food->init();
	food->autorelease();
	return food;
}

bool Food::init()
{
	CCSprite *dot = CCSprite::create("snake/circle.png");
	//dot->setScale(0.5f);
	auto size = dot->boundingBox().size;
	dot->setPosition(ccpMult(size, 0.5f));
	dot->setColor(m_color);
	addChild(dot);
	setContentSize(size);
	setPosition(m_pos);
	
	return true;
}

void Food::onEaten(CCPoint pt)
{
	auto move = CCMoveTo::create(0.3f, pt);
	auto func = CCFunctionAction::create([=]()
	{
		removeFromParent();
	});
	auto seq = CCSequence::create(move, func, NULL);
	runAction(seq);
}