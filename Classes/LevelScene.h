#pragma once
#include "cocos2d.h"
#include"HelloWorldScene.h"
extern int level;
class LevelScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	//virtual void onEnter();

	void menuCloseCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(LevelScene);
};