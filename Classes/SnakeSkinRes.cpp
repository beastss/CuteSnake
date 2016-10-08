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

	m_headRes.push_back("skin_1_head.png");
	m_bodyRes.push_back(make_pair("skin_1_body%d.png", 1));
	m_tailRes.push_back("skin_1_tail.png");

	m_headRes.push_back("skin_2_head.png");
	m_bodyRes.push_back(make_pair("skin_2_body%d.png", 2));
	m_tailRes.push_back("skin_tail.png");

	m_headRes.push_back("skin_3_head.png");
	m_bodyRes.push_back(make_pair("skin_3_body%d.png", 1));
	m_tailRes.push_back("skin_3_tail.png");

	m_headRes.push_back("skin_4_head.png");
	m_bodyRes.push_back(make_pair("skin_4_body%d.png", 2));
	m_tailRes.push_back("skin_tail.png");

	m_headRes.push_back("skin_5_head.png");
	m_bodyRes.push_back(make_pair("skin_5_body%d.png", 1));
	m_tailRes.push_back("skin_5_tail.png");

	m_headRes.push_back("skin_6_head.png");
	m_bodyRes.push_back(make_pair("skin_6_body%d.png", 1));
	m_tailRes.push_back("skin_tail.png");

	m_headRes.push_back("skin_7_head.png");
	m_bodyRes.push_back(make_pair("skin_7_body%d.png", 1));
	m_tailRes.push_back("skin_tail.png");

	m_headRes.push_back("skin_8_head.png");
	m_bodyRes.push_back(make_pair("skin_8_body%d.png", 1));
	m_tailRes.push_back("skin_tail.png");
	
	m_headRes.push_back("skin_9_head.png");
	m_bodyRes.push_back(make_pair("skin_9_body%d.png", 1));
	m_tailRes.push_back("skin_tail.png");

	m_headRes.push_back("skin_10_head.png");
	m_bodyRes.push_back(make_pair("skin_10_body%d.png", 1));
	m_tailRes.push_back("skin_tail.png");

	m_headRes.push_back("skin_11_head.png");
	m_bodyRes.push_back(make_pair("skin_11_body%d.png", 1));
	m_tailRes.push_back("skin_5_tail.png");

	m_headRes.push_back("skin_12_head.png");
	m_bodyRes.push_back(make_pair("skin_12_body%d.png", 1));
	m_tailRes.push_back("skin_tail.png");

	m_headRes.push_back("skin_13_head.png");
	m_bodyRes.push_back(make_pair("skin_13_body%d.png", 2));
	m_tailRes.push_back("skin_tail.png");

	m_headRes.push_back("skin_14_head.png");
	m_bodyRes.push_back(make_pair("skin_14_body%d.png", 2));
	m_tailRes.push_back("skin_tail.png");

	m_headRes.push_back("skin_15_head.png");
	m_bodyRes.push_back(make_pair("skin_15_body%d.png", 2));
	m_tailRes.push_back("skin_tail.png");

	m_headRes.push_back("skin_16_head.png");
	m_bodyRes.push_back(make_pair("skin_16_body%d.png", 1));
	m_tailRes.push_back("skin_tail.png");

	m_headRes.push_back("skin_17_head.png");
	m_bodyRes.push_back(make_pair("skin_17_body%d.png", 2));
	m_tailRes.push_back("skin_tail.png");

	m_headRes.push_back("skin_18_head.png");
	m_bodyRes.push_back(make_pair("skin_18_body%d.png", 2));
	m_tailRes.push_back("skin_tail.png");
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