#include "Vertex.h"

Vertex::Vertex(int v){
	this->value = v;
}
void Vertex::init(int v) {
	this->value = v;
}

void Vertex::addNeighbour(int v){
	this->neighbour[v] = 0;
}
bool Vertex::isNeighbour(int index){
	if(this->neighbour.find(index)!=this->neighbour.end())
		return true;
	else return false;
}

int Vertex::getValue(){
	return this->value;
}

double Vertex::getDegree(){
	return this->degree;
}
void Vertex::setDegree(){
	int size = this->neighbour.size();
	this->degree = 1.0/(size+1);
}

int Vertex::getclusterid() {
	return this->clusterid;
}
void Vertex::setclusterid(int arg1) {
	this->clusterid = arg1;
}

map<int, int> Vertex::getNeighbour() {
	return this->neighbour;
}

