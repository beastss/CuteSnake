#ifndef __COMMON_MACRO_H__
#define __COMMON_MACRO_H__

#define WIDTH 1600
#define HEIGHT 800

/*
#define WHITE ccc3(255, 255, 255)
#define BLACK ccc3(0, 0, 0)
#define LIGHT_PINK ccc3(255, 182, 193)
#define STEEL_BLUE ccc3(70, 130, 180)
#define CRIMSON ccc3(220, 20, 60)
#define VIOLET ccc3(238, 130, 238)
#define SLATEBLUE ccc3(106, 90, 205)
#define CYAN ccc3(0, 255, 255)
#define AUQAMARIN ccc3(127, 255, 170)
#define LIME ccc3(0, 255, 0)
#define YELLOW ccc3(255, 255, 0)
#define OLIVE ccc3(128, 128, 0)
#define CORNISLK ccc3(255, 248, 220)
#define ORANGE ccc3(255, 165, 0)
#define CORAL ccc3(255, 127, 80)
#define SKY_BLUE ccc3(135, 206, 235, 255)
#define GOLD ccc3(255, 215, 0, 255)
#define MAROON ccc3(128, 0, 0, 255)
*/

#define NOTIFY_VIEWS(_FUNC_ ,...)						\
for (size_t index = 0; index < m_views.size(); ++index) \
{														\
	m_views[index]->_FUNC_(__VA_ARGS__);				\
}

#define NORMAL_SPEED 100
#define GAME_LAYER_WIDTH 700
#define GAME_LAYER_HEIGHT 700

enum TouchPriority
{
	kTouchPriorityPanel = -10,
	kTouchPriorityDialog = -20,
};
#endif