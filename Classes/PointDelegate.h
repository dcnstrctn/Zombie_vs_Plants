#pragma once
#include "cocos2d.h"
class PointDelegate :public cocos2d::Ref 
{
private:
	float m_Fx;
	float m_Fy;
public:
	static PointDelegate* create(float x, float y);
	bool initPoint(float x, float y);
	void setX(float x);
	void setY(float y);
	float getX();
	float getY();
};