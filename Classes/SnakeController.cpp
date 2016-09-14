#include "SnakeController.h"
#include "CommonMacro.h"
USING_NS_CC;
using namespace std;

SnakeController *SnakeController::controller()
{
	static SnakeController controller;
	return &controller;
}

void SnakeController::changeAngle(int angle)
{
	NOTIFY_VIEWS(onAngleChanged, angle);
}

void SnakeController::speedUp()
{
	NOTIFY_VIEWS(onSpeedUp);
}

void SnakeController::addView(IControlSnake *view)
{
	auto iter = find(m_views.begin(), m_views.end(), view);
	if (iter == m_views.end())
	{
		m_views.push_back(view);
	}
}

void SnakeController::removeView(IControlSnake *view)
{
	auto iter = find(m_views.begin(), m_views.end(), view);
	if (iter != m_views.end())
	{
		m_views.erase(iter);
	}
}