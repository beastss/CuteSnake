#include "DataLoader.h"
#include "SnakeColor.h"
#include "SoundMgr.h"
using namespace std;

void DataLoader::loadData()
{
	SnakeColor::init();
	SoundMgr::theMgr()->init();
}
