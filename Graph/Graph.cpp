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
		case UNDISCOVERED:	//δ���֣��������߲��ݹ�
			type(i, u) = TREE; dfs(u, clock); break;
		case DISCOVERED:	//�ѷ��֣����Ϊ�ر�
			type(i, u) = BACKWARD; break;
		default:			//�ѷ��ʣ�����ǰ�ڵ���緢�ֱ��Ϊ��ǰ�ߣ���֮���
			type(i, u) = (dTime(i) < dTime(u) ? FORWARD : CROSS); break;
		}
	status(i) = VISITED; fTime(i) = clock++;
	//���˽ڵ�������������Ϊ���ʲ���¼��ʱ��
}

template<typename Tv, typename Te>
void Graph<Tv, Te>::BFS(int i) {
	reset(); int clock = 0, v = i;
	do { //�ڵ㼯�����ö�٣�����δ���ֵ�����Ϊ���
		if (status(v) == UNDISCOVERED)
			bfs(v, clock);
	} while (i != (v = (++v % nv)));
}

template<typename Tv, typename Te>
void Graph<Tv, Te>::DFS(int i) {
	reset(); int clock = 0, v = i;
	do { //�ڵ㼯�����ö�٣�����δ���ֵ�����Ϊ���
		if (status(v) == UNDISCOVERED)
			dfs(v, clock);
	} while (i != (v = (++v % nv)));
}

