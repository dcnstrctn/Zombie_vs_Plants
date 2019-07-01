#include "AStar.h"
#include<cmath>
using namespace std;
using namespace cocos2d;

bool AStar::isCheck(Vec2 point, std::vector<Vector<Grid*>>gridArray, int mapWidth, int mapHeight)
{
	//x��y<0ʱ��false
	if (point.x < 0 || point.y < 0){return false;}
	//x��y������ͼ��Ⱥ͸߶�ʱ��false
	if (point.x >= mapWidth || point.y >= mapHeight) { return false; }
	//�����openList��¼���ĵ㣬false
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
	//�Ӷ�λ�����л�ȡ��ǰ��������ĵ�ͼ�����ж��Ƿ��ͨ���������ϰ��
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

	//ʹ����ʱVector���ϴ洢��Ҫ�жϵ�8���㣬�Ƿ�����Ч�����Ŀ�ĵ�
	Vector<PointDelegate*>points;
	points.pushBack(PointDelegate::create(startPoint.x, startPoint.y + 1));//��
	points.pushBack(PointDelegate::create(startPoint.x, startPoint.y - 1));//��
	points.pushBack(PointDelegate::create(startPoint.x-1, startPoint.y));//��
	points.pushBack(PointDelegate::create(startPoint.x+1, startPoint.y));//��
	//ʹ����ʱVector���ϴ洢4�����е���Ч��
	Vector<PointDelegate*>temp;
	for (int i = 0;i < points.size();i++)
	{
		PointDelegate*pd = points.at(i);
		//�жϵ�ǰ���ǲ���endPoint
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
	//����ʱ�����յ���Ч�㰴�����·������
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
	//�ݹ��ҳ�������Ч��ֱ���������յ�
	for (int i = 0;i < temp.size();i++)
	{
		PointDelegate* pd = temp.at(i);
		Vec2 p = Vec2(pd->getX(), pd->getY());
		//�ݹ����findValidGrid
		bool flag = findValidGrid(p, endPoint, gridArray, mapWidth,mapHeight);
		if (flag) 
		{
			//�Ѿ����������Ч�㴢����openlist����
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
	//����findValidGrid���·�߲���
	findValidGrid(startPoint, endPoint, gridArray, mapWidth, mapHeight);
	m_openList.reverse();
	return m_openList;
}