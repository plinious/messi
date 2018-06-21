#include "gtest/gtest.h"

#include <iostream>
using namespace std;

int main(int argc,char* argv[]) {
    testing::InitGoogleTest(&argc,argv); //初始化
    RUN_ALL_TESTS();                     //跑单元测试
    return 0;
}
