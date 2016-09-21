#ifndef __PLAYER_DATA_H__
#define __PLAYER_DATA_H__
#include "cocos2d.h"
#include "Snake.h"

class PlayerData
{
public:
	static PlayerData *theData();
	void reset();

	const SnakeData &getData(){ return m_data; }
	void setData(const SnakeData data){ m_data = data; }
private:
	SnakeData m_data;
};


#endif