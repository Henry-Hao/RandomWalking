#pragma once
#include "Vertex.h"
#include <map>
#include <vector>

using namespace std;

class Graph {
private:
	map <int,Vertex*> vertex;
	int seedNum;

public:
	Graph() {};
	int nodenum;
	int edgenum;
	Graph(string filename);
	void build(string filename);
	bool isEdge(int v1, int v2);
	bool isVertex(int index);
	map <int, Vertex*> Graph::getAllVertex();
	Vertex* getVertex(int);
	void addVertex(Vertex* v);

	
};