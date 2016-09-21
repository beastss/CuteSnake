#include "PlayerData.h"
#include "CommonMacro.h"
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

