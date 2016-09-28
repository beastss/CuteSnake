#ifndef __COMMONUTIL_H__
#define __COMMONUTIL_H__
#include "cocos2d.h"
namespace CommonUtil
{	
	std::vector<std::string> split(std::string str, std::string pattern);
	std::vector<int> parseStrToInts(std::string str);//������ 1,2,3 ���ַ����ָ��Ϊ������
	std::string parseIntsToStr(const std::vector<int> &values);
	std::vector<float> parseStrToFloats(std::string str);

	const char *intToStr(int value);

	int getRandomValue(int begin, int end);
	bool floatEqual(float v1, float v2);
	std::vector<int> buildRandomSequence(int length);
	int getResultByPercent(const std::vector<float> &percents);
	bool isSelected(int percent);

	std::vector<int> getDifference(std::vector<int> v1, std::vector<int> v2);
	
	cocos2d::CCAnimate *getFrameAnimation(std::string pathFormat, int num, float duration);
	cocos2d::CCMenuItemSprite *getScaleMenuItemSpr(std::string path);

	cocos2d::ccColor3B getRandomColor();
	int getRotation(cocos2d::CCPoint beginPt, cocos2d::CCPoint endPt);
}

#endif