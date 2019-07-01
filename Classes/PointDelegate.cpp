#include "PointDelegate.h"
using namespace cocos2d;

PointDelegate* PointDelegate::create(float x, float y)
{
	PointDelegate* p = new PointDelegate();
	if (p && p->initPoint(x, y))
	{
		p->autorelease();
		return p;
	}
	CC_SAFE_DELETE(p);
	return nullptr;
 }


bool PointDelegate::initPoint(float x, float y)
{
	m_Fx = x;
	m_Fy = y;
	return true;
}
void PointDelegate::setX(float x)
{
	m_Fx = x;
}
void PointDelegate::setY(float y)
{
	m_Fy = y;
}
float PointDelegate::getX()
{
	return m_Fx;
}
float PointDelegate::getY()
{
	return m_Fy;
}