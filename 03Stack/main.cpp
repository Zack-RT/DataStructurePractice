// 03Stack.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
//#include "Stack_List.hpp"
#include "Stack_Vector.hpp"
#include <cstdlib>
#include <ctime>
using namespace std;
const int TEST_SIZE = 20;
using TEST_CLASS = int;

int main()
{
    srand(time(nullptr));
    Stack<TEST_CLASS> testStack;
    for (int i = 0; i < TEST_SIZE; i++) {
        testStack.push(rand() % 100);
    }
    testStack.printElem();
    return 0;
}

