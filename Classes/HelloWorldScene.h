#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class HelloWorld : public cocos2d::Layer, public TableViewDataSource,public TableViewDelegate
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	Size cellSizeForTable(cocos2d::extension::TableView * table);

	virtual void tableCellTouched(TableView* table, TableViewCell* cell) override;

	virtual void tableCellHighlight(TableView* table, TableViewCell* cell) {};

	// Í¨¹ý TableViewDataSource ¼Ì³Ð
	virtual TableViewCell * tableCellAtIndex(TableView * table, ssize_t idx) override;
	virtual ssize_t numberOfCellsInTableView(TableView * table) override;

	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
