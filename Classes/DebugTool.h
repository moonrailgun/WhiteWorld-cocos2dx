#ifndef __DebugTool__H__
#define __DebugTool__H__

#include "cocos2d.h"
USING_NS_CC;

class DebugTool{
public:
	static void log(Vec2 vec2);
	static void log(Size size);
	static void log(Node node);
};

#endif