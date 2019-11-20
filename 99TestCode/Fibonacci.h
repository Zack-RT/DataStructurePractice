#pragma once

class Fibonacci {
private:
	int n;	//��¼��ǰԪ�ص����
	__int64 f, g;	//gΪ��ǰ����µ�ֵ��fΪǰһ��ֵ
public:
	Fibonacci(): n(0), f(1), g(0) {}	//Ĭ�ϳ�ʼΪfib(0) = 0 fib(-1) = 1
	Fibonacci(int n) {
		f = 1; g = 0;
		while (n-- > 0){
			g += f;
			f = g - f;
		}
	}
	int getRank() { return n; }		//���ص�ǰfib�������
	__int64 get() { return g; }		//���ص�ǰfibֵ
	__int64 getNext() { g += f; f = g - f; n++; return g; }		//����һ���ֵ
	__int64 getPrev() { f = g - f; g -= f; n--; return g; }		//����һ���ֵ
};