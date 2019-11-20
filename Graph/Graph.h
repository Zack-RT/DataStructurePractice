#pragma once

typedef enum { UNDISCOVERED, DISCOVERED, VISITED } VStatus;				//点状态
typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } Etype;	//边类型

template <typename Tv, typename Te>
class Graph{
private:
	void reset() {//遍历前的状态复位
		for (int i = 0; i < nv; i++) {//所有点
			//通过函数返回引用进行复位赋值
			status(i) = UNDISCOVERED;
			dTime(i) = fTime(i) = -1;
			parent(i) = -1; priority(i) = INT_MAX;
			for (int j = 0; j < ne; j++)//所有边
				if (exist(i, j)) type(i, j) = UNDETERMINED;
		}
	}
	void bfs(int, int&);		//对一个连通分支的广度优先搜索
	void dfs(int, int&);		//对一个连通分支的深度优先搜索
protected:
	int nv, ne;		//点、边数
//点操作：
	virtual int insert(const Tv &) = 0;		//插入点，返回点号
	virtual Tv remove(int) = 0;				//删除点及其相关边，返回该点信息
	virtual Tv& vertex(int) = 0;			//返回点（若存在）的信息
	virtual int inDegree(int) = 0;			//点的入度
	virtual int outDegree(int) = 0;			//点的出度
	virtual int firstNbr(int) = 0;			//点的第一个邻接点
	virtual int nextNbr(int, int) = 0;		//点1相对于点2的下一邻接点
	virtual VStatus& status(int) = 0;		//该点状态
	virtual int& dTime(int) = 0;			//该点的时间标签dTime
	virtual int& fTime(int) = 0;			//该点的时间标签fTime
	virtual int& parent(int) = 0;			//该点（遍历树中）的父节点
	virtual int& priority(int) = 0;			//该点（遍历树中）的优先级
//边操作：
	virtual bool exist(int, int) = 0;		//边是否存在
	virtual void insert(const Te &, int, int, int) = 0;	//插入边
	virtual Te remove(int, int) = 0;		//删除边，返回信息
	virtual Etype& type(int, int) = 0;		//边类型
	virtual Te& edge(int, int) = 0;			//返回边（若存在）的信息
	virtual int& weight(int, int) = 0;		//返回权重
//algorithm:
	void BFS(int);			//广度优先搜索
	void DFS(int);			//深度优先搜索
};
