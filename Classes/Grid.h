#pragma once
#include "cocos2d.h"

class Grid :public cocos2d::Ref
{
public:
	//��̬create����
	static Grid* create(int x, int y);
	bool initWithPoint(int x, int y);
	void setX(int x);
	void setY(int y);
	int getX();
	int getY();
	void setPass(bool pass);
	bool isPass();
private:
	int m_x;//�ڵ�ͼ��ά�����е�x����
	int m_y;//�ڵ�ͼ��ά�����е�y����
	bool m_pass;//�Ƿ��ͨ��
	
};