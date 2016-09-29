#include "SnakeSkinRes.h"
USING_NS_CC;
using namespace std;

SnakeSkinRes *SnakeSkinRes::SnakeResData()
{
	static SnakeSkinRes res;
	return &res;
}

void SnakeSkinRes::init()
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("sprite_frames/snake_skin.plist");

	m_headRes.push_back("skin_16_head.png");
	m_bodyRes.push_back(make_pair("skin_17_body%d.png", 3));
	m_tailRes.push_back("skin_5_tail.png");
}

std::string SnakeSkinRes::getHeadRes(int skin)
{
	assert(isValidSkinId(skin));

	return m_headRes[skin];
}

std::string SnakeSkinRes::getBodyRes(int skin, int pos)
{
	assert(isValidSkinId(skin));

	int index = (pos - 1) % m_bodyRes[skin].second + 1;
	char str[100] = { 0 };
	sprintf(str, m_bodyRes[skin].first.c_str(), index);
	return str;
}

std::string SnakeSkinRes::getTailRes(int skin)
{
	assert(isValidSkinId(skin));

	return m_tailRes[skin];
}

bool SnakeSkinRes::isValidSkinId(int skin)
{
	return skin >= kFirstSkin && skin <= kLastSkin;
}