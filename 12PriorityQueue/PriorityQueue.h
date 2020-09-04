#pragma once
template <typename T> struct PriorityQueue
{
	virtual void insert(T) = 0;
	virtual T getMax(void) = 0;
	virtual T delMax(void) = 0;
};