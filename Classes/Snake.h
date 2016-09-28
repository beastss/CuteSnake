#ifndef __SNAKE_H__
#define __SNAKE_H__
#include "cocos2d.h"
#include <deque>
#include "CommonMacro.h"
#include "SnakeSkinRes.h"

class UiLayout;
class GamePanel;

struct SnakeData
{
	int score;
	int skinId;
	int length;
	std::string name;
	SnakeData(int _score, int _skinId, int _length, std::string _name)
		:score(_score), skinId(_skinId), length(_length), name(_name)
	{
	}
	SnakeData()
	{
		score = 0;
		skinId = kFirstSkin;
		length = INIT_SNAKE_LENGTH;
	}
};

class Snake: public cocos2d::CCNode
{
public:
	virtual ~Snake(){}
	bool willCrash(cocos2d::CCPoint pt, int destAngle);
	bool isCrash(cocos2d::CCPoint pt);
	void update(float dt);
	bool canEatFood(cocos2d::CCPoint pt);
	void eatFood(int enery);
	CCNode *getHead(){ return m_body[0]; }
protected:
	Snake(GamePanel *gamePanel, const SnakeData &data = SnakeData());
	void initBodyPos(cocos2d::CCPoint pos);
	void addHead();
	void addBody();
	void addTail();
	void setGodLikeState(bool open);
protected:
	virtual void onMove(cocos2d::CCPoint pos){}
	virtual void onDead(){}
	virtual void onUpdate(float dt){}
	virtual void onEatFood(){}
private:
	virtual void onExit();
	cocos2d::CCNode *getTail(){ return m_body.back(); }
	void initSnake();
	bool checkCrash();
	void crash();
protected:
	int m_destAngle;
	float m_speed;
	std::deque<cocos2d::CCNode *>m_body;
	std::deque<cocos2d::CCPoint>m_path;
	GamePanel *m_gamePanel;
	bool m_isGodlike;
	SnakeData m_data;
	cocos2d::CCLabelTTF *m_nameLabel;
private:
	int m_angle;
	int m_growEnergy;
	cocos2d::CCSpriteBatchNode *m_batchNode;

};
#endif