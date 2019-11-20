#pragma once

typedef enum { UNDISCOVERED, DISCOVERED, VISITED } VStatus;				//��״̬
typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } Etype;	//������

template <typename Tv, typename Te>
class Graph{
private:
	void reset() {//����ǰ��״̬��λ
		for (int i = 0; i < nv; i++) {//���е�
			//ͨ�������������ý��и�λ��ֵ
			status(i) = UNDISCOVERED;
			dTime(i) = fTime(i) = -1;
			parent(i) = -1; priority(i) = INT_MAX;
			for (int j = 0; j < ne; j++)//���б�
				if (exist(i, j)) type(i, j) = UNDETERMINED;
		}
	}
	void bfs(int, int&);		//��һ����ͨ��֧�Ĺ����������
	void dfs(int, int&);		//��һ����ͨ��֧�������������
protected:
	int nv, ne;		//�㡢����
//�������
	virtual int insert(const Tv &) = 0;		//����㣬���ص��
	virtual Tv remove(int) = 0;				//ɾ���㼰����رߣ����ظõ���Ϣ
	virtual Tv& vertex(int) = 0;			//���ص㣨�����ڣ�����Ϣ
	virtual int inDegree(int) = 0;			//������
	virtual int outDegree(int) = 0;			//��ĳ���
	virtual int firstNbr(int) = 0;			//��ĵ�һ���ڽӵ�
	virtual int nextNbr(int, int) = 0;		//��1����ڵ�2����һ�ڽӵ�
	virtual VStatus& status(int) = 0;		//�õ�״̬
	virtual int& dTime(int) = 0;			//�õ��ʱ���ǩdTime
	virtual int& fTime(int) = 0;			//�õ��ʱ���ǩfTime
	virtual int& parent(int) = 0;			//�õ㣨�������У��ĸ��ڵ�
	virtual int& priority(int) = 0;			//�õ㣨�������У������ȼ�
//�߲�����
	virtual bool exist(int, int) = 0;		//���Ƿ����
	virtual void insert(const Te &, int, int, int) = 0;	//�����
	virtual Te remove(int, int) = 0;		//ɾ���ߣ�������Ϣ
	virtual Etype& type(int, int) = 0;		//������
	virtual Te& edge(int, int) = 0;			//���رߣ������ڣ�����Ϣ
	virtual int& weight(int, int) = 0;		//����Ȩ��
//algorithm:
	void BFS(int);			//�����������
	void DFS(int);			//�����������
};
