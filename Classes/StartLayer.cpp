#include "StartLayer.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "GlobalDefine.h"

using namespace cocos2d;
using namespace CocosDenshion;

Scene* StartLayer::createScene()
{
	Scene* startScene = Scene::create();
	StartLayer* layer = StartLayer::create();
	startScene->addChild(layer);

	return startScene;
}

bool StartLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	// 根据音乐的开关来播放背景音乐
	if (getBoolFromXML(MUSIC_KEY))
	{
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
	else
	{
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	}

	return true;
}