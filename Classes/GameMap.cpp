#include "GameMap.h"
#include "GlobalDefine.h"

GameMap* GameMap::createGameMap(char* mapName){
	GameMap* gameMap = GameMap::create();

	auto map = GameMap::loadMap(mapName);
	//map->setAnchorPoint(Vec2(0.5, 0.5));//设置锚点
	map->setPosition(gameMap->getContentSize() / 2 - map->getContentSize() / 2);//设置居中
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
	this->_player->setAnimation("sprite", 0.15f);
	this->addChild(player);

	auto group = _map->getObjectGroup("players");
	auto playerSpawnPoint = group->getObject("playerSpawnPoint");
	auto x = playerSpawnPoint["x"].asFloat();
	auto y = playerSpawnPoint["y"].asFloat();
	auto tile = _map->getLayer("bottom")->getTileAt(getTileCoordinateAt(Vec2(x, y)));
	tile->setColor(Color3B::RED);

	Vec2 mapAnchor = this->_map->getAnchorPoint();
	Vec2 pos = tile->getPosition() + _map->getPosition() - getMapLeftBottomPos() + tile->getContentSize() / 2;
	this->_player->setPosition(pos);

	return player;
}

Vec2 GameMap::getTileCoordinateAt(Vec2 posInPixel){
	Size tileSize = this->_map->getTileSize();
	Size mapSize = this->_map->getMapSize();
	float x = floor(posInPixel.x / tileSize.width);
	float y = floor((mapSize.height * tileSize.height - posInPixel.y) / tileSize.height);

	return Vec2(x, y);
}

Vec2 GameMap::getTilePosBy(Vec2 tileCoordinate) {
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

void GameMap::setPlayerToCenter(){
	if (_player == NULL || _map == NULL){ return; }

	auto playerPos = _player->getPosition();
	auto mapPos = _map->getPosition();
	_player->setPosition(WINSIZE / 2);
	_map->setPosition(mapPos + WINSIZE / 2 - playerPos);
}

void GameMap::tryMovePlayer(Vec2 toPos) {
	Vec2 coor = getTileCoordinateAt(toPos - getMapLeftBottomPos());
	Size mapSize = this->_map->getMapSize();

	if (coor.x >= mapSize.width || coor.x < 0 || coor.y >= mapSize.height || coor.y < 0){
		return;//要到达目标在地图外
	}

	if (_map->getLayer("block")->getTileAt(coor) != NULL){
		return;//要到达的目标有障碍物
	}

	_player->setPosition(toPos);
}

Vec2 GameMap::getMapLeftBottomPos(){
	return _map->getPosition() - Vec2(_map->getAnchorPoint().x * _map->getContentSize().width, _map->getAnchorPoint().y * _map->getContentSize().height);
}

void GameMap::registerBlockTile(){

}