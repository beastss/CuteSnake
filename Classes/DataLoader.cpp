#include "DataLoader.h"
#include "SnakeColor.h"
#include "SoundMgr.h"
#include "PropsMgr.h"
using namespace std;

void DataLoader::loadData()
{
	SnakeColor::init();
	SoundMgr::theMgr()->init();
	PropsMgr::theMgr()->init();
}
