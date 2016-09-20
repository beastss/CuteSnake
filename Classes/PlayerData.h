#ifndef __PLAYER_DATA_H__
#define __PLAYER_DATA_H__
#include "cocos2d.h"

class PlayerData
{
public:
	static PlayerData *theData();
	void reset();

	void setScore(int score){ m_score = score; }
	int getScore(){ return m_score; }
	void setLength(int length){ m_length = length; }
	int getLength(){ return m_length; }
private:
	int m_length;
	int m_score;
};


#endif