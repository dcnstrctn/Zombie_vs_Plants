#include "GameScene.h"
#include "LevelScene.h"
#include "SimpleAudioEngine.h"
#include <string>
USING_NS_CC;
using namespace std;
//weaponNow = new Weapon(0);
Scene* GameScene::createScene()
{
	return GameScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	count = 0;
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//获取屏幕宽度和高度
	screenWidth = visibleSize.width;
	screenHeight = visibleSize.height;

	//Go back button
	auto goBack = Label::createWithTTF("BACK", "fonts/Marker Felt.ttf", 24);
	auto backMenu = Menu::create();
	auto menuItem1 = MenuItemLabel::create(goBack);
	backMenu->setPosition(Vec2(visibleSize.width *0.1 + origin.x, visibleSize.height*0.05 + origin.y));
	menuItem1->setCallback([&](cocos2d::Ref *sender) {
		CCDirector::sharedDirector()->replaceScene(LevelScene::createScene());
	});
	backMenu->addChild(menuItem1, 0);
	this->addChild(backMenu, 10);

	//bullet label
	bulletnum = Label::createWithTTF("Bullet: " + StringUtils::format("%d", weaponNow->bullet), "fonts/Marker Felt.ttf", 24);
	bulletnum->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - bulletnum->getContentSize().height - 32));
	this->addChild(bulletnum, 10);
	CCLOG("%d", level);

	//level label
	levelLabel = Label::createWithTTF("Level " + StringUtils::format("%d", level), "fonts/Marker Felt.ttf", 32);
	levelLabel->setColor(ccc3(255, 215, 0));
	this->addChild(levelLabel, 10);
	
	//monster label
	monsterLabel = Label::createWithTTF("Monster: " + StringUtils::format("%d", _plantsVector.size()), "fonts/Marker Felt.ttf", 32);
	this->addChild(monsterLabel, 10);
	
	//添加地图层
	GAME1 = TMXTiledMap::create(StringUtils::format("res/GAME%d.tmx", level));
	GAME1->setAnchorPoint(Vec2::ZERO);
	GAME1->setPosition(Vec2::ZERO);
	this->addChild(GAME1);

	tileWidth = int(GAME1->getTileSize().width);
	tileHeight = int(GAME1->getTileSize().height);
	mapHeight = int(GAME1->getMapSize().height);
	mapWidth = int(GAME1->getMapSize().width);

	
	//创建hero精灵
	auto objects = GAME1->getObjectGroup("Objects");
	ValueMap map = objects->getObject("hero");
	int x = map.at("x").asInt();
	int y = map.at("y").asInt();
	GameScene::m_hero = Hero::create();
	m_hero->changeWeapon(weaponNow->type);
	m_hero->m_damage = weaponNow->damage;
	m_hero->m_HP = HP;
	m_hero->setTexture(m_hero->folder + "/0.png");
	m_hero->setFlippedY(false);
	m_hero->setFlippedX(false);
	m_hero->setPosition(x, y);
	m_hero->setAnchorPoint(Vec2(0.5, 0));
	this->addChild(m_hero, 1);


	//初始化读取地图中的所有网格，并确定网格对象是否是障碍物
	for (int i = 0; i < mapWidth; i++)
	{
		Vector<Grid*>inner;
		for (int j = 0; j < mapHeight; j++)
		{
			Grid* p = Grid::create(i, j);
			inner.pushBack(p);
		}
		gridVector.push_back(inner);
	}

	//获取障碍物层
	collidable = GAME1->getLayer("collidable");
	collidable->setVisible(false);

	GAME1->getLayer("enemy_class_1")->setVisible(0);
	GAME1->getLayer("enemy_class_2")->setVisible(0);
	GAME1->getLayer("enemy_class_3")->setVisible(0);

	//获取陷阱层
	trap = GAME1->getLayer("trap");
	trap->setVisible(false);

	//循环保存根据每个网格的坐标查找GID，判断是否通过
	for (int i = 0; i < gridVector.size(); i++)
	{
		Vector<Grid*>inner = gridVector[i];
		{
			for (int j = 0; j < inner.size(); j++)
			{
				Grid* grid = inner.at(j);
				Vec2 tiledCoord = Vec2(grid->getX(), grid->getY());
				if (tiledCoord.x<0 || tiledCoord.x>mapWidth || tiledCoord.y<0 || tiledCoord.y>mapHeight)
				{
					return 0;
				}
				if (isCollision(tiledCoord, collidable))
					grid->setPass(false);
			}
		}
	}

	//获取道具层
	collectable = GAME1->getLayer("collectable");
	collectable->setVisible(false);
	medicineLayer = GAME1->getLayer("Medicine");
	weapon1Layer = GAME1->getLayer("Weapon");
	weapon2Layer = GAME1->getLayer("Weapon2");

	//lifebar
	lifebar = LoadingBar::create("blood_inside.png");
	lifebar->setScale(0.5);
	lifebar->setDirection(LoadingBar::Direction::LEFT);
	lifebar->setPercent(100);
	lifebar->setPosition(Vec2::ZERO);
	this->addChild(lifebar, 10);
	lifebar_bg = Sprite::create("background_blood.png");
	lifebar_bg->setScale(0.5);
	this->addChild(lifebar_bg, 5);

	//背包
	bag = Sprite::create("bag.png");
	bag->setPosition(Vec2::ZERO);
	this->addChild(bag, 100);

	//背包框
	bagpack = Sprite::create("bagpack.png");
	bagpack->setVisible(false);
	this->addChild(bagpack, 100);

	//武器
	Vec2 position = m_hero->getPosition();
	
	for (int i = 0; i < 8; i++)
	{
		weapons[i] = CCSprite::create();
		weapons[i]->setVisible(false);
		this->addChild(weapons[i], 101);
		weapons[i]->setPosition(Vec2(position.x - 110 + (i % 4) * 70, position.y + 35 - (i / 4) * 50));
	}
	//出口动画效果
	ValueMap exit_ = objects->getObject("exit");
	int x_e = exit_.at("x").asInt();
	int y_e = exit_.at("y").asInt();
	ps = ParticleSun::create();
	ps->setTexture(Director::getInstance()->getTextureCache()->addImage("exit.png"));
	ps->setPosition(x_e, y_e);
	this->addChild(ps, 10);
	ps->setVisible(false);

	//获取过关点
	collectable = GAME1->getLayer("collectable");
	collectable->setVisible(false);

	//键盘监听器
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	this->scheduleUpdate();
	this->schedule(schedule_selector(GameScene::shootPlants), 0.1);
	return true;
}
void GameScene::heroattackfar()
{
	auto b = Sprite::create(m_hero->folder + "/bullet.png");
	_herobullet.push_back(b);
	b->setPosition(Vec2(m_hero->getPosition().x, m_hero->getPosition().y + 70));//子弹位置上移
	this->addChild(b, 1);
	if (m_hero->face == "right")
	{
		auto action = MoveBy::create(m_hero->m_afrequency * 10, Vec2(5000, 0));
		b->runAction(action);
	}
	if (m_hero->face == "left")
	{
		auto action = MoveBy::create(m_hero->m_afrequency * 10, Vec2(-5000, 0));
		b->runAction(action);
	}
	if (m_hero->face == "up")
	{
		auto action = MoveBy::create(m_hero->m_afrequency * 10, Vec2(0, 5000));
		b->runAction(action);
	}
	if (m_hero->face == "down")
	{
		auto action = MoveBy::create(m_hero->m_afrequency * 10, Vec2(0, -5000));
		b->runAction(action);
	}
	auto repeatForever = RepeatForever::create(RotateBy::create(0.5, 360));
	b->runAction(repeatForever);
	m_hero->setTexture(m_hero->folder + "/0.png");
	m_hero->isshoot = 0;

	//子弹数-1
	weaponNow->bullet--;
	CCLOG("%d", weaponNow->bullet);
}

void GameScene::onKeyPressed(EventKeyboard::KeyCode code, Event* event)
{
	if (m_hero->m_ismoving && (code == EventKeyboard::KeyCode::KEY_A || code == EventKeyboard::KeyCode::KEY_W || code == EventKeyboard::KeyCode::KEY_S || code == EventKeyboard::KeyCode::KEY_D))
	{
		m_hero->changedirection(Vec2(0, 0));
		m_hero->stopAction(r);
	}
	else if (code == EventKeyboard::KeyCode::KEY_A || code == EventKeyboard::KeyCode::KEY_W || code == EventKeyboard::KeyCode::KEY_S || code == EventKeyboard::KeyCode::KEY_D)
	{
		m_hero->m_ismoving = 1;
		auto animation = Animation::create();
		for (int i = 1; i <= 4; i++)
		{
			animation->addSpriteFrameWithFile(m_hero->folder + StringUtils::format("/%d.png", i));
		}
		animation->setDelayPerUnit(2.0f / 8.0f);
		auto animate = Animate::create(animation);
		r = RepeatForever::create(animate);
		m_hero->runAction(r);
		if (code == EventKeyboard::KeyCode::KEY_W)
		{
			m_hero->changedirection(Vec2(0, 1));
			m_hero->face = "up";
		}
		if (code == EventKeyboard::KeyCode::KEY_A)
		{
			m_hero->setFlipX(false);
			m_hero->changedirection(Vec2(-1, 0));
			m_hero->face = "left";
		}
		if (code == EventKeyboard::KeyCode::KEY_S)
		{
			m_hero->changedirection(Vec2(0, -1));
			m_hero->face = "down";
		}
		if (code == EventKeyboard::KeyCode::KEY_D)
		{
			m_hero->setFlippedX(true);
			m_hero->changedirection(Vec2(1, 0));
			m_hero->face = "right";
		}
	}
	else if (code == EventKeyboard::KeyCode::KEY_J && m_hero->isshoot == 1)
	{
		heroattackfar();
		auto delay = DelayTime::create(0.1);
		auto s = Sequence::create(delay, CallFunc::create([=] { m_hero->isshoot = 1; }), NULL);
		m_hero->runAction(s);
	}
	if (code == EventKeyboard::KeyCode::KEY_B) {
		if (bagpack->isVisible()) {
			bagpack->setVisible(false);

			undisplayBag();
		}
		else
		{
			//generateBag();
			bagpack->setVisible(true);
			displayBag();

		}


	}
	if (bagpack->isVisible())
	{
		if (code == EventKeyboard::KeyCode::KEY_1) equip(1);
		if (code == EventKeyboard::KeyCode::KEY_2) equip(2);
		if (code == EventKeyboard::KeyCode::KEY_3) equip(3);
		if (code == EventKeyboard::KeyCode::KEY_4) equip(4);
		if (code == EventKeyboard::KeyCode::KEY_5) equip(5);
		if (code == EventKeyboard::KeyCode::KEY_6) equip(6);
		if (code == EventKeyboard::KeyCode::KEY_7) equip(7);
		if (code == EventKeyboard::KeyCode::KEY_8) equip(8);
	}
	//退出键
	if (code == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		CCDirector::sharedDirector()->replaceScene(LevelScene::createScene());
	}
}
void GameScene::onKeyReleased(EventKeyboard::KeyCode code, Event* event)
{
	if (code == EventKeyboard::KeyCode::KEY_A || code == EventKeyboard::KeyCode::KEY_W || code == EventKeyboard::KeyCode::KEY_S || code == EventKeyboard::KeyCode::KEY_D)
	{
		m_hero->m_ismoving = 0;
		m_hero->stopAction(r);
		m_hero->setTexture(m_hero->folder + "/0.png");
		if (m_hero->getdirection() == Vec2(0, 1))
		{
			if (code == EventKeyboard::KeyCode::KEY_W)
				m_hero->changedirection(Vec2(0, 0));
		}
		if (m_hero->getdirection() == Vec2(0, -1))
		{
			if (code == EventKeyboard::KeyCode::KEY_S)
				m_hero->changedirection(Vec2(0, 0));
		}
		if (m_hero->getdirection() == Vec2(-1, 0))
		{
			if (code == EventKeyboard::KeyCode::KEY_A)
				m_hero->changedirection(Vec2(0, 0));
		}
		if (m_hero->getdirection() == Vec2(1, 0))
		{
			if (code == EventKeyboard::KeyCode::KEY_D)
				m_hero->changedirection(Vec2(0, 0));
		}
	}

}

void GameScene::setViewpointCenter(Vec2 position)
{
	//让地图跟随精灵移动，超过屏幕中心的需要移动
	int x = MAX(position.x, screenWidth / 2);
	int y = MAX(position.y, screenHeight / 2);
	//不让显示区域超出地图边界
	x = MIN(x, (GAME1->getMapSize().width * GAME1->getTileSize().width - screenWidth / 2));
	y = MIN(y, (GAME1->getMapSize().height * GAME1->getTileSize().height - screenHeight / 2));
	//实际移动的位置坐标
	Point actualPosition = Vec2(x, y);
	//屏幕中心位置
	Point centerOfView = Vec2(screenWidth / 2, screenHeight / 2);
	Point viewPoint = centerOfView - actualPosition;
	//重新设置屏幕位置
	this->setPosition(viewPoint);

	//设置背包及背包框位置
	bag->setPosition(Vec2(-viewPoint.x + 80, -viewPoint.y + 80));
	bagpack->setPosition(position);

	lifebar->setPosition(Vec2(-viewPoint.x + 237, -viewPoint.y + 700));
	lifebar_bg->setPosition(Vec2(-viewPoint.x + 200, -viewPoint.y + 700));
	//设置血条位置

	//display bullet number
	bulletnum->setString("Bullet: " + StringUtils::format("%d", weaponNow->bullet));
	bulletnum->setPosition(Vec2(-viewPoint.x + 500, -viewPoint.y + 700));

	//display level
	levelLabel->setPosition(Vec2(-viewPoint.x + 800, -viewPoint.y + 700));

	//display number of monsters
	monsterLabel->setPosition(Vec2(-viewPoint.x + 500, -viewPoint.y + 80));
	monsterLabel->setString("Monster: " + StringUtils::format("%d",_plantsVector.size()));
}

Vec2 GameScene::tiledCoordForPosition(Vec2 position)
{
	int x = int(position.x / tileWidth);
	int y = int((mapHeight * tileHeight - position.y) / tileHeight);
	return Vec2(x, y);
}

// tile坐标转成瓦片格子中心的OpenGL坐标

Vec2 GameScene::positionForTileCoord(const Vec2 pos)
{
	int x = (int)(pos.x * (GAME1->getTileSize().width / CC_CONTENT_SCALE_FACTOR()));
	float pointHeight = GAME1->getTileSize().height / CC_CONTENT_SCALE_FACTOR();
	int y = (int)((GAME1->getMapSize().height * pointHeight) - (pos.y * pointHeight));
	return Vec2(x, y);
}
//每帧调用的函数
void  GameScene::update(float duration)
{
	//实时更新HP
	HP = m_hero->m_HP;
	
	if (weaponNow->bullet <= 0)
	{
		popWeapons();
	}
	lifebar->setPercent(m_hero->m_HP);
	Vec2 m_position = m_hero->getPosition();
	int m_speed = m_hero->getspeed();
	Vec2 m_direction = m_hero->getdirection();
	Vec2 prePosition = Vec2(m_position.x, m_position.y);
	m_position = m_position + m_speed * m_direction * duration;


	Vec2 tilePosition = tiledCoordForPosition(m_position);
	//碰撞判断
	if (tilePosition.x<0 || tilePosition.x>mapWidth || tilePosition.y<0 || tilePosition.y>mapHeight)
	{
		return;
	}
	if (isCollision(tilePosition, collidable))
		m_position = prePosition;


	//物品的拾捡
	if (tilePosition.x<0 || tilePosition.x>mapWidth || tilePosition.y<0 || tilePosition.y>mapHeight)
	{
		return;
	}
	if (isCollision(tilePosition, medicineLayer))
	{
		collectable->setTileGID(0, tiledCoordForPosition(m_position));
		medicineLayer->setTileGID(0, tiledCoordForPosition(m_position));
		m_hero->addToBlood();
	}
	if (tilePosition.x<0 || tilePosition.x>mapWidth || tilePosition.y<0 || tilePosition.y>mapHeight)
	{
		return;
	}
	if (isCollision(tilePosition, weapon1Layer))
	{
		collectWeapon(tilePosition, weapon1Layer, 1);
	}
	if (tilePosition.x<0 || tilePosition.x>mapWidth || tilePosition.y<0 || tilePosition.y>mapHeight)
	{
		return;
	}
	if (isCollision(tilePosition, weapon2Layer))
	{
		collectWeapon(tilePosition, weapon2Layer, 2);
	}
	if (isPass)
	{
		if (isCollision(tilePosition, collectable))
		{
			if (level < 10)
			{
				level++;
				CCDirector::sharedDirector()->replaceScene(GameScene::createScene());
				m_position = prePosition;
			}
			else
				CCDirector::sharedDirector()->replaceScene(PassScene::createScene());
		}
		ps->setVisible(true);
	}
	for (int i = 0; i < _herobullet.size(); i++)
	{
		Vec2 a = tiledCoordForPosition(_herobullet.at(i)->getPosition());
		if (hittarget(_herobullet.at(i)))
		{
			_herobullet.at(i)->removeFromParent();
			_herobullet.erase(_herobullet.begin() + i);
			i--;
		}

		else if (a.x<0 || a.x>mapWidth || a.y<0 || a.y>mapHeight)
		{
			return;
		}
		else if (isCollision(a, collidable))
		{
			_herobullet.at(i)->removeFromParent();
			_herobullet.erase(_herobullet.begin() + i);
			i--;
		}

	}
	updatePlants(duration);
	for (int i = 0; i < _plantsVector.size(); i++)
	{
		Plants* _plant = _plantsVector.at(i);
		_plant->getHPBar()->setPosition(Vec2(_plant->getPosition().x, _plant->getPosition().y + 40));
	}
	m_hero->setPosition(m_position);
	generateBag(m_position);
	setViewpointCenter(m_hero->getPosition());
	if (m_hero->m_HP <= 0)
	{
		m_hero->setVisible(false);
		m_hero->m_HP = 100;
		auto s = Sprite::create("die/0.png");
		s->setPosition(m_hero->getPosition());
		this->addChild(s, 1);
		auto animation = Animation::create();
		for (int i = 3; i < 20; i++)
		{
			animation->addSpriteFrameWithFile(StringUtils::format("die/%d.png", i));
		}
		animation->setDelayPerUnit(2.0f / 20.0f);
		auto animate = Animate::create(animation);
		s->runAction(animate);
		CCDirector::sharedDirector()->replaceScene(GameOverScene::createScene());
	}

	//trap
	if (isCollision(tiledCoordForPosition(m_position), trap) && !(m_hero->isSpeedChange()))
	{
		trap->setVisible(true);
		m_speed = m_speed - 200;
		m_hero->changespeed(m_speed);
		count_start = count;
	}
	count++;

	if (count - count_start > 50)
		m_hero->changespeed(300);

	

}

bool  GameScene::isCollision(Vec2 tileposition, TMXLayer* propsLayer)
{
	if (propsLayer->getTileGIDAt(tileposition))return true;
	else return false;

}

void  GameScene::collectWeapon(Vec2 tileposition, TMXLayer* layer, int type)
{
	if (num_weapon <= 8)
	{
		num_weapon++;
		weaponList[num_weapon - 1] = new Weapon(type);
		layer->setTileGID(0, tileposition);
	}
	else return;

}

void  GameScene::generateBag(Vec2 position)
{
	for (int i = 0; i < num_weapon; i++)
	{
		string path = weaponList[i]->path;
		weapons[i]->setTexture(path);
		weapons[i]->setPosition(Vec2(position.x - 110 + (i % 4) * 70, position.y + 35 - (i / 4) * 50));
	}
}
void  GameScene::displayBag() {
	for (int i = 0; i < 8; i++)
	{
		weapons[i]->setVisible(true);
	}
}

void  GameScene::undisplayBag() {
	for (int i = 0; i < 8; i++)
	{
		weapons[i]->setVisible(false);
	}
}

void GameScene::popWeapons() {
	equip(1);
	num_weapon--;
	CCLOG("num_weapon:%d", num_weapon);

	//和最后一个武器交换

	weaponList[0] = weaponList[num_weapon];
	weaponList[num_weapon] = nullptr;
	weapons[num_weapon]->setTexture(NULL);
	weapons[num_weapon]->setTextureRect(CCRect());

}

void  GameScene::equip(int number)
{
	if (number <= num_weapon)
	{
		//更换背包里的图标
		weapons[number - 1]->setTexture(weaponNow->path);

		//真正的武器交换
		Weapon* temp = weaponList[number - 1];
		weaponList[number - 1] = weaponNow;
		weaponNow = temp;

		//更换服装更新伤害值
		m_hero->changeWeapon(weaponNow->type);
		m_hero->m_damage = weaponNow->damage;
		m_hero->setTexture(m_hero->folder + "/0.png");
	}
}
bool GameScene::hittarget(Sprite * bullet)
{
	bool a = 0;
	for (int i = 0; i < _plantsVector.size(); i++)
	{
		if (i < 0 || i >= _plantsVector.size())
		{
			i++;
		}
		if (bullet->getBoundingBox().intersectsRect(_plantsVector.at(i)->getBoundingBox()))
		{

			_plantsVector.at(i)->getHPBar()->setPercent(_plantsVector.at(i)->getHPBar()->getPercent() - m_hero->m_damage / _plantsVector.at(i)->getHealth() * 100);
			a = 1;
			if (_plantsVector.at(i)->getHPBar()->getPercent() <= 0)
			{
;				_plantsVector.at(i)->removeFromParent();
				_plantsVector.erase(i);
				i--;
				if (_plantsVector.size() == 0)
				{
					isPass = true;
				}
			}
		}
	}
	return a;
}

void GameScene::startPlants(float health, float Aspd, float Adistance, float damage, float speed, Vec2 guardBegin, Vec2 guardEnd, int i, int frame)
{
	_isPlantsStart = true;
	Plants* _plant = Plants::create("shoot.png");
	_plant->setPosition(guardEnd);
	_plant->setHealth(health);
	_plant->setAspd(Aspd);
	_plant->setAdistance(Adistance);
	_plant->setDemage(damage);
	_plant->setSpeed(speed);
	_plant->setGuardBegin(guardBegin);
	_plant->setGuardEnd(guardEnd);
	_plant->setType(i);
	_plant->setFrame(frame);

	auto loadingBar = LoadingBar::create("LoadingBar.png");
	loadingBar->setScale(1);
	loadingBar->setDirection(LoadingBar::Direction::LEFT);
	loadingBar->setPercent(100);
	_plant->setHPBar(loadingBar);
	this->addChild(_plant->getHPBar(), 100);
	loadingBar->setPosition(_plant->getPosition());

	_plant->setHPInterval(1);
	_plantsVector.pushBack(_plant);
	this->addChild(_plant, 4);
	auto action = Sequence::create(CallFunc::create([=] {
		_isShoot.push_back(0);
		guardPlants(_isShoot.size() - 1);
	}), NULL);
	_plant->runAction(action);
}

int minimum(int a, int b, int c)
{
	int m = a;
	if (m > b) m = b;
	if (m > c) m = c;
	return m;
}

void GameScene::updatePlants(float delta)
{
	if (!_isPlantsStart)
	{
		auto objects = GAME1->getObjectGroup("Objects");
		for (int i = 1; i <= 30; i++)
		{
			string beginS = "enemy" + to_string(i) + "begin";
			string endS = "enemy" + to_string(i) + "end";
			ValueMap begin = objects->getObject(beginS);
			ValueMap end = objects->getObject(endS);
			if (begin.size() == 0)break;
			Vec2 BeginVec = tiledCoordForPosition(Vec2(begin["x"].asInt(), begin["y"].asInt()));
			if (isCollision(BeginVec, GAME1->getLayer("enemy_class_1")))
			{
				startPlants(50.0, 0.3, 200, 1, 100, Vec2(begin["x"].asInt(), begin["y"].asInt()), Vec2(end["x"].asInt(), end["y"].asInt()), 1, 15);
			}
			else if (isCollision(BeginVec, GAME1->getLayer("enemy_class_2")))
			{
				startPlants(100.0, 1, 200, 2, 100, Vec2(begin["x"].asInt(), begin["y"].asInt()), Vec2(end["x"].asInt(), end["y"].asInt()), 2, 11);
			}
			else if (isCollision(BeginVec, GAME1->getLayer("enemy_class_3")))
			{
				startPlants(500.0, 1, 200, 3, 100, Vec2(begin["x"].asInt(), begin["y"].asInt()), Vec2(end["x"].asInt(), end["y"].asInt()), 3, 9);
			}
		}
		_isPlantsStart = 1;
	}
	for (int i = 0; i < minimum(_isShoot.size(), _bulletVector.size(),_plantsVector.size()); i++)
	{
		if (_isShoot.at(i))
		{
			for (int j = 0; j < _bulletVector.at(i).size(); j++)
			{
				auto bullet = _bulletVector[i][j];
				Vec2 a = tiledCoordForPosition(bullet->getPosition());
				if (m_hero->getBoundingBox().intersectsRect(bullet->getBoundingBox()))
				{
					if (i < 0 || i >= _plantsVector.size())
					{
						i++;
					}
					m_hero->hit(_plantsVector.at(i)->getDemage());
					removeBullet(i, j);
					--j;
				}
				else if (bullet->getPosition().x > GAME1->getMapSize().width * GAME1->getTileSize().width || bullet->getPosition().x < 0 || bullet->getPosition().y > GAME1->getMapSize().height * GAME1->getTileSize().height || bullet->getPosition().y < 0)
				{
					removeBullet(i, j);
					--j;
				}
				else
				{
					if (a.x<0 || a.x>mapWidth || a.y<0 || a.y>mapHeight)
					{
						return;
					}
					if (isCollision(a, collidable))
					{
						removeBullet(i, j);
						--j;
					}
				}
			}
		}
	}
}

void GameScene::guardPlants(int i)
{
	if (i < 0 || i >= _plantsVector.size())
	{
		i++;
	}
	Plants* _plant = _plantsVector.at(i);

	_plant->stopAllActions();
	double dist = _plant->getGuardBegin().distance(_plant->getGuardEnd());
	auto moveLeft = MoveTo::create(dist / _plant->getSpeed(), _plant->getGuardBegin());
	auto moveRight = MoveTo::create(dist / _plant->getSpeed(), _plant->getGuardEnd());
	auto sequence = Sequence::create(moveLeft, moveRight, NULL);
	auto action = RepeatForever::create(sequence);
	_plant->runAction(action);
	int a = _plant->getType();
	auto animation = Animation::create();
	for (int j = 0; j < _plant->getFrame(); j++)
	{
		string s = "plants/" + to_string(a) + "/" + to_string(j) + ".png";
		animation->addSpriteFrameWithFile(s);
	}
	animation->setDelayPerUnit(1.0f / (double)_plant->getFrame());
	auto animate = Animate::create(animation);
	RepeatForever * p = RepeatForever::create(animate);
	_plant->runAction(p);
}



void GameScene::shootPlants(float delta)
{
	for (int i = 0; i < _plantsVector.size(); i++)
	{
		if (i < 0 || i >= _plantsVector.size())
		{
			i++;
		}
		Plants* plant = _plantsVector.at(i);
		if (_isShoot.size() < i + 1)
		{
			continue;
		}
		else if (!_isShoot.at(i))
		{
			if (m_hero->getPosition().distance(plant->getPosition()) <= plant->getAdistance())
			{
				_isShoot.at(i) = 1;
			}
		}
		else if (m_hero->getPosition().distance(plant->getPosition()) > plant->getAdistance())
		{
			_isShoot.at(i) = 0;
			plant->stopAllActions();
			auto animation = Animation::create();
			int a = plant->getType();
			for (int j = 0; j < plant->getFrame(); j++)
			{
				string s = "plants/" + to_string(a) + "/" + to_string(j) + ".png";
				animation->addSpriteFrameWithFile(s);
			}
			animation->setDelayPerUnit(1.0f / (double)plant->getFrame());
			auto animate = Animate::create(animation);
			RepeatForever * p = RepeatForever::create(animate);
			plant->runAction(p);

			AStar * pa = AStar::create();
			Vec2 start = tiledCoordForPosition(plant->getPosition());
			Vec2 end = tiledCoordForPosition(plant->getGuardEnd());
			Vector<PointDelegate*> pathVector = pa->getPath(start, end, gridVector, mapWidth, mapHeight);
			Vector<FiniteTimeAction*> actionVector;

			PointDelegate * pd = pathVector.at(0);
			Vec2 now = plant->getPosition();
			Vec2 next = positionForTileCoord(Vec2(pd->getX(), pd->getY()));
			MoveTo * moveTo = MoveTo::create(next.distance(now) / plant->getSpeed(), next);
			actionVector.pushBack(moveTo);

			for (int j = 1; j < pathVector.size(); j++)
			{
				PointDelegate* pd = pathVector.at(j);
				PointDelegate* pdBefore = pathVector.at(j - 1);
				Vec2 now = positionForTileCoord(Vec2(pdBefore->getX(), pdBefore->getY()));
				Vec2 next = positionForTileCoord(Vec2(pd->getX(), pd->getY()));
				MoveTo * moveTo = MoveTo::create(next.distance(now) / plant->getSpeed(), next);
				actionVector.pushBack(moveTo);
			}
			actionVector.pushBack(CallFunc::create([=] {
				guardPlants(i);
			}));
			plant->runAction(Sequence::create(actionVector));


		}
		else
		{
			newBullet(i);

			plant->stopAllActions();
			auto animation = Animation::create();
			int a = plant->getType();
			for (int j = 0; j < plant->getFrame(); j++)
			{
				string s = "plants/" + to_string(a) + "/" + to_string(j) + ".png";
				animation->addSpriteFrameWithFile(s);
			}
			animation->setDelayPerUnit(1.0f / (double)plant->getFrame());
			auto animate = Animate::create(animation);
			RepeatForever * p = RepeatForever::create(animate);
			plant->runAction(p);

			AStar * pa = AStar::create();
			Vec2 start = tiledCoordForPosition(plant->getPosition());
			Vec2 end = tiledCoordForPosition(m_hero->getPosition());
			Vector<PointDelegate*> pathVector = pa->getPath(start, end, gridVector, mapWidth, mapHeight);
			PointDelegate * pd = pathVector.at(0);
			Vec2 now = plant->getPosition();
			Vec2 next = positionForTileCoord(Vec2(pd->getX(), pd->getY()));
			//double length = now.distance(next);
			//next = now + (next - now) / length * delta * plant->getSpeed();
			//if (isCollision(tiledCoordForPosition(next), collidable))next = now;
			MoveTo * moveTo = MoveTo::create(next.distance(now) / plant->getSpeed(), next);
			plant->runAction(moveTo);

		}
	}
}

void GameScene::removeBullet(int i, int j)
{
	auto bullet = _bulletVector[i][j];
	_bulletVector[i].erase(_bulletVector[i].begin() + j);
	bullet->removeFromParent();
}
void GameScene::newBullet(int i)
{
	if (i < 0 || i >= _plantsVector.size())
	{
		i++;
	}
	Plants* plant = _plantsVector.at(i);
	Sprite* bullet = Sprite::create("plants/" + to_string(plant->getType()) + "/attack.png");
	bullet->setPosition(plant->getPosition());
	this->addChild(bullet);
	MoveBy* moveBy = MoveBy::create(m_hero->getPosition().distance(plant->getPosition()) / 0.3, 1000 * (m_hero->getPosition() - plant->getPosition()));
	bullet->runAction(moveBy);
	while (_bulletVector.size() < i + 1)_bulletVector.push_back({});
	_bulletVector[i].push_back(bullet);
}