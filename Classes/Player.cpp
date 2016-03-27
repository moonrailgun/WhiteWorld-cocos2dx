#include "Player.h"

USING_NS_CC;

void Player::InitPlayerSprite(char *_playerName, int _level){
	playerSprite = NULL;
	m_bCanCrazy = false;
	m_bIsAction = false;
	m_bIsJumping = false;
	HeroDirecton = false;    	// 向右运动
	playerName = NULL;
	IsRunning = false;
	IsAttack = false;
	IsHurt = false;
	IsDead = false;
	pos_x = 0;
	pos_y = 0;

	m_iCurrentMp = 0.0f;
	m_iTotleMp = 100.0f;
	m_iSpeed = 5;
	playerName = _playerName;
	m_iCurrentHp = m_iTotleHp = 300.0f * _level;
	percentage = 100.0f;


	auto sprite = DrawNode::create();
	sprite->drawSolidCircle(Vec2(pos_x, pos_y), 10, 2 * CC_DEGREES_TO_RADIANS(360), 16, Color4F(1, 1, 1, 1));
	this->playerSprite = sprite;
	this->addChild(playerSprite);
}

Node* Player::GetSprite(){
	return this->playerSprite;
}