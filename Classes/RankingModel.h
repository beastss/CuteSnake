#ifndef __RANKING_MODEL_H__
#define __RANKING_MODEL_H__
#include "cocos2d.h"
#include <unordered_map>
class RankingModel
{
public:
	static RankingModel *theModel();
	void updateScore(std::string name, int score);
	std::string applyName();//…Í«Î√˚◊÷
	void removeRank(std::string name);
	std::vector<std::pair<std::string, int>>getCurRank(int topNum);

	void init();
private:
	RankingModel(){}
private:
	std::unordered_map<std::string, int>m_rank;
	std::vector<std::string>m_notUsedNames;
};
#endif
