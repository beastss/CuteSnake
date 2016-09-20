#ifndef __RANKING_PANEL_H__
#define __RANKING_PANEL_H__
#include "cocos2d.h"
#include <unordered_map>

class RankingPanel
	: public cocos2d::CCNode
{
public:
	CREATE_FUNC(RankingPanel);
private:
	virtual bool init();
	void initData();
private:
	std::unordered_map<std::string, int> m_ranking;
};

#endif