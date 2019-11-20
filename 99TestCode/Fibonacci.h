#pragma once

class Fibonacci {
private:
	int n;	//记录当前元素的序号
	__int64 f, g;	//g为当前序号下的值，f为前一个值
public:
	Fibonacci(): n(0), f(1), g(0) {}	//默认初始为fib(0) = 0 fib(-1) = 1
	Fibonacci(int n) {
		f = 1; g = 0;
		while (n-- > 0){
			g += f;
			f = g - f;
		}
	}
	int getRank() { return n; }		//返回当前fib数列序号
	__int64 get() { return g; }		//返回当前fib值
	__int64 getNext() { g += f; f = g - f; n++; return g; }		//求下一项的值
	__int64 getPrev() { f = g - f; g -= f; n--; return g; }		//求上一项的值
};