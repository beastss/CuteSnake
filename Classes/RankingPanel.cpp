#include "RankingPanel.h"
#include "UiLayout.h"
#include "cocos-ext.h"
#include "CommonUtil.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

bool RankingPanel::init()
{
	initData();
	CCScale9Sprite * scale9 = CCScale9Sprite::create("game_scene/ranking_bk.png");
	scale9->setAnchorPoint(ccp(0, 0));
	addChild(scale9);

	float width = 0;
	float height = 0;
	for (auto iter = m_ranking.rbegin(); iter != m_ranking.rend(); ++iter)
	{
		auto node = UiLayout::create("layout/ranking_node.xml");
		auto name = dynamic_cast<CCLabelTTF *>(node->getChildById(1));
		name->setString((iter->first).c_str());
		auto score = dynamic_cast<CCLabelTTF *>(node->getChildById(2));
		score->setString(CommonUtil::intToStr(iter->second));
		node->setPosition(0, height);
		addChild(node);
		height += node->getContentSize().height;
		width = max(width, node->getContentSize().width);
	}

	setContentSize(CCSize(width, height));
	scale9->setContentSize(getContentSize());
	return true;
}

void RankingPanel::initData()
{
	m_ranking["a_kiejge"] = 3550;
	m_ranking["b_sdkf"] = 3520;
	m_ranking["funny66"] = 3200;
	m_ranking["april"] = 3020;
	m_ranking["15james"] = 2800;
	m_ranking["jasony"] = 2750;
	m_ranking["tonny"] = 2650;
	m_ranking["_goodns"] = 2550;
}