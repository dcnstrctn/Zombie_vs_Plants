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
	Vector<PointDelegate*>m_closeList;//记录已经过的点
	Vector<PointDelegate*>m_openList;//记录有效点
public:
	static AStar* create();
	//寻路函数，返回从startPoint到endPoint之间的最佳路径
	Vector<PointDelegate*>getPath(Vec2 startPoint, Vec2 endPoint, std::vector<Vector<Grid*>>gridArray,int mapWidth,int mapHeight);
	//查找有效路径函数（递归），根据有无有效路径返回bool
	bool findValidGrid(Vec2 startPoint, Vec2 endPoint, std::vector<Vector<Grid*>>gridArray, int mapWidth, int mapHeight);
	//检查Point有效性
	bool isCheck(Vec2 point, std::vector<Vector<Grid*>>gridArray, int mapWidth, int mapHeight);
};