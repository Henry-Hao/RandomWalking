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
	//���캯��
	Vertex(int v);
	void init(int v);
	//���һ���ھӽ��
	void addNeighbour(int);
	bool isNeighbour(int);
	int getclusterid();
	void setclusterid(int);
	map<int, int> getNeighbour();
	//���value
	int getValue();
	double getDegree();
	void setDegree();
};