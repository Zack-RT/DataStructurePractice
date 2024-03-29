// Graph.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Graph_Matrix.h"
#include <iostream>
using namespace std;

static int testRound = 0;
typedef char vertexType;
typedef int graphType;

template <typename Tv, typename Te>	//输出图的点集与邻接矩阵
void printGraphInfo(GraphMatrix<Tv, Te>& G);

template <typename Tv, typename Te>	//输出各个点的fTime Dtime
void printFDtime(GraphMatrix<Tv, Te>& G);

int main()
{
	GraphMatrix<vertexType, graphType> G;
	for (char i = 'A'; i <= 'G'; i++)
		G.insert(i);
	G.insert(1, 0, 1); G.insert(1, 0, 5); G.insert(1, 0, 2);
	G.insert(1, 1, 2); G.insert(1, 5, 6); G.insert(1, 6, 0);
	G.insert(1, 6, 2); G.insert(1, 3, 0); G.insert(1, 3, 4);
	G.insert(1, 4, 5); printGraphInfo(G);
	G.BFS(0); printFDtime(G);
	G.DFS(0); printFDtime(G);

//	system("pause");
    return 0;
}

template <typename Tv, typename Te>
void printGraphInfo(GraphMatrix<Tv, Te>& G) {
	cout << "Round: " << ++testRound << endl;
	cout << "---------Vertex----------" << endl;
	for (int i = 0; i < G.getnv(); i++)
		cout << G.vertex(i) << " ";
	cout << endl;
	cout << "---------Matrix----------" << endl;
	for (int i = 0; i < G.getnv(); i++) {
		for (int j = 0; j < G.getnv(); j++)
			if (G.exist(i, j)) cout << G.edge(i, j) << " ";
			else cout << "0" << " ";
			cout << endl;
	}
	cout << "--------inDegree---------" << endl;
	for (int i = 0; i < G.getnv(); i++)
		cout << G.inDegree(i) << " ";
	cout << endl;
	cout << "--------outDegree--------" << endl;
	for (int i = 0; i < G.getnv(); i++)
		cout << G.outDegree(i) << " ";
	cout << endl;
}

template<typename Tv, typename Te>
void printFDtime(GraphMatrix<Tv, Te>& G){
	cout << "Vertex\tftime\tdtime" << endl;
	for (int n = 0; n < G.getnv(); n++)
		cout << G.vertex(n) << "\t" <<
		G.dTime(n) << "\t" << G.fTime(n) << endl;
}
