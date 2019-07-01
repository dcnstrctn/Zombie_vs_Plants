#pragma once
#include "cocos2d.h"
#include "Grid.h"
#include "PointDelegate.h"
#include <vector>
using namespace std;
using namespace cocos2d;

/*enum 
{
	mapWidth = 40,
	mapHeight = 20
};*/

class AStar :public cocos2d::Ref {
private:
	Vector<PointDelegate*>m_closeList;//��¼�Ѿ����ĵ�
	Vector<PointDelegate*>m_openList;//��¼��Ч��
public:
	static AStar* create();
	//Ѱ·���������ش�startPoint��endPoint֮������·��
	Vector<PointDelegate*>getPath(Vec2 startPoint, Vec2 endPoint, std::vector<Vector<Grid*>>gridArray,int mapWidth,int mapHeight);
	//������Ч·���������ݹ飩������������Ч·������bool
	bool findValidGrid(Vec2 startPoint, Vec2 endPoint, std::vector<Vector<Grid*>>gridArray, int mapWidth, int mapHeight);
	//���Point��Ч��
	bool isCheck(Vec2 point, std::vector<Vector<Grid*>>gridArray, int mapWidth, int mapHeight);
};