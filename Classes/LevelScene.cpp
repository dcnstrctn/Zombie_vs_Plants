#include"LevelScene.h"
#include"GameScene.h"
#include"ui/CocosGUI.h"
using namespace std;
USING_NS_CC;

int level = 0;
Weapon* GameScene::weaponList[8];
int GameScene::num_weapon = 0;
CCSprite* GameScene::weapons[8];//to display
Weapon* GameScene::weaponNow = new Weapon(0);
int GameScene::HP = 100;

Scene* LevelScene::createScene()
{
	return LevelScene::create();
}

bool LevelScene::init()
{
	GameScene::weaponList[8];
	GameScene::num_weapon = 0;
	GameScene::weapons[8];//to display
	GameScene::weaponNow = new Weapon(0);
	GameScene::HP = 100;
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	ParticleSystem* ps = ParticleFire::create();
	ps->setTexture(Director::getInstance()->getTextureCache()->addImage("rain.png"));
	ps->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height-200));
	this->addChild(ps, 10);

	//Go back button
    auto goBack = Label::createWithTTF("BACK", "fonts/Marker Felt.ttf",24);
	auto backMenu = Menu::create();
	auto menuItem1 = MenuItemLabel::create(goBack);
	backMenu->setPosition(Vec2(visibleSize.width *0.1 + origin.x, visibleSize.height*0.05 + origin.y));
	menuItem1->setCallback([&](cocos2d::Ref *sender) {
		CCDirector::sharedDirector()->replaceScene(HelloWorld::createScene());
	});
	backMenu->addChild(menuItem1, 0);
	this->addChild(backMenu, 0);

	auto label = Label::createWithTTF("Choose a level", "fonts/Marker Felt.ttf", 64);
	label->enableGlow(Color4B::WHITE);
	label->setColor(ccc3(255, 215, 0));
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));
	this->addChild(label, 1);

	//用TTF创建菜单
	TTFConfig labelConfig;
	labelConfig.fontFilePath = "fonts/Marker Felt.ttf";
	labelConfig.fontSize = 48;
	labelConfig.glyphs = GlyphCollection::DYNAMIC;
	labelConfig.outlineSize = 0;
	labelConfig.customGlyphs = nullptr;
	labelConfig.distanceFieldEnabled = false;

	//add main menu
	auto mainmenu = Menu::create();
	int index = 2;

	//level 1
	auto itemlabel = Label::createWithTTF(labelConfig, "1");
	auto menuItem = MenuItemLabel::create(itemlabel);
	itemlabel->setColor(ccc3(229, 240, 247));
	menuItem->setCallback([&](cocos2d::Ref *sender) {
		level = 1;
		CCDirector::sharedDirector()->replaceScene(GameScene::createScene());
	});
	menuItem->setPosition(Vec2(origin.x + visibleSize.width / 4, origin.y + visibleSize.width / 2));
	mainmenu->addChild(menuItem, 2);
	//mainmenu->setPosition(Vec2::ZERO);

	//level 2
	itemlabel = Label::createWithTTF(labelConfig, "2");
	menuItem = MenuItemLabel::create(itemlabel);
	itemlabel->setColor(ccc3(229, 240, 247));
	menuItem->setCallback([&](cocos2d::Ref *sender) {
		level = 2;
		CCDirector::sharedDirector()->replaceScene(GameScene::createScene());
	});
	menuItem->setPosition(Vec2(origin.x + visibleSize.width / 4, origin.y + visibleSize.width / 2 - 100));
	mainmenu->addChild(menuItem, 2);

	//level 3
	itemlabel = Label::createWithTTF(labelConfig, "3");
	menuItem = MenuItemLabel::create(itemlabel);
	itemlabel->setColor(ccc3(229, 240, 247));
	menuItem->setCallback([&](cocos2d::Ref *sender) {
		level = 3;
		CCDirector::sharedDirector()->replaceScene(GameScene::createScene());
	});
	menuItem->setPosition(Vec2(origin.x + visibleSize.width / 4, origin.y + visibleSize.width / 2 - 200));
	mainmenu->addChild(menuItem, 2);

	//level 4
	itemlabel = Label::createWithTTF(labelConfig, "4");
	menuItem = MenuItemLabel::create(itemlabel);
	itemlabel->setColor(ccc3(229, 240, 247));
	menuItem->setCallback([&](cocos2d::Ref *sender) {
		level = 4;
		CCDirector::sharedDirector()->replaceScene(GameScene::createScene());
	});
	menuItem->setPosition(Vec2(origin.x + visibleSize.width / 4, origin.y + visibleSize.width / 2 - 300));
	mainmenu->addChild(menuItem, 2);
	
	//level 5
	itemlabel = Label::createWithTTF(labelConfig, "5");
	menuItem = MenuItemLabel::create(itemlabel);
	itemlabel->setColor(ccc3(229, 240, 247));
	menuItem->setCallback([&](cocos2d::Ref *sender) {
		level = 5;
		CCDirector::sharedDirector()->replaceScene(GameScene::createScene());
	});
	menuItem->setPosition(Vec2(origin.x + visibleSize.width / 4, origin.y + visibleSize.width / 2 - 400));
	mainmenu->addChild(menuItem, 2);

	//level 6
	itemlabel = Label::createWithTTF(labelConfig, "6");
	menuItem = MenuItemLabel::create(itemlabel);
	itemlabel->setColor(ccc3(229, 240, 247));
	menuItem->setCallback([&](cocos2d::Ref *sender) {
		level = 6;
		CCDirector::sharedDirector()->replaceScene(GameScene::createScene());
	});
	menuItem->setPosition(Vec2(origin.x + visibleSize.width / 4*3, origin.y + visibleSize.width / 2 ));
	mainmenu->addChild(menuItem, 2);

	//level 7
	itemlabel = Label::createWithTTF(labelConfig, "7");
	menuItem = MenuItemLabel::create(itemlabel);
	itemlabel->setColor(ccc3(229, 240, 247));
	menuItem->setCallback([&](cocos2d::Ref *sender) {
		level = 7;
		CCDirector::sharedDirector()->replaceScene(GameScene::createScene());
	});
	menuItem->setPosition(Vec2(origin.x + visibleSize.width / 4 * 3, origin.y + visibleSize.width / 2-100));
	mainmenu->addChild(menuItem, 2);

	//level 8
	itemlabel = Label::createWithTTF(labelConfig, "8");
	menuItem = MenuItemLabel::create(itemlabel);
	itemlabel->setColor(ccc3(229, 240, 247));
	menuItem->setCallback([&](cocos2d::Ref *sender) {
		level = 8;
		CCDirector::sharedDirector()->replaceScene(GameScene::createScene());
	});
	menuItem->setPosition(Vec2(origin.x + visibleSize.width / 4 * 3, origin.y + visibleSize.width / 2-200));
	mainmenu->addChild(menuItem, 2);

	//level 9
	itemlabel = Label::createWithTTF(labelConfig, "9");
	menuItem = MenuItemLabel::create(itemlabel);
	itemlabel->setColor(ccc3(229, 240, 247));
	menuItem->setCallback([&](cocos2d::Ref *sender) {
		level = 9;
		CCDirector::sharedDirector()->replaceScene(GameScene::createScene());
	});
	menuItem->setPosition(Vec2(origin.x + visibleSize.width / 4 * 3, origin.y + visibleSize.width / 2-300));
	mainmenu->addChild(menuItem, 2);

	//level 10
	itemlabel = Label::createWithTTF(labelConfig, "10");
	menuItem = MenuItemLabel::create(itemlabel);
	itemlabel->setColor(ccc3(229, 240, 247));
	menuItem->setCallback([&](cocos2d::Ref *sender) {
		level = 10;
		CCDirector::sharedDirector()->replaceScene(GameScene::createScene());
	});
	menuItem->setPosition(Vec2(origin.x + visibleSize.width / 4 * 3, origin.y + visibleSize.width / 2-400));
	mainmenu->addChild(menuItem, 2);
	//add main menu
	mainmenu->setPosition(Vec2::ZERO);
	this->addChild(mainmenu, 1);
	return true;
}
