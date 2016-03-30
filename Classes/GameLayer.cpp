#include "GameLayer.h"
#include "GlobalDefine.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* GameLayer::createScene(){
	Scene* scene = Scene::create();
	GameLayer* layer = GameLayer::create();
	scene->addChild(layer);

	return scene;
}

bool GameLayer::init(){
	if (!Layer::init()){
		return false;
	}

	if (getBoolFromXML(MUSIC_KEY)){
		float music = getFloatFromXML(MUSICVOL)*100.0f;
		audioEngine->setBackgroundMusicVolume(getFloatFromXML(MUSICVOL));
		if (audioEngine->isBackgroundMusicPlaying())
		{
			audioEngine->pauseBackgroundMusic();
			audioEngine->playBackgroundMusic("sound/Airship.mp3", true);
		}
		else{
			audioEngine->playBackgroundMusic("sound/Airship.mp3", true);
		}
	}
	else{
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	}

	auto map = TMXTiledMap::create("map/home.tmx");
	map->setScale(2);
	map->setAnchorPoint(Vec2(0.5, 0.5));
	map->setPosition(WINSIZE.width / 2, WINSIZE.height / 2);
	this->addChild(map);

	auto mapSize = map->getMapSize();//地图尺寸

	auto hero = DrawNode::create();
	hero->drawSolidCircle(Vec2(WINSIZE.width / 2, WINSIZE.height / 2), 10, 360, 18, Color4F(Color4B(255,255,255,255)));
	this->addChild(hero);

	DrawNode* selectBlock = DrawNode::create();
	this->addChild(selectBlock);

	auto listener = EventListenerMouse::create();
	listener->onMouseMove = [&, map, mapSize, selectBlock](EventMouse* mouse){
		float x = mouse->getCursorX();
		float y = mouse->getCursorY();

		TMXLayer* mapLayer = map->getLayer("bottom");

		Vec2 coor = Vec2(0, 0);

		float left = WINSIZE.width / 2 - mapSize.width / 2;
		float bottom = WINSIZE.height / 2 - mapSize.height / 2;

		coor.x = (int)((x - left) / (32*2));
		coor.y = (int)((y - bottom) / (32*2));
		if (coor.x < 0 || coor.y<0){return;}
		auto tile = mapLayer->getTileAt(coor);
		auto tilePos = convertToWorldSpaceAR(tile->getPosition());

		selectBlock->clear();
		selectBlock->drawRect(Vec2(tilePos.x, tilePos.y), Vec2(tilePos.x + 32 * 2, tilePos.y + 32 * 2), Color4F(1, 0, 0, 1));

		log("(%f,%f)", x, y);
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}