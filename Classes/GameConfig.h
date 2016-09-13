#ifndef __GAME_CONFIG_H__
#define __GAME_CONFIG_H__
#include "cocos2d.h"

class GameConfig
{
public:
	static GameConfig *theModel();
	std::string getValue(std::string key);
};

#define GameConfigSelf GameConfig::theModel()
#endif