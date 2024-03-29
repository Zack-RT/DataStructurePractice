// Vector.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Vector.hpp"
#include <cstdlib>
#include <ctime>
const int TEST_SIZE = 20;
using TEST_CLASS = int;

int main()
{
    clock_t t1, t2;
    TEST_CLASS testArray[TEST_SIZE];
    std::srand(std::time(nullptr));
    for (int i = 0; i < TEST_SIZE; i++) {
        testArray[i] = std::rand() % 100;
    }

    // 构造
//    t1 = clock();
    Vector<TEST_CLASS> testVector(testArray, TEST_SIZE);
//    t2 = clock();
    testVector.printElem();
//    printf("construction time is: %f s\n", ((double)(t2 - t1) / CLOCKS_PER_SEC));

    // 无序查找
    TEST_CLASS searchElem = testArray[rand() % TEST_SIZE];
    Rank searchElemRank = testVector.find(searchElem);
    cout << searchElem << "'s Rank is: " << searchElemRank << endl;

    // 删除
    Rank removeElemRank = rand() % TEST_SIZE;
    cout << "\nremove the " << removeElemRank << "th element" << endl;
    testVector.remove(removeElemRank);
    testVector.printElem();

    // 插入
    TEST_CLASS* insertElem = new TEST_CLASS(1);
    Rank insertRank = rand() % TEST_SIZE;
    cout << "insert " << *insertElem << " in " << insertRank << "th" << endl;
    testVector.insert(insertRank, *insertElem);
    testVector.printElem();

    return 0;
}

