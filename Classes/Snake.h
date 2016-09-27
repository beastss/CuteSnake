#ifndef __SNAKE_H__
#define __SNAKE_H__
#include "cocos2d.h"
#include <deque>
#include "CommonMacro.h"
#include "SnakeColor.h"

class UiLayout;
class GamePanel;

struct SnakeData
{
	int score;
	cocos2d::ccColor3B color;
	int length;
	std::string name;
	SnakeData(int _score, cocos2d::ccColor3B _color, int _length, std::string _name)
		:score(_score), color(_color), length(_length), name(_name)
	{
	}
	SnakeData()
	{
		score = 0;
		color = RANDOM_COLOR;
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
	void addBody();
	void setGodLikeState(bool open);
protected:
	virtual void onMove(cocos2d::CCPoint pos){}
	virtual void onDead(){}
	virtual void onUpdate(float dt){}
	virtual void onEatFood(){}
private:
	virtual void onExit();
	void initSnake();
	bool checkCrash();
	void crash();
protected:
	int m_destAngle;
	float m_speed;
	std::vector<cocos2d::CCNode *>m_body;
	std::deque<cocos2d::CCPoint>m_path;
	GamePanel *m_gamePanel;
	bool m_isGodlike;
	SnakeData m_data;
private:
	int m_angle;
	int m_growEnergy;
	cocos2d::CCSpriteBatchNode *m_batchNode;
	cocos2d::CCLabelTTF *nameLabel;
};
#endif