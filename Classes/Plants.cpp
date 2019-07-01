#include "Plants.h"
#include"HelloWorldScene.h"
#include"GameScene.h"

Plants::Plants()
{
}


Plants::~Plants()
{
}

Plants* Plants::create(const std::string& filename)
{
	Plants* sprite = new (std::nothrow) Plants();
	if (sprite && sprite->initWithFile(filename))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}


void Plants::setHealth(float health)
{
	_health = health;
}

float Plants::getHealth()
{
	return _health;
}

void Plants::setAspd(float Aspd)
{
	_Aspd = Aspd;
}

float Plants::getAspd()
{
	return _Aspd;
}

void Plants::setAdistance(float Adistance)
{
	_adistance = Adistance;
}

float Plants::getAdistance()
{
	return _adistance;
}

void Plants::setDemage(float d)
{
	_demage = d;
}

float Plants::getDemage()
{
	return _demage;
}

void Plants::setSpeed(float s)
{
	_speed = s;
}

float Plants::getSpeed()
{
	return _speed;
}

void Plants::setHPBar(LoadingBar* HPBar)
{
	_HPBar = HPBar;
}

LoadingBar* Plants::getHPBar()
{
	return _HPBar;
}

void Plants::setHPInterval(float HPInterval)
{
	_HPInterval = HPInterval;
}

float Plants::getHPInterval()
{
	return _HPInterval;
}

void Plants::setGuardBegin(Vec2 guardBegin)
{
	_guardBegin = guardBegin;
}

Vec2 Plants::getGuardBegin()
{
	return _guardBegin;
}

void Plants::setGuardEnd(Vec2 guardEnd)
{
	_guardEnd = guardEnd;
}

Vec2 Plants::getGuardEnd()
{
	return _guardEnd;
}

void Plants::setType(int type)
{
	_type = type;
}

int Plants::getType()
{
	return _type;
}

void Plants::setFrame(int frame)
{
	_frame = frame;
}

int Plants::getFrame()
{
	return _frame;
}
