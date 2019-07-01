/*#include "GAME1.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

Scene*GAME1::createScene()
{
	Scene *scene = Scene::create();

}
bool GAME1::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	//加载地图层
	TMXTiledMap* map_2 = TMXTiledMap::create("res/test1.tmx");
	this->addChild(map_2);

	//添加精灵层
	Sprite *Hero = Sprite::create("res/run1.png");
	this->addChild(Hero);
	Hero->setAnchorPoint(Vec2(0, 0));
	Hero->setPosition(Vec2(90, 90));
	
	return true;
}*/