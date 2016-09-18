#include "RankingPanel.h"
#include "UiLayout.h"
USING_NS_CC;
using namespace std;

bool RankingPanel::init()
{
	auto bk = CCLayerColor::create(ccc4(0, 255, 0, 120));
	addChild(bk);

	float width = 0;
	float height = 0;
	for (int i = 0; i < 5; i++)
	{
		auto node = UiLayout::create("layout/ranking_node.xml");
		auto name = dynamic_cast<CCLabelTTF *>(node->getChildById(1));
		auto score = dynamic_cast<CCLabelTTF *>(node->getChildById(2));
		node->setPosition(0, height);
		addChild(node);
		height += node->getContentSize().height;
		width = max(width, node->getContentSize().width);
	}

	setContentSize(CCSize(width, height));
	bk->setContentSize(getContentSize());
	return true;
}