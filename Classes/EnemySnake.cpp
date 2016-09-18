#include "EnemySnake.h"
USING_NS_CC;
using namespace std;

EnemySnake::EnemySnake(GamePanel *gamePanel)
: Snake(gamePanel)
{

}

EnemySnake *EnemySnake::create(GamePanel *gamePanel)
{
	EnemySnake *snake = new EnemySnake(gamePanel);
	snake->init();
	snake->autorelease();
	return snake;
}

bool EnemySnake::init()
{
	return true;
}