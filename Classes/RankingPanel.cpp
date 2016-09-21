#include "RankingPanel.h"
#include "UiLayout.h"
#include "cocos-ext.h"
#include "CommonUtil.h"
#include <utility>
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
	for (auto iter = m_ranking.begin(); iter != m_ranking.end(); ++iter)
	{
		auto node = UiLayout::create("layout/ranking_node.xml");
		auto name = dynamic_cast<CCLabelTTF *>(node->getChildById(1));
		name->setString((iter->second).c_str());
		auto score = dynamic_cast<CCLabelTTF *>(node->getChildById(2));
		score->setString(CommonUtil::intToStr(iter->first));
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
	m_ranking.insert(make_pair(3550, "a_kiejge"));
	m_ranking.insert(make_pair(3520, "b_sdkf"));
	m_ranking.insert(make_pair(3200, "funny66"));
	m_ranking.insert(make_pair(3020, "april"));
	m_ranking.insert(make_pair(2800, "15james"));
	m_ranking.insert(make_pair(2750, "jasony"));
	m_ranking.insert(make_pair(2650, "tonny"));
	m_ranking.insert(make_pair(2550, "_goodns"));
}