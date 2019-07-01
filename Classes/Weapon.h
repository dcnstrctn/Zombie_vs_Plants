#pragma once
#include "cocos2d.h"
using namespace std;
using namespace cocos2d;
class Weapon
{
public:
	Weapon(int);
	~Weapon();

	int getBullet();

public:
	int type;
	string path;
	bool farAttack = true;
	int bullet = 10;
	int damage = 10;
};