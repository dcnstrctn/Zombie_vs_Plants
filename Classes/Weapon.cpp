#include "Weapon.h"
using namespace cocos2d;

Weapon::Weapon(int label) {
	//switch
	if (label == 1) {
		type = 1;
		bullet = 50;
		damage = 20;
		path = "res/door.png";
	}
	else if (label == 2) {
		type = 2;
		bullet = 50;
		damage = 30;
		path = "res/helmet.png";
	}
	else if (label == 0)
	{
		type = 0;
		bullet = 100000;
		damage = 10;
		path = "res/chanzi.png";
	}
}

Weapon::~Weapon() {
}


