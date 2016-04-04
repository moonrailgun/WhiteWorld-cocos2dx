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

	this->scheduleUpdate();
	return true;
}

void GameLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event){
	if (!!_player->isHurt){
		return;
	}

	float playerMaxSpeed = _player->maxSpeed;
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_W:
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		_player->direction = EntityDirection::Up;
		_player->currentSpeed = playerMaxSpeed;
		break;
	case EventKeyboard::KeyCode::KEY_A:
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		_player->direction = EntityDirection::Left;
		_player->currentSpeed = playerMaxSpeed;
		break;
	case EventKeyboard::KeyCode::KEY_S:
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		_player->direction = EntityDirection::Down;
		_player->currentSpeed = playerMaxSpeed;
		break;
	case EventKeyboard::KeyCode::KEY_D:
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		_player->direction = EntityDirection::Right;
		_player->currentSpeed = playerMaxSpeed;
		break;
	default:
		_player->currentSpeed = 0;
		break;
	}
}

void GameLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event){
	if (_player->currentSpeed != 0){
		_player->currentSpeed = 0;
	}
}

void GameLayer::update(float delta){
	//移动玩家位置
	_player->isMove = false;
	if (!_player->isHurt && _player->currentSpeed > 0){
		_player->isMove = true;
		auto direcion = _player->direction;
		float currentSpeed = _player->currentSpeed;

		Vec2 delta = Vec2::ZERO;
		switch (direcion){
		case EntityDirection::Up:
			delta = Vec2(0, currentSpeed);
			break;
		case EntityDirection::Down:
			delta = Vec2(0, -currentSpeed);
			break;
		case EntityDirection::Left:
			delta = Vec2(-currentSpeed, 0);
			break;
		case EntityDirection::Right:
			delta = Vec2(currentSpeed, 0);
			break;
		default:
			break;
		}
		_player->setPosition(_player->getPosition() + delta);
		/*
		//todo 移动地图
		if (_player->judgePosition()){
		//当玩家在画面中间时，移动地图
		mapManager->moveMap(_player);
		}
		else
		{
		//当玩家在画面边缘时，移动玩家
		Vec2 delta = Vec2::ZERO;
		switch (direcion){
		case EntityDirection::Up:
		delta = Vec2(0, currentSpeed);
		break;
		case EntityDirection::Down:
		delta = Vec2(0, -currentSpeed);
		break;
		case EntityDirection::Left:
		delta = Vec2(-currentSpeed, 0);
		break;
		case EntityDirection::Right:
		delta = Vec2(currentSpeed, 0);
		break;
		default:
		break;
		}

		_player->setPosition(_player->getPosition() + delta);
		}*/
	}
}