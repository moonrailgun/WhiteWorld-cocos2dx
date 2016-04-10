#include "DebugTool.h"

void DebugTool::log(Vec2 vec2){
	cocos2d::log("[Debug]Vec2: (%f,%f)", vec2.x, vec2.y);
}
void DebugTool::log(Size size){
	cocos2d::log("[Debug]Size: (%f,%f)", size.width, size.height);
}
void DebugTool::log(Node* node){
	cocos2d::log("[Debug]Node: pos->(%f,%f), size->(%f,%f), tag->%d", 
		node->getPositionX(),
		node->getPositionY(),
		node->getContentSize().width, 
		node->getContentSize().height, 
		node->getTag());
}