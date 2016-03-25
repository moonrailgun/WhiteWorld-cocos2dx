#include "StartLayer.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "GlobalDefine.h"
#include "CreateProfileLayer.h"
#include "SetLayer.h"

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

	bgPic = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("StartBackground.png"));
	bgPic->setPosition(WINSIZE.width / 2, WINSIZE.height / 2);
	this->addChild(bgPic);

	addonBoard = LayerColor::create(Color4B(0, 0, 0, 126), 710, 570);
	addonBoard->setPosition(50, 70);
	addonBoard->setVisible(false);
	this->addChild(addonBoard);

	auto newGameItem = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("NewGameNormal.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("NewGameSelected.png")),
		CC_CALLBACK_1(StartLayer::touchNewGame, this));//新的开始

	auto continueGameItem = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("ContinueGameNormal.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("ContinueGameSelected.png")),
		CC_CALLBACK_1(StartLayer::touchContinueGame, this));//旧的回忆

	auto setItem = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("SetNormal.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("SetSelected.png")),
		CC_CALLBACK_1(StartLayer::touchSet, this));//设置

	auto helpItem = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("HelpNormal.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("HelpSelected.png")),
		CC_CALLBACK_1(StartLayer::touchHelp, this));//帮助

	newGameItem->setPosition(WINSIZE.width - 195, WINSIZE.height - 113);
	continueGameItem->setPosition(WINSIZE.width - 195, WINSIZE.height - 113 - 110 * 1);
	setItem->setPosition(WINSIZE.width - 195, WINSIZE.height - 113 - 110 * 2);
	helpItem->setPosition(WINSIZE.width - 195, WINSIZE.height - 113 - 110 * 3);

	//todo 添加事件监听鼠标悬停
	auto menu = Menu::create(newGameItem, continueGameItem, setItem, helpItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 2);

	return true;
}

void StartLayer::touchNewGame(Ref* pSender)
{
	log("NewGame");
	PLAYEFFECT;
	Director::getInstance()->replaceScene(CreateProfileLayer::createScene());
	//Director::getInstance()->replaceScene(SetLayer::createScene());
}

void StartLayer::touchContinueGame(Ref* pSender)
{
	log("ContinueGame");
	PLAYEFFECT;
	//Director::getInstance()->replaceScene(SetLayer::createScene());
}

void StartLayer::touchSet(Ref* pSender)
{
	log("Set");
	PLAYEFFECT;

	showAddonBoard();
	//Director::getInstance()->replaceScene(SetLayer::createScene());
}

void StartLayer::touchHelp(Ref* pSender)
{
	log("Help");
	PLAYEFFECT;
	//Director::getInstance()->replaceScene(SetLayer::createScene());
}

void StartLayer::showAddonBoard(){
	if (addonBoard != NULL && !addonBoard->isVisible()){
		addonBoard->setVisible(true);
	}
}