#include"ScoreScene.h"

USING_NS_CC;

Scene* ScoreScene::createScene()
{
     return ScoreScene::create();;
}

bool ScoreScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	ParticleSystem* ps = ParticleExplosion::create();
	ps->setTexture(Director::getInstance()->getTextureCache()->addImage("prize.png"));
	ps->setPosition(Point(200, 400));
	this->addChild(ps, 10);

	auto sp = Sprite::create("prize.png");
	sp->setPosition(Vec2(visibleSize.width *0.75 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(sp, 0);
	
	//Go back button
	auto goBack = Label::createWithTTF("BACK", "fonts/Marker Felt.ttf", 24);
	auto backMenu = Menu::create();
	auto menuItem1 = MenuItemLabel::create(goBack);
	backMenu->setPosition(Vec2(visibleSize.width *0.1 + origin.x, visibleSize.height*0.05 + origin.y));
	menuItem1->setCallback([&](cocos2d::Ref *sender) {
		CCDirector::sharedDirector()->replaceScene(HelloWorld::createScene());
	});
	backMenu->addChild(menuItem1, 0);
	this->addChild(backMenu, 0);

	auto label = Label::createWithTTF("Top Scores", "fonts/Marker Felt.ttf", 64);
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
	int index = 0;
	auto itemlabel = Label::createWithTTF(labelConfig, "00000");
	auto menuItem = MenuItemLabel::create(itemlabel);
	while (index <= 4)
	{
		itemlabel = Label::createWithTTF(labelConfig, std::to_string(0));
		itemlabel->setColor(ccc3(229, 240, 247));
		menuItem = MenuItemLabel::create(itemlabel);
		menuItem->setPosition(Vec2(origin.x + visibleSize.width / 4, origin.y + visibleSize.width / 2-100*index++));
		mainmenu->addChild(menuItem, 2);
		//mainmenu->setPosition(Vec2::ZERO);
	}

	//add main menu
	mainmenu->setPosition(Vec2::ZERO);
	this->addChild(mainmenu, 1);
	return true;
}

