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
	//�������Ϊ�Ӿ���������ʾ���õ�ͼ������ƶ�
	void setViewpointCenter(Vec2 position);

	Vec2 positionForTileCoord(const Vec2 pos);

	//�ص����º������ú���ÿ֡�������
	void update(float duration);

	//void changeScene(int sceneId)

	//����ĻOpenGL����ת��ΪTiledMap����
	Vec2 tiledCoordForPosition(Vec2 position);

	//��ͼ��hero��ײ�ж�
	bool isCollision(Vec2, TMXLayer*);

	//��ʰ���ߴ�������
	void collectWeapon(Vec2, TMXLayer*, int);

	//���ڱ�����ʾ
	void generateBag(Vec2);
	void displayBag();
	void undisplayBag();
	void popWeapons();

	//ѡ��װ������
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
	TMXLayer* collidable;//�ϰ���
	TMXLayer* trap;//����
	TMXLayer* collectable;//��Ʒ
	TMXLayer* medicineLayer;//��������Ʒ��
	TMXLayer* weapon1Layer;//��һ��װ����
	TMXLayer* weapon2Layer; //�ڶ���װ����
	int count;//��Ϸ֡������
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
	ParticleSystem* ps;//���ڶ���
};
#endif 