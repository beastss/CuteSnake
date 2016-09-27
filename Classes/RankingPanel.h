#ifndef __RANKING_PANEL_H__
#define __RANKING_PANEL_H__
#include "cocos2d.h"

class RankingPanel
	: public cocos2d::CCNode
{
public:
	CREATE_FUNC(RankingPanel);
private:
	virtual bool init();
	void initData();
	void onUpdate(float dt);
private:
};

#endif