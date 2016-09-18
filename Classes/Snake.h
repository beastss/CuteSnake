#ifndef __SNAKE_H__
#define __SNAKE_H__
#include "cocos2d.h"
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
protected:
	Snake(GamePanel *gamePanel);
	void addBody();
	CCNode *getHead(){ return m_body[0]; }
protected:
	virtual void onMove(cocos2d::CCPoint pos){}
	virtual void onDead(){}
private:
	void initSnake();
	void update(float dt);
	bool checkCrash();
	void crash();
protected:
	cocos2d::ccColor3B m_color;
	int m_length;
	int m_destAngle;
	float m_speed;
	std::vector<cocos2d::CCNode *>m_body;
	std::vector<cocos2d::CCPoint>m_path;
	GamePanel *m_gamePanel;
private:
	int m_angle;
};
#endif