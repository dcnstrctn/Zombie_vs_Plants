#include "cocos2d.h"
#include<string>
USING_NS_CC;
class Hero :public Sprite
{
public:
	Hero();
	~Hero();
	virtual bool init();
	Sprite* getsprite();
	void bindsprite(Sprite* sprite);
	void changespeed(double s);
	int getspeed();
	bool isSpeedChange();
	void changedirection(Vec2 direction);
	Vec2 getdirection();
	void hit(int);
	bool die();
	void changeWeapon(int);
	void addToBlood();
	CREATE_FUNC(Hero);
public:
	std::string face="up";
	bool isshoot = 1;
	Sprite* m_sprite;
	bool faceto = 0;
	int m_HP;
	double m_damage;
	double m_speed;
	double m_afrequency;
	double attackdistance;
	Vec2 m_direction;
	bool m_ismoving;
	bool m_isSpeedChange;
	int type = 0;
	std::string folder = "zombie";
	int numFrame = 21;
};