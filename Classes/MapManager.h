#ifndef __MapManager__H__
#define __MapManager__H__

#include "cocos2d.h"

USING_NS_CC;

class MapManager: public Ref{
public :
	MapManager();
	bool loadMap(char *mapName);
	bool replaceMap(char *mapName);
};

#endif