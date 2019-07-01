#include "AStar.h"
#include<cmath>
using namespace std;
using namespace cocos2d;

bool AStar::isCheck(Vec2 point, std::vector<Vector<Grid*>>gridArray, int mapWidth, int mapHeight)
{
	//x和y<0时，false
	if (point.x < 0 || point.y < 0){return false;}
	//x和y超过地图宽度和高度时，false
	if (point.x >= mapWidth || point.y >= mapHeight) { return false; }
	//如果是openList记录过的点，false
	PointDelegate* g = PointDelegate::create(point.x, point.y);
	for (int i = 0;i < m_closeList.size();i++)
	{
		PointDelegate* pp = m_closeList.at(i);
		Vec2 t = Vec2(pp->getX(), pp->getY());
		if (point.equals(t))
		{
			return false;
		}
	}
	//从二位数组中获取当前点所代表的地图网格，判断是否可通过（有无障碍物）
	Vector<Grid*> tempX = gridArray.at((int)g->getX());
	Grid* grid = tempX.at((int)g->getY());
	if (point.x >= 0 && point.y >= 0 && grid->isPass())
	{
		return true;
	}
	return false;
}

bool AStar::findValidGrid(Vec2 startPoint, Vec2 endPoint, std::vector<Vector<Grid*>>gridArray, int mapWidth, int mapHeight)
{
	PointDelegate* startPointDelegate = PointDelegate::create(startPoint.x, startPoint.y);
	m_closeList.pushBack(startPointDelegate);

	//使用临时Vector集合存储需要判断的8个点，是否是有效点或者目的点
	Vector<PointDelegate*>points;
	points.pushBack(PointDelegate::create(startPoint.x, startPoint.y + 1));//上
	points.pushBack(PointDelegate::create(startPoint.x, startPoint.y - 1));//下
	points.pushBack(PointDelegate::create(startPoint.x-1, startPoint.y));//左
	points.pushBack(PointDelegate::create(startPoint.x+1, startPoint.y));//右
	//使用临时Vector集合存储4个点中的有效点
	Vector<PointDelegate*>temp;
	for (int i = 0;i < points.size();i++)
	{
		PointDelegate*pd = points.at(i);
		//判断当前点是不是endPoint
		Vec2 p = Vec2(pd->getX(), pd->getY());
		if (p.equals(endPoint))
		{
			m_openList.pushBack(pd);
			return 1;
		}
		if (isCheck(p, gridArray, mapWidth,mapHeight))
		{
			temp.pushBack(pd);
		}
	}
	//对临时集合终点有效点按照最短路径排序
	std::sort(temp.begin(), temp.end(), [=](const Ref* obj1, const Ref* obj2)
	{
		PointDelegate* p1 = (PointDelegate*)obj1;
		PointDelegate* p2 = (PointDelegate*)obj2;
		double x1 = abs(p1->getX() - endPoint.x);
		double y1 = abs(p1->getY() - endPoint.y);
		double x2 = abs(p2->getX() - endPoint.x);
		double y2 = abs(p2->getY() - endPoint.y);
		double r1 = hypot(x1, y1);
		double r2 = hypot(x2, y2);
		return r1 < r2 ? -1 : 0;

	});
	//递归找出所有有效点直到搜索到终点
	for (int i = 0;i < temp.size();i++)
	{
		PointDelegate* pd = temp.at(i);
		Vec2 p = Vec2(pd->getX(), pd->getY());
		//递归调用findValidGrid
		bool flag = findValidGrid(p, endPoint, gridArray, mapWidth,mapHeight);
		if (flag) 
		{
			//把距离最近的有效点储存在openlist数组
			m_openList.pushBack(pd);
			return true;
		}
	}
	return false;
}

AStar* AStar::create()
{
	AStar* p = new AStar();
	if (p)p->autorelease();
	else CC_SAFE_DELETE(p);
	return p;
}

Vector<PointDelegate*> AStar::getPath(Vec2 startPoint, Vec2 endPoint, std::vector<Vector<Grid*>>gridArray, int mapWidth, int mapHeight)
{
	//调用findValidGrid完成路线查找
	findValidGrid(startPoint, endPoint, gridArray, mapWidth, mapHeight);
	m_openList.reverse();
	return m_openList;
}