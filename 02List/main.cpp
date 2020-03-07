// 02List.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <cstdlib>
#include <ctime>
#include "List.hpp"

const int TEST_SIZE = 20;
using TEST_CLASS = int;

int main()
{
//    clock_t t1, t2;
    std::srand(std::time(nullptr));
    List<TEST_CLASS> testList;
    for (int i = 0; i < TEST_SIZE; i++) {
        testList.insertAsLast(std::rand() % 100);
    }
    testList.PrintElem();
    
    return 0;
}

