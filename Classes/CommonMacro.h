#ifndef __COMMON_MACRO_H__
#define __COMMON_MACRO_H__

#define NOTIFY_VIEWS(_FUNC_ ,...)						\
for (size_t index = 0; index < m_views.size(); ++index) \
{														\
	m_views[index]->_FUNC_(__VA_ARGS__);				\
}

#define NORMAL_SPEED 200
#define GAME_LAYER_WIDTH 4000
#define GAME_LAYER_HEIGHT 4000

enum TouchPriority
{
	kTouchPriorityPanel = -10,
	kTouchPriorityDialog = -20,
};
#endif