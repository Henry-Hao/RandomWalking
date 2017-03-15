#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Graph.h"
#include "Vertex.h"
#include "limit.h"
#include "randomwalkingset.h"
#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include <algorithm>

template<class RandomAccessIterator>
void random_shuffle(
	RandomAccessIterator _First,
	RandomAccessIterator _Last
);

using namespace std;
LARGE_INTEGER start, End, freq;
double timer;
vector<int> seed;
randomwalkingset* rws;


void doit(string inputfile,string outputfile,Graph graph) {
	string line;
	FILE *out;
	fopen_s(&out, outputfile.c_str(), "w");

	ifstream clusteringfile(inputfile.c_str());
	int v1, v2;
	if (clusteringfile.is_open()) {
		int i = 0;
		while (getline(clusteringfile, line)) {
			printf("%d\n", i++);
			vector<pair<int,int> > result;
			rws = new randomwalkingset();
			getline(clusteringfile, line);
			string from;
			string t;
			istringstream lines(line);
			getline(lines, from, ':');
			while (getline(lines, t, ' '))
			{
				Vertex* tmp = graph.getVertex(atoi(t.c_str()));
				(*tmp).setDegree();
				(*tmp).setclusterid(i);
				(*rws).addnode(tmp);
			}
			{
				(*rws).setnodenum((*rws).getnodeset().size());
				if ((*rws).getnodenum() < BOUND)
					fprintf(out, "%d\n", (*rws).getMaxDegree());
				else {
					result = (*rws).randomwalking(graph);
					for (auto it = result.begin(); it != result.end(); it++) {
						fprintf(out, "%d\n", (*it).first);
					}
					
				}
			}
			rws->~randomwalkingset();
			delete rws;
		}
		clusteringfile.close();
	}
}


int main(int argc, char* argv[]) {
	//输入文件 p值 bound值 输出文件  
	string graphfile = argv[1];
	string clusteringfile = argv[2];
	string outputfile = argv[3];

	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);
	printf("processing\n");
	 
	Graph graph(graphfile);
	doit(clusteringfile, outputfile, graph); 


	printf("success\n");


}