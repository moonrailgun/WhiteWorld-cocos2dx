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

	void tryMovePlayer(Vec2 toPos);
private:
	TMXTiledMap* _map;
	Player* _player;
	float _mapZoom = 1;
	std::vector<Vec2> blockTileCoorList;
	
	//通过在该层中的像素坐标获取图块坐标
	Vec2 getTileCoordinateAt(Vec2 posInPixel);
	//通过图块坐标获取像素坐标
	Vec2 getTilePosBy(Vec2 tileCoordinate);
	//获取地图左下角坐标
	Vec2 getMapLeftBottomPos();
	//注册不可达到的地块坐标
	void registerBlockTile();
};

#endif