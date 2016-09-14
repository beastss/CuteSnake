#ifndef __ENEMY_SNAKE_H__
#define __ENEMY_SNAKE_H__ 
#include "Snake.h"
class EnemySnake : public Snake
{
public:
	CREATE_FUNC(EnemySnake);
private:
	virtual bool init();

};
#endif