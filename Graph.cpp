#include "Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <set>
#include <algorithm>
#include <iterator>

Graph::Graph(string filename) {
	Graph::build(filename);
}

void Graph::build(string filename) {
	string line;
	ifstream graphfile(filename.c_str());
	int v1, v2;
	if (graphfile.is_open()) {
		int i = 0;
		while (getline(graphfile, line)) {
			Vertex *vv1, *vv2;
			vv1 = new Vertex();
			vv2 = new Vertex();
			string from, to;
			istringstream lines(line);
			getline(lines, from, ' ');
			getline(lines, to, ' ');
			//保证没有自己到自己的边
			if (from == to) continue;
			v1 = atoi(from.c_str());
			v2 = atoi(to.c_str());
			//这条边已经出现过
			if (isEdge(v1, v2))
				continue;
			if (Graph::isVertex(v1))
				vv1 = Graph::getVertex(v1);
			else {
				(*vv1).init(v1);
				Graph::addVertex(vv1);
			}
			if (Graph::isVertex(v2))
				vv2 = Graph::getVertex(v2);
			else {
				(*vv2).init(v2);
				Graph::addVertex(vv2);
			}			
			(*vv1).addNeighbour(v2);
			(*vv2).addNeighbour(v1);
			i++;
		}
		graphfile.close();
	}
	else
		cout << "Unable to open file " << filename;
}


map <int,Vertex*> Graph::getAllVertex() {
	return Graph::vertex;
}

bool Graph::isVertex(int index){
	if (Graph::vertex.find(index) != Graph::vertex.end())
		return true;
	else
		return false;
}

bool Graph::isEdge(int v1, int v2) {
	Vertex* x;
	if (Graph::isVertex(v1)) {
		x = Graph::getVertex(v1);
		if ((*x).isNeighbour(v2))
			return true;
		else
			return false;
	}	
	else if (Graph::isVertex(v2)) {
		x = Graph::getVertex(v2);
		if ((*x).isNeighbour(v1))
			return true;
		else
			return false;
	}
	else
		return false;

}

Vertex* Graph::getVertex(int index) {
	return Graph::vertex.find(index)->second;
}

void Graph::addVertex(Vertex* v) {
	Graph::vertex[(*v).getValue()] = v;
}
