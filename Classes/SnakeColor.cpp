#include "SnakeColor.h"
USING_NS_CC;
using namespace std;

std::vector<cocos2d::ccColor3B> SnakeColor::m_colors;

void SnakeColor::init()
{
	m_colors.clear();
	m_colors.push_back(cocos2d::ccc3(0, 0, 0));
	m_colors.push_back(cocos2d::ccc3(255, 182, 193));
	m_colors.push_back(cocos2d::ccc3(70, 130, 180));
	m_colors.push_back(cocos2d::ccc3(220, 20, 60));
	m_colors.push_back(cocos2d::ccc3(238, 130, 238));
	m_colors.push_back(cocos2d::ccc3(106, 90, 205));
	m_colors.push_back(cocos2d::ccc3(0, 255, 255));
	m_colors.push_back(cocos2d::ccc3(127, 255, 170));
	m_colors.push_back(cocos2d::ccc3(0, 255, 0));
	m_colors.push_back(cocos2d::ccc3(255, 255, 0));
	m_colors.push_back(cocos2d::ccc3(128, 128, 0));
	m_colors.push_back(cocos2d::ccc3(255, 248, 220));
	m_colors.push_back(cocos2d::ccc3(255, 165, 0));
	m_colors.push_back(cocos2d::ccc3(255, 127, 80));
	m_colors.push_back(cocos2d::ccc3(135, 206, 235));
	m_colors.push_back(cocos2d::ccc3(255, 215, 0));
	m_colors.push_back(cocos2d::ccc3(128, 0, 0));
}

cocos2d::ccColor3B SnakeColor::getRandomColor()
{
	int index = CommonUtil::getRandomValue(0, m_colors.size() - 1);
	return m_colors[index];
}
