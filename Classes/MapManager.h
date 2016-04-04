#ifndef __MapManager__H__
#define __MapManager__H__

#include "cocos2d.h"
#include "Player.h"

USING_NS_CC;

class GameLayer;

class MapManager: public Ref{
public :
	bool init();
	CREATE_FUNC(MapManager);

	static MapManager* createManager(GameLayer* gameLayer);

	bool loadMap(char *mapName,int mapZoom = 2);//加载地图
	void setSelectedHighlight();//设置选中高亮

	TMXTiledMap* getMap();
	char* getMapName();
	Size getMapSize();
	int getMapZoom();
	GameLayer* getGameLayer();
	void moveMap(Player* player);

	Sprite* selectedBlock;
	DrawNode* selectedBlockHighLight;
	void onMouseMove(EventMouse* event);
private:
	//地图配置
	GameLayer* _gameLayer;
	TMXTiledMap* _currentMap;
	char* _currentMapName;
	Size _currentMapSize;
	int _mapZoom;
	Size _tileSize;
};

#endif