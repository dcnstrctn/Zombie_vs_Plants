#include"PassScene.h"

USING_NS_CC;

Scene* PassScene::createScene()
{
	return PassScene::create();;
}

bool PassScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/*ParticleSystem* ps = ParticleGalaxy::create();
	ps->setTexture(Director::getInstance()->getTextureCache()->addImage("prize.png"));
	ps->setPosition(Point(400, 400));
	this->addChild(ps, 10);*/

	Sprite *sp = Sprite::create("dancing/0.png");
	sp->setPosition(Vec2(visibleSize.width *0.5 + origin.x, visibleSize.height / 2 + origin.y + 120));
	Vector<SpriteFrame*> Frames;
	for (int i = 0; i < 22; i++) {
		auto fileName = StringUtils::format("dancing/%d.png", i);
		auto frame = SpriteFrame::create(fileName, Rect(0, 0, 166, 144));
		Frames.pushBack(frame);
	}
	auto ani = Animation::createWithSpriteFrames(Frames, 0.1f);
	auto anim = RepeatForever::create(Animate::create(ani));
	sp->runAction(anim);
	this->addChild(sp);

	//Go back button
	auto goBack = Label::createWithTTF("BACK", "fonts/Marker Felt.ttf", 24);
	auto backMenu = Menu::create();
	auto menuItem1 = MenuItemLabel::create(goBack);
	backMenu->setPosition(Vec2(visibleSize.width *0.5 + origin.x, visibleSize.height*0.05 + origin.y));
	menuItem1->setCallback([&](cocos2d::Ref *sender) {
		CCDirector::sharedDirector()->replaceScene(HelloWorld::createScene());
	});
	backMenu->addChild(menuItem1, 0);
	this->addChild(backMenu, 0);

	auto label = Label::createWithTTF("YOU WIN", "fonts/Marker Felt.ttf", 128);
	label->enableGlow(Color4B::YELLOW);
	label->setColor(ccc3(50, 205, 50));
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));
	this->addChild(label, 1);


	return true;
}