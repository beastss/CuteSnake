#ifndef __SNAKE_H__
#define __SNAKE_H__
#include "cocos2d.h"
#include <deque>
#include "CommonMacro.h"
/*
class SnakeNode
{
public:
	static SnakeNode *create(cocos2d::ccColor3B color, );
	void updateNextNode();
private:
	virtual bool init();
private:
	SnakeNode *m_nextNode;
};
*/
class UiLayout;
class GamePanel;
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
	Snake(GamePanel *gamePanel, int length);
	void addBody();
	void setGodLikeState(bool open);
protected:
	virtual void onMove(cocos2d::CCPoint pos){}
	virtual void onDead(){}
	virtual void onUpdate(float dt){}
	virtual void onEatFood(){}
private:
	void initSnake(int length);
	bool checkCrash();
	void crash();
protected:
	cocos2d::ccColor3B m_color;
	int m_destAngle;
	float m_speed;
	std::vector<cocos2d::CCNode *>m_body;
	std::deque<cocos2d::CCPoint>m_path;
	GamePanel *m_gamePanel;
	bool m_isGodlike;
	int m_score;
private:
	int m_angle;
	int m_growEnergy;
};
#endif