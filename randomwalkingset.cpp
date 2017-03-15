#include "randomwalkingset.h"
#include "limit.h"
#include <algorithm>
#include <time.h>



randomwalkingset::randomwalkingset()
{
	this->avgtimes = 0;
	this->nodenum = 0;
	this->nodeset;
	srand((unsigned)time(NULL));
}


randomwalkingset::~randomwalkingset()
{
	this->nodeset.~vector();
}

void randomwalkingset::addnode(Vertex *x)
{
	this->nodeset.push_back(x);
}

void randomwalkingset::setnodenum(int num) {
	this->nodenum = num;
}
int randomwalkingset::getnodenum()
{
	return this->nodenum;
}
vector<Vertex*> randomwalkingset::getnodeset() {
	return this->nodeset;
}
vector <Vertex*> randomwalkingset::generateSeed() {
	vector <Vertex*> randomset;
	randomset.assign(this->nodeset.begin(), this->nodeset.end());
	random_shuffle(randomset.begin(), randomset.end());
	return randomset;
}

int randomwalkingset::getMaxDegree() {
	vector <Vertex*> nodeset = this->getnodeset();
	double max = (*(*(nodeset.begin()))).getDegree();
	int index = (*(*(nodeset.begin()))).getValue();
	for (auto it = nodeset.begin(); it != nodeset.end(); it++){
		if ((*(*it)).getDegree() < max) {
			index = (*(*it)).getValue();
			max = (*(*it)).getDegree();
		}
	}
	return index;
}

bool mycompare(const pair<int, int> a, const pair<int, int> b) {
	return (a.second > b.second);
}
bool mycompare2(Vertex* arg1, Vertex* arg2) {
	return (*arg1).getValue() < (*arg2).getValue();
}


vector<pair<int,int> > randomwalkingset::randomwalking(Graph graph) {
	int iter_time = ITER_TIME;
	vector<Vertex*> result;
	vector<Vertex*> seedpool;
	map<int, int> tmpresult;
	//实验多次取平均
	while (iter_time-- >= 0) {
		int step = STEPS;
		seedpool = this->generateSeed();
		int seednum = sqrt(this->nodenum);
		vector<Vertex*> seed(seedpool.begin(), seedpool.begin() + seednum);
		int clusterid = seed[0]->getclusterid();
		//结束条件为某一次的受影响节点为空或者step为0
		while (step-- >= 0 && !seed.empty()) {
			vector<Vertex*> seed2;
			//每次遍历种子节点
			for (auto it1 = seed.begin(); it1 != seed.end(); it1++) {
				Vertex* tmpVertex = (*it1);
				map<int, int>tmpneighbour = (*tmpVertex).getNeighbour();
				for (auto it2 = tmpneighbour.begin(); it2 != tmpneighbour.end(); it2++) {
					Vertex *tmpVertex2 = graph.getVertex((*it2).first);
					//如果某个点的邻居不属于这个聚类,continue.
					if ((*tmpVertex2).getclusterid() != clusterid)
						continue;
					double rand1 = (double)rand() / (double)RAND_MAX;
					//if (rand1 < (*tmpVertex2).getDegree())
					if (rand1 < 0.1)
						seed2.push_back(tmpVertex2);
				}
			}
			for (auto it3 = seed2.begin(); it3 != seed2.end(); it3++) {
				if (tmpresult.find((*(*it3)).getValue()) != tmpresult.end())
					tmpresult[(*(*it3)).getValue()] += 1;
				else
					tmpresult[(*(*it3)).getValue()] = 1;
			} 
			//保证每次初始时种子节点是唯一的
			sort(seed2.begin(), seed2.end(), mycompare2);
			seed2.erase(unique(seed2.begin(),seed2.end()), seed2.end());
			seed = seed2;
			vector<Vertex*>().swap(seed2);
		}
	}
	if (this->nodenum == 38)
		int a = 1;
	vector<pair<int,int> > sortresult;
	int max = (*(tmpresult.begin())).second;
	int index = (*(tmpresult.begin())).first;
	for (auto it4 = tmpresult.begin(); it4!= tmpresult.end(); it4++) {
		sortresult.push_back(make_pair((int)((*it4).first), (int)((*it4).second)));
	}
	sort(sortresult.begin(), sortresult.end(),mycompare);
	vector<pair<int,int> > returnresult(sortresult.begin(), sortresult.begin() + 3);
	return returnresult;
}
