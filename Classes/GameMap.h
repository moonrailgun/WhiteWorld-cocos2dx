#ifndef __GameMap__H__
#define __GameMap__H__

#include "cocos2d.h"
#include "Player.h"

USING_NS_CC;

class GameMap : public Layer{
public:
	static GameMap* createGameMap(char* mapName);
	CREATE_FUNC(GameMap);

	static TMXTiledMap* loadMap(char* mapName);
	Player* loadPlayer();
	void setMapZoom(float _mapZoom);

	void moveMapTo(Vec2 pos);
	void setMapToCenter(Vec2 anchor = Vec2(0.5, 0.5));
	void setPlayerToCenter();

	void tryMovePlayer();
private:
	TMXTiledMap* _map;
	Player* _player;
	float _mapZoom = 1;
	
	Vec2 getTileCoordinateAt(Vec2 posInPixel);
	Vec2 getTilePosBy(Vec2 tileCoordinate);
};

#endif