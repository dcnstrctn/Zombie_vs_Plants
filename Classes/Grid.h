#pragma once
#include "cocos2d.h"

class Grid :public cocos2d::Ref
{
public:
	//静态create函数
	static Grid* create(int x, int y);
	bool initWithPoint(int x, int y);
	void setX(int x);
	void setY(int y);
	int getX();
	int getY();
	void setPass(bool pass);
	bool isPass();
private:
	int m_x;//在地图二维数组中的x坐标
	int m_y;//在地图二维数组中的y坐标
	bool m_pass;//是否可通过
	
};