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
	scale9->setContentSize(CCSize(width, height));

	height += 10;
	auto title = UiLayout::create("layout/ranking_title.xml");
	CCScale9Sprite * titleBk = CCScale9Sprite::create("game_scene/ranking_bk.png");
	titleBk->setAnchorPoint(ccp(0, 0));
	addChild(titleBk);
	titleBk->setContentSize(ccpAdd(title->getContentSize(), ccp(0, 5)));
	titleBk->setPosition(ccp(0, height));

	title->setPosition(0, height);
	height += title->getContentSize().height;
	width = max(width, title->getContentSize().width);
	addChild(title);

	setContentSize(CCSize(width, height));
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