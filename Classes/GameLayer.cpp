#include "GameLayer.h"
#include "GlobalDefine.h"
#include "GlobalData.h"
#include "SimpleAudioEngine.h"
#include "MapManager.h"

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

	this->setName("game");

	playerName = "12456";

	mapManager = MapManager::createManager(this);
	mapManager->loadMap("home");
	mapManager->setSelectedHighlight();

	return true;
}