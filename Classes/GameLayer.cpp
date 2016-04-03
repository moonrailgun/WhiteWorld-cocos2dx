#include "GameLayer.h"
#include "GlobalDefine.h"
#include "GlobalData.h"
#include "SimpleAudioEngine.h"
#include "MapManager.h"
#include "DialogueManager.h"
#include "DialogueHelper.h"
#include "Player.h"

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
	mapManager->getMap()->setAnchorPoint(Vec2(0.5, 0.5));
	mapManager->getMap()->setPosition(WINSIZE.width / 2, WINSIZE.height / 2);
	mapManager->setSelectedHighlight();

	_player = Player::create();
	this->addChild(_player, 3);
	_player->setAnimation("sprite", 0.15f);
	_player->setPosition(WINSIZE.width / 2, WINSIZE.height / 2);

	/*
	dialogueManager = DialogueManager::create();
	dialogueManager->showDialogue(this);
	dialogueManager->updateDialogueText("test string");

	DialogueHelper* dialogueHelper = DialogueHelper::parseWithFile("common");
	auto dialogue = dialogueHelper->getFirstDialogue();
	dialogueManager->updateDialogueText(dialogue->at(0).content.c_str());*/

	//添加键盘事件,领onKeyPressed和onKeyReleased方法生效
	this->setKeyboardEnabled(true);
	return true;
}

void GameLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event){
	int playerMaxSpeed = 5;
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_W:
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		this->_playerDirection = EntityDirection::Up;
		this->_playerSpeed = playerMaxSpeed;
		break;
	case EventKeyboard::KeyCode::KEY_A:
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		this->_playerDirection = EntityDirection::Left;
		this->_playerSpeed = playerMaxSpeed;
		break;
	case EventKeyboard::KeyCode::KEY_S:
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		this->_playerDirection = EntityDirection::Down;
		this->_playerSpeed = playerMaxSpeed;
		break;
	case EventKeyboard::KeyCode::KEY_D:
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		this->_playerDirection = EntityDirection::Right;
		this->_playerSpeed = playerMaxSpeed;
		break;
	default:
		this->_playerSpeed = 0;
		break;
	}

	cocos2d::log("%d", _playerDirection);
}

void GameLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event){
	this->_playerSpeed = 0;
}