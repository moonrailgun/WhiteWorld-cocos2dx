#include "GameMap.h"
#include "GlobalDefine.h"
#include "GlobalData.h"
#include "DialogueHelper.h"

int GameMap::dialogueIndex = 0;

GameMap* GameMap::createGameMap(char* mapName){
	GameMap* gameMap = GameMap::create();

	auto map = GameMap::loadMap(mapName);
	map->setPosition(gameMap->getContentSize() / 2 - map->getContentSize() / 2);//设置居中
	gameMap->_map = map;
	gameMap->registerInspectObjects();
	gameMap->addChild(map);

	return gameMap;
}

TMXTiledMap* GameMap::loadMap(char *mapName){
	auto name = String::createWithFormat("map/%s.tmx", mapName);
	log("is loading map which named %s [%s]", mapName, name->getCString());
	auto map = TMXTiledMap::create(name->getCString());//加载地图对象

	if (map == NULL){
		log("loading error: no such tmx file");
	}
	else
	{
		log("loading completed");
	}

	return map;
}

Player* GameMap::loadPlayer(){
	auto player = Player::create();
	this->_player = player;
	this->_player->setAnimation("sprite", 0.15f);
	this->addChild(player);

	auto group = _map->getObjectGroup("players");
	auto playerSpawnPoint = group->getObject("playerSpawnPoint");
	auto x = playerSpawnPoint["x"].asFloat();
	auto y = playerSpawnPoint["y"].asFloat();
	auto tile = _map->getLayer("bottom")->getTileAt(getTileCoordinateAt(Vec2(x, y)));
	tile->setColor(Color3B::RED);

	Vec2 pos = tile->getPosition() + getMapLeftBottomPos() + tile->getContentSize() / 2;
	this->_player->setPosition(pos);

	return player;
}

Vec2 GameMap::getTileCoordinateAt(Vec2 posInPixel){
	Size tileSize = this->_map->getTileSize();
	Size mapSize = this->_map->getMapSize();
	float x = floor(posInPixel.x / tileSize.width);
	float y = floor((mapSize.height * tileSize.height - posInPixel.y) / tileSize.height);

	return Vec2(x, y);
}

Vec2 GameMap::getTilePosBy(Vec2 tileCoordinate) {
	Size tileSize = this->_map->getTileSize();
	Size mapSize = this->_map->getMapSize();
	float x = floor(tileCoordinate.x * tileSize.width);
	float y = floor(mapSize.height * tileSize.height - tileCoordinate.y * tileSize.height);

	return Vec2(x, y);
}

void GameMap::setMapZoom(float _mapZoom){
	this->_mapZoom = _mapZoom;
	this->setScale(_mapZoom);
}

void GameMap::onMapLoadCompleted(){
	auto map = this->_map;
	if (map == NULL){
		log("error: map is null");
		return;
	}

	ValueMap properties = map->getProperties();
	if (properties == ValueMapNull){ return; }

	int triggerPlotId = properties.at("triggerPlotId").asInt();
	if (triggerPlotId != 0 && dialogueManager != NULL){
		//触发对话事件
		triggerPlot(triggerPlotId);
	}
}

void GameMap::moveMapTo(Vec2 pos){
	this->_map->setPosition(pos);
}

void GameMap::setMapToCenter(Vec2 anchor){
	this->_map->setAnchorPoint(Vec2(0.5, 0.5));//设置锚点
	this->_map->setPosition(WINSIZE / 2);//设置居中
}

void GameMap::setPlayerToCenter(){
	if (_player == NULL || _map == NULL){ return; }

	auto playerPos = _player->getPosition();
	auto mapPos = _map->getPosition();
	_player->setPosition(WINSIZE / 2);
	_map->setPosition(mapPos + WINSIZE / 2 - playerPos);
}

void GameMap::tryMovePlayer(Vec2 toPos) {
	//禁止移动事项
	if (isShowDialogue){ return; }

	Vec2 coor = getTileCoordinateAt(toPos - getMapLeftBottomPos());
	Size mapSize = this->_map->getMapSize();

	if (coor.x >= mapSize.width || coor.x < 0 || coor.y >= mapSize.height || coor.y < 0){
		return;//要到达目标在地图外
	}

	TMXLayer* blockLayer = _map->getLayer("block");
	if (blockLayer != NULL &&  blockLayer->getTileAt(coor) != NULL){
		return;//要到达的目标有障碍物
	}

	ValueMap inspectObject = getInspectObjectAt(toPos);
	if (inspectObject != ValueMapNull && inspectObject["isBlock"].asBool() == true){
		return;//当要到达的位置有可以调查的物体且该物体属性为可以被阻挡时
	}

	_player->setPosition(toPos);
}

Vec2 GameMap::getMapLeftBottomPos(){
	return _map->getPosition() - Vec2(_map->getAnchorPoint().x * _map->getContentSize().width, _map->getAnchorPoint().y * _map->getContentSize().height);
}

void GameMap::registerInspectObjects(){
	auto group = _map->getObjectGroup("inspect");
	if (group == NULL){ return; }

	_inspectObjects.clear();//清空之前元素
	auto objects = group->getObjects();
	for (auto object : objects){
		auto obj = object.asValueMap();
		_inspectObjects.push_back(obj);
	}
}

ValueMap GameMap::getInspectObjectAt(Vec2 pos){
	Vec2 mapPos = pos - getMapLeftBottomPos();

	for (ValueMap object : _inspectObjects){
		float width = object["width"].asFloat();
		float height = object["height"].asFloat();
		float x = object["x"].asFloat();
		//float y = _map->getContentSize().height - object["y"].asFloat() - height;
		float y = object["y"].asFloat();

		if (mapPos.x >= x && mapPos.x <= x + width && mapPos.y >= y && mapPos.y <= y + height){
			return object;
		}
	}

	return ValueMapNull;
}

void GameMap::inspect(){
	auto direcion = _player->direction;
	Vec2 delta = Vec2::ZERO;
	switch (direcion){
	case EntityDirection::Up:
		delta = Vec2(0, inspectDis);
		break;
	case EntityDirection::Down:
		delta = Vec2(0, -inspectDis);
		break;
	case EntityDirection::Left:
		delta = Vec2(-inspectDis, 0);
		break;
	case EntityDirection::Right:
		delta = Vec2(inspectDis, 0);
		break;
	default:
		break;
	}

	Vec2 targetPos = _player->getPosition() + delta;
	inspectWith(targetPos);
}

void GameMap::inspectWith(Vec2 targetMapPos) {
	auto inspectObject = getInspectObjectAt(targetMapPos);
	if (inspectObject != ValueMapNull){
		std::string inspectType = inspectObject["type"].asString();
		if (inspectType == "teleport"){
			//传送类型
			std::string inspectTo = inspectObject["to"].asString();
			log("is try teleport to %s", inspectTo.c_str());
		}
	}
}

void GameMap::triggerPlot(int triggerPlotId, const char *dialogueFileName){
	if (triggerPlotId != 0) {
		DialogueHelper* dialogueHelper = DialogueHelper::parseWithFile(dialogueFileName);
		auto dialogue = dialogueHelper->getDialogueById(triggerPlotId);
		if (!dialogue.empty()){
			auto parentNode = this->getParent();
			dialogueManager->showDialogue(parentNode);
			isShowDialogue = true;

			auto type = dialogue.at(0).type;
			if (type == DialogueType::string){
				//文本类型
				DialogueHelper::updateDialogueText(dialogue.at(0).content.c_str());
			}
			else if (type == DialogueType::option){
				//选项类型
				DialogueHelper::updateDialogueOptions(dialogue.at(0).options);
			}

			GameMap::dialogueIndex = 1;
			addDialogueTouchEvent(dialogue);
		}
	}
}

void GameMap::addDialogueTouchEvent(std::vector<DialogueData> dialogue){
	int dialogueMaxIndex = dialogue.size();
	auto dialogueBg = dialogueManager->getDialogueBg();
	//定义点击回调事件
	onMapTouchBegan = [&, dialogue, dialogueBg, dialogueMaxIndex](Touch *  touch, Event *  unused_event){
		if (GameMap::dialogueIndex >= dialogueMaxIndex){
			//对话完毕
			dialogueBg->getEventDispatcher()->removeEventListenersForTarget(dialogueBg);//关闭点击事件
			dialogueManager->hideDialogue();
			this->isShowDialogue = false;

			return true;
		}

		updateDialogueContent(dialogue);
		
		return true;
	};

	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = onMapTouchBegan;
	dialogueBg->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, dialogueBg);
}

void GameMap::updateDialogueContent(std::vector<DialogueData> dialogue){
	auto dialogueBg = dialogueManager->getDialogueBg();
	DialogueData data = dialogue.at(GameMap::dialogueIndex);
	DialogueType type = data.type;
	if (type == DialogueType::string) {
		DialogueHelper::updateDialogueText(data.content.c_str());
		GameMap::dialogueIndex++;
	}
	else if (type == DialogueType::option) {
		DialogueHelper::updateDialogueText("");
		std::function<void(const char*, int)> callback = [&, dialogue, dialogueBg](const char* text, int toId){
			log("%s-%d", text, toId);//todo
			if (toId > 0){
				log("跳转到对话ID：%d ------------------------未实现", toId);
			}
			dialogueIndex++;
			updateDialogueContent(dialogue);
		};
		DialogueHelper::updateDialogueOptions(data.options, callback);
	}
}