#pragma once
//�ڽӾ���ʵ��ͼ
#include "Graph.cpp"
#include <vector>
using std::vector;

template<typename Tv> struct Vertex{
	Tv data;	//��������
	int inDegree, outDegree;	//��ȳ���
	VStatus status;		//����״̬
	int dTime, fTime;	//ʱ���ǩ
	int parent;			//�ڱ������еĸ��ڵ�
	int priority;		//�ڱ������е����ȼ�
	Vertex(const Tv & d) :	//���캯��
		data(d), inDegree(0), outDegree(0), status(UNDISCOVERED),
		dTime(-1), fTime(-1), parent(-1), priority(INT_MAX) {}
};

template <typename Te> struct Edge{
	Te data;	//������
	int weight;	//Ȩ��
	Etype etype;	//������
	Edge(const Te & d, int w) :	//���캯��
		data(d), weight(w), etype(UNDETERMINED) {}
};

template <typename Tv, typename Te>
class GraphMatrix: public Graph<Tv, Te>{
private:
	vector< Vertex<Tv> > V;				//�㼯
	vector< vector< Edge<Te>* > > E;	//�߼�
public:
	GraphMatrix() { this->ne = this->nv = 0; }
	~GraphMatrix() {	//ɾ����̬������ڴ漴��
		for (int i = 0; i < this->nv; i++)
			for (int j = 0; j < this->nv; j++)
				delete E[i][j];
	}
//�����
	virtual int getnv(void) { return this->nv; }
	virtual int insert(const Tv & vData) {
		for (int i = 0; i < this->nv; i++)	//ԭ�߼�Ϊ�µ�Ԥ��λ��
			E[i].push_back((Edge<Te>*)nullptr);
		V.push_back(Vertex<Tv>(vData));	this->nv++;	//�㼯���в����µ㣬����+1
		E.push_back(vector< Edge<Te>* >(this->nv, (Edge<Te>*)nullptr));	//�µ�����Ӧ�ı߼�
		return this->nv - 1;	//���ز��������
	}
	virtual Tv remove(int i) {	//0 <= i < n
		if (this->nv - 1 < i) exit(1);
		for (int j = 0; j < this->nv; j++)	//ɾ��i�ĳ���
			if (exist(i, j)) {	delete E[i][j];	V[j].inDegree--; }
		E.erase(E.begin() + i);	this->nv--;	//ɾ������ĵ�i��
		Tv temp = V[i].data;	V.erase(V.begin() + i);	//ɾ����i����
		for (int j = 0; j < this->nv; j++) {
			Edge<Te>* e = E[j][i];	
			E[j].erase(E[j].begin() + i);
			if (e) { delete e; V[j].outDegree--; }
		}
		return temp;
	}
	virtual int nextNbr(int i, int j) {	//�Ժ���ǰѰ��
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
//�߲���
	virtual int getne(void) { return this->ne; }
	virtual bool exist(int i, int j) {
		return -1 < i && -1 < j && i < this->nv && j < this->nv && E[i][j] != nullptr;
	}
	virtual void insert(const Te & eData, int i, int j, int weight = 0) {
		if (exist(i, j)) return;
		E[i][j] = new Edge<Te>(eData, weight);
		this->ne++; V[i].outDegree++; V[j].inDegree++;
	}
	virtual Te remove(int i, int j) {	//����E[i][j]
		Te temp = edge(i, j);
		V[i].outDegree--; V[j].inDegree--;
		delete E[i][j]; E[i][j] = nullptr; this->ne--;
		return temp;
	}
	virtual Etype& type(int i, int j) { return E[i][j]->etype; }
	virtual Te& edge(int i, int j) { return E[i][j]->data; }
	virtual int& weight(int i, int j) { return E[i][j]->weight; }
//algorithm:
	void BFS(int i) { Graph<Tv, Te>::BFS(i); }			//�����������
	void DFS(int i) { Graph<Tv, Te>::DFS(i); }			//�����������
};