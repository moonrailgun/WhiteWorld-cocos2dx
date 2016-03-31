#include "MapManager.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "GameLayer.h"

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

	return true;
}

MapManager* MapManager::createManager(GameLayer* gameLayer){
	MapManager* mapManager = MapManager::create();
	mapManager->_gameLayer = gameLayer;

	return mapManager;
}

bool MapManager::loadMap(char *mapName,int mapZoom){
	auto name = String::createWithFormat("map/%s.tmx", mapName);
	log("is loading map which named %s [%s]", mapName, name->getCString());
	_currentMapName = mapName;
	_mapZoom = mapZoom;
	_currentMap = TMXTiledMap::create(name->getCString());

	if (_currentMap == NULL){
		return false;
	}

	_currentMapSize =Size(_currentMap->getMapSize());
	_tileSize =Size(_currentMap->getTileSize());
	
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

void MapManager::onMouseMove(EventMouse *mouse){
	Vec2 mousePos = Vec2(mouse->getCursorX(), mouse->getCursorY());
	//TMXLayer* bottomLayer = _currentMap->getLayer("bottom");
	
	this->selectedBlockHighLight->clear();
	this->selectedBlockHighLight->drawRect(mousePos, mousePos + Vec2(32, 32), Color4F(1, 0, 0, 1));

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
