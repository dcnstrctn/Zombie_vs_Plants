#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Weapon.h"
#include "Hero.h"
#include "Plants.h"
#include"AStar.h"

USING_NS_CC;

class GameScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void onKeyPressed(EventKeyboard::KeyCode, Event*);
	void onKeyReleased(EventKeyboard::KeyCode, Event*);
	//把玩家作为视觉中心来显示，让地图随玩家移动
	void setViewpointCenter(Vec2 position);

	Vec2 positionForTileCoord(const Vec2 pos);

	//回调更新函数，该函数每帧都会调用
	void update(float duration);

	//void changeScene(int sceneId)

	//将屏幕OpenGL坐标转换为TiledMap坐标
	Vec2 tiledCoordForPosition(Vec2 position);

	//地图与hero碰撞判断
	bool isCollision(Vec2, TMXLayer*);

	//捡拾道具触发函数
	void collectWeapon(Vec2, TMXLayer*, int);

	//关于背包显示
	void generateBag(Vec2);
	void displayBag();
	void undisplayBag();
	void popWeapons();

	//选择并装备武器
	void equip(int);

	//zombies
	void heroattack();
	void heroattackfar();
	bool hittarget(Sprite*);

	//plants
	void startPlants(float health, float Aspd, float Adistance, float demage, float speed, Vec2 guardBegin, Vec2 guardEnd, int i, int frame);
	void updatePlants(float delta);
	void guardPlants(int i);

	void removePlants(float delta);
	void shootPlants(float delta);
	void removeBullet(int i, int j);
	void newBullet(int i);

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

	static Weapon* weaponList[8];
	static int num_weapon;
	static CCSprite* weapons[8];//to display
	static Weapon* weaponNow;
	static int HP;
private:
	TMXTiledMap*GAME1;
	Hero* m_hero;
	Sprite* bag;
	Sprite* bagpack;
	int m_score;
	int screenWidth, screenHeight;
	int mapHeight, mapWidth, tileWidth, tileHeight;
	TMXLayer* collidable;//障碍物
	TMXLayer* trap;//陷阱
	TMXLayer* collectable;//物品
	TMXLayer* medicineLayer;//真正的物品层
	TMXLayer* weapon1Layer;//第一个装备层
	TMXLayer* weapon2Layer; //第二个装备层
	int count;//游戏帧计数器
	int count_start;
	Vector<Plants*> _plantsVector;
	std::vector<std::vector<Sprite*>> _bulletVector;
	std::vector<bool>_isShoot;
	std::vector<Sprite*> _herobullet;
	LoadingBar* lifebar;
	Sprite* lifebar_bg;
	bool _isPlantsStart = 0;
	RepeatForever* r;
	std::vector<Vector<Grid*>>gridVector;
	bool isPass = false;
	Label* bulletnum;
	Label* levelLabel;
	Label* monsterLabel;
	ParticleSystem* ps;//出口动画
};
#endif 