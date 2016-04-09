#include "PointHelper.h"

Vec2 PointHelper::getNodeLeftTopPoint(Node* node){
	Vec2 point = node->getPosition() - Vec2(node->getAnchorPoint().x * node->getContentSize().width, -node->getAnchorPoint().y * node->getContentSize().height);
	return point;
}
Vec2 PointHelper::getNodeLeftBottomPoint(Node* node){
	Vec2 point = node->getPosition() - Vec2(node->getAnchorPoint().x * node->getContentSize().width, node->getAnchorPoint().y * node->getContentSize().height);
	return point;

}
Vec2 PointHelper::getNodeRightTopPoint(Node* node){
	Vec2 point = node->getPosition() + Vec2(node->getAnchorPoint().x * node->getContentSize().width, node->getAnchorPoint().y * node->getContentSize().height);
	return point;

}
Vec2 PointHelper::getNodeRightBottomPoint(Node* node){
	Vec2 point = node->getPosition() + Vec2(node->getAnchorPoint().x * node->getContentSize().width, -node->getAnchorPoint().y * node->getContentSize().height);
	return point;
}
Vec2 PointHelper::getNodeCenterPoint(Node* node){
	Vec2 point = PointHelper::getNodeLeftBottomPoint(node) + node->getContentSize() / 2;
	return point;
}
Vec2 PointHelper::getNodeMiddleTopPoint(Node* node){
	Vec2 point = PointHelper::getNodeCenterPoint(node) + Vec2(0, node->getContentSize().height / 2);
	return point;
}
Vec2 PointHelper::getNodeMiddleBottomPoint(Node* node){
	Vec2 point = PointHelper::getNodeCenterPoint(node) - Vec2(0, node->getContentSize().height / 2);
	return point;
}
Vec2 PointHelper::getNodeMiddleRightPoint(Node* node){
	Vec2 point = PointHelper::getNodeCenterPoint(node) + Vec2(node->getContentSize().width / 2, 0);
	return point;
}
Vec2 PointHelper::getNodeMiddleLeftPoint(Node* node){
	Vec2 point = PointHelper::getNodeCenterPoint(node) - Vec2(node->getContentSize().width / 2, 0);
	return point;
}