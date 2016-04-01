﻿#include "MapManager.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "GameLayer.h"
#include "GlobalData.h"

USING_NS_CC;
bool MapManager::init(){
	_gameLayer = NULL;
	_currentMap = NULL;
	_currentMapName = "";
	_currentMapSize = Size::ZERO;
	_mapZoom = NULL;
	_tileSize = Size::ZERO;

	selectedBlock = NULL;
	selectedBlockHighLight = NULL;

	this->retain();//保留对象所有权，使对象不会被释放

	return true;
}

MapManager* MapManager::createManager(GameLayer* gameLayer){
	MapManager* mapManager = MapManager::create();
	mapManager->_gameLayer = gameLayer;

	return mapManager;
}

//加载地图
bool MapManager::loadMap(char *mapName, int mapZoom){
	auto name = String::createWithFormat("map/%s.tmx", mapName);
	log("is loading map which named %s [%s]", mapName, name->getCString());
	_currentMapName = mapName;
	_mapZoom = mapZoom;
	_currentMap = TMXTiledMap::create(name->getCString());

	if (_currentMap == NULL){
		return false;
	}

	_currentMapSize = Size(_currentMap->getMapSize());
	_tileSize = Size(_currentMap->getTileSize());

	_currentMap->setScale(_mapZoom);

	if (_gameLayer == NULL){
		return false;
	}
	_gameLayer->addChild(_currentMap);

	log("loading completed");

	return true;
}

void MapManager::setSelectedHighlight(){
	if (_gameLayer == NULL || _currentMap == NULL){
		return;
	}

	selectedBlockHighLight = DrawNode::create();
	_gameLayer->addChild(selectedBlockHighLight);

	//鼠标事件配置
	auto listener = EventListenerMouse::create();
	listener->onMouseMove = CC_CALLBACK_1(MapManager::onMouseMove, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, _gameLayer);
}

void MapManager::onMouseMove(EventMouse *mouse) {
	Vec2 mousePos = Vec2(mouse->getCursorX(), mouse->getCursorY());
	TMXLayer* bottomLayer = _currentMap->getLayer("bottom");

	auto mapTileSize = bottomLayer->getMapTileSize() * getMapZoom();//地块实际大小
	auto map = getMap();
	auto mapSize = Size(map->getMapSize().width * mapTileSize.width, map->getMapSize().height * mapTileSize.height);//地图实际大小
	auto mapAnchor = map->getAnchorPoint();

	Vec2 mapStartPoint = Vec2(map->getPositionX() - mapSize.width * mapAnchor.x, map->getPositionY() - mapSize.height * mapAnchor.y);//地图左下角坐标

	mousePos.clamp(mapStartPoint + Vec2(0.1, 0.1), mapStartPoint + mapSize - Vec2(0.1, 0.1));//限制在地图内,距离地图边缘0.1像素

	Vec2 tileCoordinate = Vec2(mousePos.x / mapTileSize.width, mousePos.y / mapTileSize.height);
	Sprite* tileSelected = bottomLayer->getTileAt(Vec2((int)tileCoordinate.x, map->getMapSize().height - 1 - (int)tileCoordinate.y));//获取选中地块的精灵
	auto tileSelectedPos = tileSelected->getPosition();//地块相对坐标
	auto tileSelectedRealPos = tileSelectedPos * getMapZoom() + Vec2(mapSize.width * mapAnchor.x, mapSize.height*mapAnchor.y) + mapStartPoint; //地块真实像素坐标

	selectedBlockHighLight->clear();
	//selectedBlockHighLight->drawRect(mousePos, mousePos + Vec2(32, 32), Color4F(1, 0, 0, 1));
	selectedBlockHighLight->drawRect(tileSelectedRealPos, tileSelectedRealPos + mapTileSize, Color4F(1, 0, 0, 1));//地块高亮绘制
}

GameLayer* MapManager::getGameLayer(){
	return this->_gameLayer;
}
TMXTiledMap* MapManager::getMap(){
	return this->_currentMap;
}
char* MapManager::getMapName(){
	return this->_currentMapName;
}
Size MapManager::getMapSize(){
	return this->_currentMapSize;
}
int MapManager::getMapZoom(){
	return this->_mapZoom;
}