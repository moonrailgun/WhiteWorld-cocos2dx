#include "ActionTool.h"

Animate* ActionTool::animationWithFrameName(const char* frameName, int iloops, float delay){
	SpriteFrame* frame = NULL;
	Animation* animation = Animation::create();
	int index = 1;
	// 遍历具有frameName特征的图片帧
	do
	{
		String * name = String::createWithFormat("%s%02d.png", frameName, index++);   // 当前是第index帧
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name->getCString());
		if (frame == NULL)
		{
			break;
		}
		animation->addSpriteFrame(frame);
	} while (true);
	// 设置Animation的一些基本属性
	animation->setDelayPerUnit(delay);
	animation->setRestoreOriginalFrame(true);
	animation->setLoops(iloops);
	Animate* animate = Animate::create(animation);
	// 返回一个Animate
	return animate;
}