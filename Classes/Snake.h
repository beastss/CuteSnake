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

class Snake: public cocos2d::CCNode
{
public:
	virtual ~Snake(){}
protected:
	Snake();
protected:
	void initSnake();
	void addBody();
private:
	void update(float dt);
protected:
	cocos2d::ccColor3B m_color;
	int m_length;
	int m_destAngle;
	float m_speed;
	UiLayout *m_head;
	std::vector<cocos2d::CCNode *>m_body;
	std::vector<cocos2d::CCPoint>m_path;
private:
	int m_angle;
};
#endif