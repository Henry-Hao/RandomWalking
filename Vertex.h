#pragma once
#include <map>

using namespace std;

class Vertex {
private:
	int value;
	map <int,int> neighbour;
	int clusterid;
	double degree;

public:
	Vertex() {};
	//构造函数
	Vertex(int v);
	void init(int v);
	//添加一个邻居结点
	void addNeighbour(int);
	bool isNeighbour(int);
	int getclusterid();
	void setclusterid(int);
	map<int, int> getNeighbour();
	//获得value
	int getValue();
	double getDegree();
	void setDegree();
};