#include "Grid.h"
using namespace cocos2d;

 Grid* Grid::create(int x, int y)
{
	Grid* g = new Grid();
	if (g && g->initWithPoint(x, y))
	{
		g->autorelease();
		return g;
	}
	CC_SAFE_DELETE(g);
	return nullptr;
}
bool Grid::initWithPoint(int x, int y)
{
	m_x = x;
	m_y = y;
	m_pass = true;
	return true;
}
void Grid::setX(int x)
{
	m_x = x;
}
void Grid::setY(int y)
{
	m_y = y;
}
int Grid::getX()
{
	return m_x;
}
int Grid::getY()
{
	return m_y;
}
void Grid::setPass(bool pass)
{
	m_pass = pass;
}
bool Grid::isPass()
{
	return m_pass;
}