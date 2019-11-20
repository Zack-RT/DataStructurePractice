#include "stdafx.h"
#include "Graph.h"
using std::queue;

template<typename Tv, typename Te>
void Graph<Tv, Te>::bfs(int i, int & clock) {
	queue<int> Q; status(i) = DISCOVERED; Q.push(i);
	while (!Q.empty()) {
		int v = Q.front(); Q.pop();
		dTime(v) = clock++;
		for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u))
			if (status(u) == UNDISCOVERED) {
				status(u) = DISCOVERED; Q.push(u);
				type(v, u) = TREE; parent(u) = v;
			}
			else type(v, u) = CROSS;
		status(v) = VISITED;
	}
}

template<typename Tv, typename Te>
void Graph<Tv, Te>::dfs(int i, int & clock) {
	status(i) = DISCOVERED; dTime(i) = clock++;
	for (int u = firstNbr(i); -1 < u; u = nextNbr(i, u))
		switch (status(u)) {
		case UNDISCOVERED:	//未发现，纳入树边并递归
			type(i, u) = TREE; dfs(u, clock); break;
		case DISCOVERED:	//已发现，标记为回边
			type(i, u) = BACKWARD; break;
		default:			//已访问，若当前节点更早发现标记为向前边，反之跨边
			type(i, u) = (dTime(i) < dTime(u) ? FORWARD : CROSS); break;
		}
	status(i) = VISITED; fTime(i) = clock++;
	//至此节点操作结束，标记为访问并记录下时间
}

template<typename Tv, typename Te>
void Graph<Tv, Te>::BFS(int i) {
	reset(); int clock = 0, v = i;
	do { //在点集中逐个枚举，遇到未发现的以其为起点
		if (status(v) == UNDISCOVERED)
			bfs(v, clock);
	} while (i != (v = (++v % nv)));
}

template<typename Tv, typename Te>
void Graph<Tv, Te>::DFS(int i) {
	reset(); int clock = 0, v = i;
	do { //在点集中逐个枚举，遇到未发现的以其为起点
		if (status(v) == UNDISCOVERED)
			dfs(v, clock);
	} while (i != (v = (++v % nv)));
}

