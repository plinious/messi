#include <gtest/gtest.h>

#include "IpAddr.h"

#include <iostream>

using namespace std;
using namespace messi;

TEST(toHexTest, toHexTestCase){
    // 整数值和字符串值均正确
    {
    IpAddr addr;
    addr.setFromString("0.0.0.00");
    ASSERT_EQ(addr.getIpAddr(), "0.0.0.0");
    ASSERT_EQ(addr.getIpAddrI(), 0);
    }
}
