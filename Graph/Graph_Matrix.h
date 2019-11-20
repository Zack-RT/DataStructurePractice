#pragma once
//邻接矩阵实现图
#include "Graph.cpp"
#include <vector>
using std::vector;

template<typename Tv> struct Vertex{
	Tv data;	//顶点数据
	int inDegree, outDegree;	//入度出度
	VStatus status;		//顶点状态
	int dTime, fTime;	//时间标签
	int parent;			//在遍历树中的父节点
	int priority;		//在遍历树中的优先级
	Vertex(const Tv & d) :	//构造函数
		data(d), inDegree(0), outDegree(0), status(UNDISCOVERED),
		dTime(-1), fTime(-1), parent(-1), priority(INT_MAX) {}
};

template <typename Te> struct Edge{
	Te data;	//边数据
	int weight;	//权重
	Etype etype;	//边类型
	Edge(const Te & d, int w) :	//构造函数
		data(d), weight(w), etype(UNDETERMINED) {}
};

template <typename Tv, typename Te>
class GraphMatrix: public Graph<Tv, Te>{
private:
	vector< Vertex<Tv> > V;				//点集
	vector< vector< Edge<Te>* > > E;	//边集
public:
	GraphMatrix() { this->ne = this->nv = 0; }
	~GraphMatrix() {	//删除动态分配的内存即可
		for (int i = 0; i < this->nv; i++)
			for (int j = 0; j < this->nv; j++)
				delete E[i][j];
	}
//点操作
	virtual int getnv(void) { return this->nv; }
	virtual int insert(const Tv & vData) {
		for (int i = 0; i < this->nv; i++)	//原边集为新点预留位置
			E[i].push_back((Edge<Te>*)nullptr);
		V.push_back(Vertex<Tv>(vData));	this->nv++;	//点集当中插入新点，点数+1
		E.push_back(vector< Edge<Te>* >(this->nv, (Edge<Te>*)nullptr));	//新点所对应的边集
		return this->nv - 1;	//返回插入点的序号
	}
	virtual Tv remove(int i) {	//0 <= i < n
		if (this->nv - 1 < i) exit(1);
		for (int j = 0; j < this->nv; j++)	//删除i的出边
			if (exist(i, j)) {	delete E[i][j];	V[j].inDegree--; }
		E.erase(E.begin() + i);	this->nv--;	//删除矩阵的第i行
		Tv temp = V[i].data;	V.erase(V.begin() + i);	//删除第i个点
		for (int j = 0; j < this->nv; j++) {
			Edge<Te>* e = E[j][i];	
			E[j].erase(E[j].begin() + i);
			if (e) { delete e; V[j].outDegree--; }
		}
		return temp;
	}
	virtual int nextNbr(int i, int j) {	//自后向前寻找
		while ((-1 < j) && (!exist(i, --j))); return j;
	}
	virtual Tv& vertex(int i) { return V[i].data; }
	virtual int inDegree(int i) { return V[i].inDegree; }
	virtual int outDegree(int i) { return V[i].outDegree; }
	virtual int firstNbr(int i) { return nextNbr(i, this->nv); }
	virtual VStatus& status(int i) { return V[i].status; }
	virtual int& dTime(int i) { return V[i].dTime; }
	virtual int& fTime(int i) { return V[i].fTime; }
	virtual int& parent(int i) { return V[i].parent; }
	virtual int& priority(int i) { return V[i].priority; }
//边操作
	virtual int getne(void) { return this->ne; }
	virtual bool exist(int i, int j) {
		return -1 < i && -1 < j && i < this->nv && j < this->nv && E[i][j] != nullptr;
	}
	virtual void insert(const Te & eData, int i, int j, int weight = 0) {
		if (exist(i, j)) return;
		E[i][j] = new Edge<Te>(eData, weight);
		this->ne++; V[i].outDegree++; V[j].inDegree++;
	}
	virtual Te remove(int i, int j) {	//存在E[i][j]
		Te temp = edge(i, j);
		V[i].outDegree--; V[j].inDegree--;
		delete E[i][j]; E[i][j] = nullptr; this->ne--;
		return temp;
	}
	virtual Etype& type(int i, int j) { return E[i][j]->etype; }
	virtual Te& edge(int i, int j) { return E[i][j]->data; }
	virtual int& weight(int i, int j) { return E[i][j]->weight; }
//algorithm:
	void BFS(int i) { Graph<Tv, Te>::BFS(i); }			//广度优先搜索
	void DFS(int i) { Graph<Tv, Te>::DFS(i); }			//深度优先搜索
};