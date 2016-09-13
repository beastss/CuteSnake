#include "GameConfig.h"
USING_NS_CC;
using namespace std;

GameConfig *GameConfig::theModel()
{
	static GameConfig model;
	return &model;
}

std::string GameConfig::getValue(std::string key)
{
	string value;

	return value;
}