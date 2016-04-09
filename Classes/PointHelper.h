#ifndef __PointHelper__H__
#define __PointHelper__H__

#include "cocos2d.h"

USING_NS_CC;

class PointHelper{
public:
	static Vec2 getNodeLeftTopPoint(Node* node);
	static Vec2 getNodeLeftBottomPoint(Node* node);
	static Vec2 getNodeRightTopPoint(Node* node);
	static Vec2 getNodeRightBottomPoint(Node* node);
	static Vec2 getNodeCenterPoint(Node* node);
	static Vec2 getNodeMiddleTopPoint(Node* node);
	static Vec2 getNodeMiddleBottomPoint(Node* node);
	static Vec2 getNodeMiddleRightPoint(Node* node);
	static Vec2 getNodeMiddleLeftPoint(Node* node);
};

#endif