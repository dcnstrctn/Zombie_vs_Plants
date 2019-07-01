#include "cocos2d.h"
#include<string>
using namespace cocos2d;
class Player :public CCSprite
{
public:
	Player()
	{
		speed = 0.8f;
		health = 100;
		damage = 10;
		afrequency = 2.0f;
		ismoving = false;
	}
	~Player()
	{

	}
	virtual bool init()
	{
		return true;
	}
	CCSprite* getsprite()
	{
		return m_sprite;
	}
	void bindsprite(CCSprite* sprite)
	{
		this->m_sprite = sprite;
		this->addChild(m_sprite);
	}
	void changespeed(double s)
	{
		speed = s;
	}
	void changedirection(std::string s)
	{
		direction = s;
	}
	void move()
	{
		if (ismoving)
			return;
		else
		{
			ismoving = true;
			if (direction == "up")
			{
				CCAction*action = MoveBy::create(speed, Vec2(0, 10));
				runAction(action);
			}
			if (direction == "down")
			{
				CCAction*action = MoveBy::create(speed, Vec2(0, -10));
				runAction(action);
			}
			if (direction == "left")
			{
				CCAction*action = MoveBy::create(speed, Vec2(-10, 0));
				runAction(action);
			}
			if (direction == "right")
			{
				CCAction*action = MoveBy::create(speed, Vec2(10, 0));
				runAction(action);
			}
			ismoving = false;
		}
	}
	void hit()
	{
	}
	void attack()
	{

	}
	CREATE_FUNC(Player);
private:
	CCSprite* m_sprite;
	int health;
	double damage;
	double speed;
	double afrequency;
	std::string direction;
	bool ismoving;
};