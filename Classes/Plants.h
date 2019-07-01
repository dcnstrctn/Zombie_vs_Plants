#pragma once
#include"cocos2d.h"
#include"ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;
class Plants :public Sprite
{
public:
	Plants();
	~Plants();

	static Plants* create(const std::string& filename);

	void setHealth(float health);
	float getHealth();

	void setAspd(float Aspd);
	float getAspd();

	void setAdistance(float Adistance);
	float getAdistance();

	void setDemage(float demage);
	float getDemage();

	void setSpeed(float speed);
	float getSpeed();

	void setHPBar(LoadingBar* _HPBar);
	LoadingBar* getHPBar();

	void setHPInterval(float HPInterval);
	float getHPInterval();

	void setGuardBegin(Vec2 guardBegin);
	Vec2 getGuardBegin();

	void setGuardEnd(Vec2 guardEnd);
	Vec2 getGuardEnd();

	void setType(int type);
	int getType();

	void setFrame(int frame);
	int getFrame();

	CREATE_FUNC(Plants);
private:
	float _health;
	float _Aspd;
	float _adistance;
	float _demage;
	float _speed;
	LoadingBar* _HPBar;
	float _HPInterval;
	Vec2 _guardBegin;
	Vec2 _guardEnd;
	int _type;
	int _frame;
};

