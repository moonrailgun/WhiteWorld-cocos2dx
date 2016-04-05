#include "GameMap.h"
#include "GlobalDefine.h"

GameMap* GameMap::createGameMap(char* mapName){
	GameMap* gameMap = GameMap::create();

	auto map = GameMap::loadMap(mapName);
	map->setAnchorPoint(Vec2(0.5, 0.5));//设置锚点
	map->setPosition(gameMap->getContentSize() / 2);//设置居中
	log("size %f,%f", gameMap->getContentSize().width, gameMap->getContentSize().height);
	gameMap->_map = map;
	gameMap->addChild(map);

	return gameMap;
}

TMXTiledMap* GameMap::loadMap(char *mapName){
	auto name = String::createWithFormat("map/%s.tmx", mapName);
	log("is loading map which named %s [%s]", mapName, name->getCString());
	auto map = TMXTiledMap::create(name->getCString());

	log("loading completed");

	return map;
}

Player* GameMap::loadPlayer(){
	auto player = Player::create();
	this->_player = player;
	this->addChild(player);

	auto group = _map->getObjectGroup("players");
	auto playerSpawnPoint = group->getObject("playerSpawnPoint");
	auto x = playerSpawnPoint["x"];
	auto y = playerSpawnPoint["y"];
	auto tile = _map->getLayer("bottom")->getTileAt(getTileCoordinateAt(Vec2(x.asFloat(), y.asFloat())));
	tile->setColor(Color3B::RED);

	return player;
}

Vec2 GameMap::getTileCoordinateAt(Vec2 posInPixel){
	Size tileSize = this->_map->getTileSize();
	Size mapSize = this->_map->getMapSize();
	float x = floor(posInPixel.x / tileSize.width);
	float y = floor((mapSize.height * tileSize.height - posInPixel.y) / tileSize.height);

	return Vec2(x, y);
}

Vec2 GameMap::getTilePosBy(Vec2 tileCoordinate){
	Size tileSize = this->_map->getTileSize();
	Size mapSize = this->_map->getMapSize();
	float x = floor(tileCoordinate.x * tileSize.width);
	float y = floor(mapSize.height * tileSize.height - tileCoordinate.y * tileSize.height);
	
	return Vec2(x, y);
}

void GameMap::setMapZoom(float _mapZoom){
	this->_mapZoom = _mapZoom;
	this->setScale(_mapZoom);
}

void GameMap::moveMapTo(Vec2 pos){
	this->_map->setPosition(pos);
}

void GameMap::setMapToCenter(Vec2 anchor){
	this->_map->setAnchorPoint(Vec2(0.5, 0.5));//设置锚点
	this->_map->setPosition(WINSIZE / 2);//设置居中
}