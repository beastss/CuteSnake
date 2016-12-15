#ifndef _MSGNOTIFIER_H_
#define _MSGNOTIFIER_H_
#include "CommonMacro.h"
#include "cocos2d.h"

struct IMsgWatcherView
{
	virtual void onUpdateGameState(bool pause){};
	virtual void onPropsNumChanged(){};
};

class MsgNotifier
{
public:
	static MsgNotifier *theNotifier();
	void addView(IMsgWatcherView *view);
	void removeView(IMsgWatcherView *view);
public:
	void onUpdateGameState(bool pause){ NOTIFY_VIEWS(onUpdateGameState, pause); }
	void onPropsNumChanged(){ NOTIFY_VIEWS(onPropsNumChanged); }
private:
	MsgNotifier(){}
private:
	std::vector<IMsgWatcherView *>m_views;

};
#endif