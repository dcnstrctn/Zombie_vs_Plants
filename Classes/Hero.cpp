#include "Hero.h"
using namespace cocos2d;

Hero::Hero()
{
	m_HP = 100;
	m_damage = 10;
	m_speed = 300;
	m_afrequency = 1.0f;
	attackdistance = 1;
	m_ismoving = 0;
}
Hero::~Hero()
{

}

bool Hero::init()
{
	return true;
}

void Hero::changespeed(double s)
{
	m_speed = s;
	m_isSpeedChange = !(m_isSpeedChange);
}

int Hero::getspeed()
{
	return m_speed;
}

bool Hero::isSpeedChange()
{
	return m_isSpeedChange;
}

void Hero::changedirection(Vec2 direction)
{
	m_direction = direction;
}

Vec2 Hero::getdirection()
{
	return m_direction;
}

void Hero::hit(int damage)
{
	m_HP -= damage;
}

bool Hero::die()
{
	if (m_HP < 0)
	{
		auto blink = Blink::create(2, 3);
		Hero::~Hero();
		return true;
	}
	else return false;
}
void Hero::changeWeapon(int type)
{
	switch (type)
	{
	case 0:
		folder = "zombie";
		numFrame = 21;
		break;
	case 1:
		folder = "zombie_door";
		numFrame = 22;
		break;
	case 2:
		folder = "zombie_football";
		numFrame = 10;
	}
	this->setTexture(folder + "/0.png");
}

void Hero::addToBlood()
{
	this->m_HP += 50;
	if (m_HP > 100)
		m_HP = 100;
}