#include "PlayerData.h"
#include "CommonMacro.h"
#include "GameConfig.h"
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
	string name = GameConfigSelf->getStrValue("common", "player_name");
	return name;
}
