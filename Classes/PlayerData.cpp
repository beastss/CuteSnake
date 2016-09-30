#include "PlayerData.h"
#include "CommonMacro.h"
#include "GameConfig.h"
#include "SavingHelper.h"
#include "CommonUtil.h"
USING_NS_CC;
using namespace std;

PlayerData *PlayerData::theData()
{
	static PlayerData mgr;
	return &mgr;
}

void PlayerData::reset()
{
	m_data = SnakeData();
}

std::string PlayerData::getName()
{
	auto name = SAVING->getName();
	if (name.empty())
	{
		name = GameConfigSelf->getStrValue("common", "player_name");
		for (int i = 0; i < 5; ++i)
		{
			name += CommonUtil::intToStr(CommonUtil::getRandomValue(0, 9));
		}
		SAVING->saveName(name.c_str());
	}
	return name;
}
