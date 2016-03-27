#ifndef __Player__H__
#define __Player__H__

#include "cocos2d.h"
USING_NS_CC;

class Player : public Node
{
public:
	// 根据图片名创建英雄
	void InitPlayerSprite(char *_playerName, int _level);
	// 返回当前英雄
	Node* GetSprite();

	// 设置动画，run_directon为精灵脸朝向，false朝右,frameName为图片帧名字
	void SetAnimation(const char *frameName, float delay, bool run_directon);
	// 停止动画
	void StopAnimation();
	// 跳起动画
	void JumpUpAnimation(const char *name_each, float delay, bool run_directon);
	// 跳落动画
	void JumpDownAnimation(const char *name_each, float delay, bool run_directon);
	// 跳落动画结束
	void JumpEnd();
	// 攻击动画
	void AttackAnimation(const char *name_each, float delay, bool run_directon);
	// 攻击动画结束
	void AttackEnd();
	// 死亡动画
	void DeadAnimation(const char *name_each, float delay, bool run_directon);
	// 死亡动画结束
	void DeadEnd();
	// 受伤动画
	void HurtByMonsterAnimation(const char *name_each, float delay, bool run_directon);
	// 受伤动画结束
	void HurtByMonsterEnd();
	// 判断英雄是否运动到了窗口的中间位置,visibleSize为当前窗口的大小  
	bool JudgePosition(Size visibleSize);

	bool IsDead;

	// HP & MP 值
	float m_iCurrentHp;
	float m_iTotleHp;
	float m_iCurrentMp;
	float m_iTotleMp;

	float percentage;
	float m_iSpeed;

	bool m_bIsAction;          // 查看当前是否已经在打怪了
	bool m_bIsJumping;         // 查看是否在跳
	bool IsRunning;  // 判断是否在跑动画
	bool IsAttack;  // 判断是否在攻击动画

	bool IsHurt; // 判断是否受伤

	bool HeroDirecton; // 英雄运动的方向
	bool m_bCanCrazy; // 判断是否处于狂暴状态

	float pos_x;//位置X坐标
	float pos_y;//位置Y坐标

	CREATE_FUNC(Player);
private:
	Node* playerSprite; // 精灵
	char* playerName; // 用来保存初始状态的精灵图片名称
};
#endif