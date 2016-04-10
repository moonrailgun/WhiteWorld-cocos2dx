#ifndef __GameMap__H__
#define __GameMap__H__

#include "cocos2d.h"
#include "Player.h"
#include "DialogueHelper.h"

USING_NS_CC;

class GameMap : public Layer{
public:
	static GameMap* createGameMap(char* mapName);
	CREATE_FUNC(GameMap);

	static TMXTiledMap* loadMap(char* mapName);
	Player* loadPlayer();
	void setMapZoom(float _mapZoom);

	void onMapLoadCompleted();

	void moveMapTo(Vec2 pos);
	void setMapToCenter(Vec2 anchor = Vec2(0.5, 0.5));
	void setPlayerToCenter();

	void tryMovePlayer(Vec2 toPos);
	//交互操作
	void inspect();
	void inspectWith(Vec2 targetMapPos);

	//触发对话
	void triggerPlot(int triggerPlotId, const char *dialogueFileName = "common");

	bool isShowDialogue = false;

	EventListenerTouchOneByOne::ccTouchBeganCallback onMapTouchBegan;//地图触摸回调
	static int dialogueIndex;//对话索引编号
	void addDialogueTouchEvent(std::vector<DialogueData> dialogue);//添加触摸事件
	void updateDialogueContent(std::vector<DialogueData> dialogue);//更新对话框内容
private:
	TMXTiledMap* _map;
	Player* _player;
	float _mapZoom = 1;
	float inspectDis = 32.0f;
	std::vector<Vec2> _blockTileCoorList;
	std::vector<ValueMap> _inspectObjects;
	
	//通过在该层中的像素坐标获取图块坐标
	Vec2 getTileCoordinateAt(Vec2 posInPixel);
	//通过图块坐标获取像素坐标
	Vec2 getTilePosBy(Vec2 tileCoordinate);
	//获取地图左下角坐标
	Vec2 getMapLeftBottomPos();
	//注册交互对象
	void registerInspectObjects();
	//根据坐标获取调查对象
	ValueMap getInspectObjectAt(Vec2 pos);
};

#endif