#include <gtest/gtest.h>

#include "StringUtil.h"

#include <iostream>

using namespace std;
using namespace messi;

TEST(toHexTest, toHexTestCase){
    {
    std::string s1;
    s1.append(1, '\n').append(1, 247);
    std::string s = StringUtil::toHex(s1);
    cout << s << endl;
    ASSERT_EQ("0AF7", s);
    }
}
