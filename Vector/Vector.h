#pragma once
typedef int Rank;
const int DEFAULT_CAPCITY = 3;

template <typename T> class Vector {
public:
	Rank _size;	int _capacity;	T* _elem;
	void copyFrom(T const* A, Rank lo, Rank hi);
	void expand();
	void shrink();
	Rank max(Rank lo, Rank hi);
	Rank max() { return max(0, _size); }

	bool bubble(Rank lo, Rank hi);
	void bubbleSort(Rank lo, Rank hi);
	void merge(Rank lo, Rank mi, Rank hi);
	void mergeSort(Rank lo, Rank hi);
	//void selectionSort(Rank lo, Rank hi);
	//Rank partition(Rank lo, Rank hi);
	//void quickSort(Rank lo, Rank hi);
	//void heapSort(Rank lo, Rank hi);
public:
	//constructor
	Vector(int c = DEFAULT_CAPCITY, int s = 0, int v = 0) {
		_elem = new T[_capacity = c];
		for (_size = 0; _size < s; _elem[_size++] = v);
	}
	Vector(T* const A, Rank n) { copyFrom(A, 0, n); }
	Vector(T* const A, Rank lo, Rank hi) { copyFrom(A, lo, hi); }
	Vector(Vector const& V) { copyFrom(V._elem, 0, V._size); }
	Vector(Vector const& V, Rank lo, Rank hi) { copyFrom(V._elem, lo, hi); }
	//destructor
	~Vector() { delete[] _elem; }

	//只读接口
	void print()const;
	int get_size_capacity()const;

	Rank size()const { return _size; }
	bool empty()const { return !_size; }
	int disordered()const;
	Rank find(T const& e, Rank lo, Rank hi) const;
	Rank find(T const& e)const { return find(e, 0, _size); }
	Rank search(T const& e, Rank lo, Rank hi) const;
	Rank search(T const& e)const {
		return (0 >= _size) ? -1 : search(e, 0, _size);
	}

	//可写接口
	T& operator[](Rank t)const;
	Vector<T> & operator=(Vector<T> const& t);
	int remove(Rank lo, Rank hi);
	int remove(Rank r) { return remove(r, r + 1); }
	Rank insert(Rank r, T const& e);
	Rank insert(T const& e) { return insert(_size, e); }//默认在末尾插入
	int deduplicate();
	int uniquify();
	void sort(Rank lo, Rank hi);
	void sort() { sort(0, _size); };
	void unsort(Rank lo, Rank hi);
	void unsort() { unsort(0, _size); };
	//遍历 函数指针、函数对象
	void traverse(void(*visit)(T&));
	template <typename VST> void traverse(VST&);
};