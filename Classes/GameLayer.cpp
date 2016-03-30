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

	auto hero = DrawNode::create();
	hero->drawSolidCircle(Vec2(WINSIZE.width / 2, WINSIZE.height / 2), 10, 360, 18, Color4F(Color4B(255,255,255,255)));
	this->addChild(hero);

	return true;
}