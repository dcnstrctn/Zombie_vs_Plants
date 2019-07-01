/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "ScoreScene.h"
#include "LevelScene.h"


USING_NS_CC;
Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    /*auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);*/

    /////////////////////////////
    // 3. add your codes below...
	//title
	auto label = Label::createWithTTF("Zombies vs. Plants", "fonts/Marker Felt.ttf", 64);
	label->enableGlow(Color4B::WHITE);
	label->setColor(ccc3(255, 215, 0));
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height-32));
	this->addChild(label, 1);
	
	ParticleSystem* ps = ParticleRain::create();
	//ParticleSystem* ps = ParticleExplosion::create();
	//ParticleSystem* ps = ParticleFire::create();
	ps->setTexture(Director::getInstance()->getTextureCache()->addImage("rain.png"));
	ps->setPosition(Vec2(origin.x+visibleSize.width/2, origin.y+visibleSize.height));
	this->addChild(ps, 10);

	//用TTF创建菜单
	TTFConfig labelConfig;
	labelConfig.fontFilePath = "fonts/Marker Felt.ttf";
	labelConfig.fontSize = 64;
	labelConfig.glyphs = GlyphCollection::DYNAMIC;
	labelConfig.outlineSize = 0;
	labelConfig.customGlyphs = nullptr;
	labelConfig.distanceFieldEnabled = false;
	
	//add main menu
	auto mainmenu = Menu::create();

	//start game
	auto itemlabel = Label::createWithTTF(labelConfig, "Start Game");
	itemlabel->setColor(ccc3(218, 165, 32));
	auto menuItem = MenuItemLabel::create(itemlabel);
	menuItem->setCallback([&](cocos2d::Ref *sender) {
		CCDirector::sharedDirector()->replaceScene(LevelScene::createScene());
	});
	menuItem->setPosition(Vec2(origin.x + visibleSize.width / 4, origin.y+visibleSize.width/2-50));
	mainmenu->addChild(menuItem, 2);
	mainmenu->setPosition(Vec2::ZERO);

	//exit
	itemlabel = Label::createWithTTF(labelConfig, "Exit");
	itemlabel->setColor(ccc3(218, 165, 32));
	menuItem = MenuItemLabel::create(itemlabel);
	menuItem->setCallback([&](cocos2d::Ref *sender) {
		menuCloseCallback(sender);
	});
	menuItem->setPosition(Vec2(origin.x + visibleSize.width / 4, origin.y + visibleSize.width / 2 - 200));
	mainmenu->addChild(menuItem, 2);
	mainmenu->setPosition(Vec2::ZERO);

	//add main menu
	mainmenu->setPosition(Vec2::ZERO);
	this->addChild(mainmenu, 1);

	

    // add "zombie" splash screen"
	Sprite *sp = Sprite::create("zombie_football/0.png");
	sp->setPosition(Vec2(visibleSize.width *0.85 + origin.x, visibleSize.height / 2 + origin.y));
	Vector<SpriteFrame*> Frames;
	for (int i = 0; i < 11; i++) {
		auto fileName = StringUtils::format("zombie_football/%d.png", i);
		auto frame = SpriteFrame::create(fileName, Rect(0, 0, 154,160));
		Frames.pushBack(frame);
	}
	auto ani = Animation::createWithSpriteFrames(Frames, 0.1f);
	auto anim = RepeatForever::create(Animate::create(ani));
	sp->runAction(anim);
	this->addChild(sp);

	Sprite *sp2 = Sprite::create("Chomper_attack/0.png");
	sp2->setPosition(Vec2(visibleSize.width *0.65 + origin.x, visibleSize.height / 2 + origin.y));
	Vector<SpriteFrame*> Frames2;
	for (int i = 0; i < 9; i++) {
		auto fileName2 = StringUtils::format("Chomper_attack/%d.png", i);
		auto frame2 = SpriteFrame::create(fileName2, Rect(0, 0, 130, 114));
		Frames2.pushBack(frame2);
	}
	auto ani2 = Animation::createWithSpriteFrames(Frames2, 0.1f);
	auto anim2 = RepeatForever::create(Animate::create(ani2));
	sp2->runAction(anim2);
	this->addChild(sp2);

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
