#include "Player.h"
#include "ActionTool.h"

USING_NS_CC;

bool Player::init(){
	_playerSprite = NULL;
	_playerName = NULL;

	m_iCurrentMp = 0.0f;
	m_iTotleMp = 100.0f;
	m_iSpeed = 5;
	m_iCurrentHp = m_iTotleHp = 100.0f;
	percentage = 100.0f;

	this->_playerSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("sprite01.png"));
	this->addChild(_playerSprite);

	return true;
}

Sprite* Player::getSprite(){
	return this->_playerSprite;
}

void Player::setName(char* playerName){
	this->_playerName = playerName;
}

char* Player::getName(){
	return this->_playerName;
}

void Player::setAnimation(const char *frameName, float delay){
	Animate* action = ActionTool::animationWithFrameName(frameName, -1, delay);
	_playerSprite->runAction(action);
}

void Player::stopAnimation(){
	_playerSprite->stopAllActions();
}