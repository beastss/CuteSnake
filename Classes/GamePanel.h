#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"
#include "BasePanel.h"
#include "MsgNotifier.h"
class UiLayer;
class Snake;
class Food;
class FoodMgr;

class GamePanel 
	: public BasePanel
	, public IMsgWatcherView
{
public:
	CREATE_FUNC(GamePanel);
	void setFocus(cocos2d::CCPoint pos);
	std::vector<Snake *> getSnakes(){ return m_snakes; }
	void removeSnake(Snake *snake);
	void addFood(cocos2d::ccColor3B color, cocos2d::CCPoint pos);
	void addFood(std::string path, cocos2d::CCPoint pos);
	void addSnake(Snake *snake);
	cocos2d::CCNode *getSnakeBatch(){ return m_snakeBatchNode; }
	~GamePanel();
private:
	GamePanel();
    virtual bool init();  
	virtual void onEnter();
	virtual void onExit();
	void initGameBk();
	void initSnakes();
	void update(float dt);
	virtual void onBackKeyTouched();
private:
	virtual void onUpdateGameState(bool pause);
private:
	UiLayer *m_uiLayer;
	cocos2d::CCNode *m_snakeField;
	cocos2d::CCSpriteBatchNode *m_snakeBatchNode;
	FoodMgr *m_foodMgr;
	std::vector<Snake *> m_snakes;
	bool m_runningUpdate;
};

#endif 
