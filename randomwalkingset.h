#pragma once
#include <vector>
#include "Vertex.h"
#include "Graph.h"

using namespace std;
class randomwalkingset
{
private:
	int nodenum;
	vector <Vertex*> nodeset;
	int avgtimes;
	
public:
	randomwalkingset();
	~randomwalkingset();
	void addnode(Vertex*);
	void setnodenum(int);
	int getnodenum();
	vector <Vertex*> getnodeset();
	vector <Vertex*> generateSeed();
	int getMaxDegree();
	vector<pair<int,int> > randomwalking(Graph);
};

