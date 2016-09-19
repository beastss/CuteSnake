#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"

class ScaleDialog;
class BasePanel;

enum PanelId
{
	kPanelIdDefault,
	kPanelIdMenuPanel,
	kPanelIdGamePanel,
	kPanelIdHelpPanel,
};
class MainScene : public cocos2d::CCScene
{
public:
	static MainScene *theScene();
	~MainScene();
	void showPanel(int panelId);
	void showDialog(ScaleDialog *dialog);
private:
	MainScene();
    virtual bool init();  
private:
	cocos2d::CCNode *m_panelLayer;
	cocos2d::CCNode *m_dialogLayer;
	static MainScene *m_scene;
};

#endif 
