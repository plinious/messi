#include <gtest/gtest.h>
#define private public
#define protected public
#include "Range.h"

using messi::IntRange;

class RangeTest : public testing::Test {
 public:
  virtual void SetUp() {
  }

  virtual void TearDown() {
  }
};

template<typename T1>
static void allInFuncPass(const messi::Range<T1> &r) {
}
template<typename T1, typename ... T2>
static void allInFuncPass(const messi::Range<T1> &r, T1 arg1, T2... args) {
  EXPECT_TRUE(r.isIn(arg1));
  allInFuncPass(r, args...);
}

template<typename T1>
static void allInFuncFail(const messi::Range<T1> &r) {
}
template<typename T1, typename ... T2>
static void allInFuncFail(const messi::Range<T1> &r, T1 arg1, T2... args) {
  EXPECT_FALSE(r.isIn(arg1));
  allInFuncFail(r, args...);
}

TEST(RangeTest, int_test_empty_range) {
  IntRange ir;
  EXPECT_TRUE(ir.empty());
  auto const &kv = ir.getMap();
  EXPECT_TRUE(kv.empty());
  EXPECT_EQ(0, ir.size());

  ir.clear();
  EXPECT_TRUE(ir.empty());
  EXPECT_TRUE(kv.empty());
  EXPECT_EQ(0, ir.size());

  allInFuncFail(ir, 0, 2, 1000000, -1000000);
}

TEST(RangeTest, int_test_single_element) {
  IntRange ir;
  ir.put(1, 10);
  EXPECT_FALSE(ir.empty());
  EXPECT_EQ(1, ir.size());
  auto const &kv = ir.getMap();
  EXPECT_EQ(1, kv.size());

  allInFuncPass(ir, 1, 2, 9, 10);
  allInFuncFail(ir, 0, 11, 1000000, -1000000);
  ir.clear();
  EXPECT_TRUE(ir.empty());
  EXPECT_EQ(0, kv.size());
}

TEST(RangeTest, int_test_multi_element) {
  IntRange ir;
  ir.put(1, 10);
  ir.put(21, 96);
  ir.put(-19, 2);
  EXPECT_FALSE(ir.empty());

  allInFuncPass(ir, -19, -18, 0, 1, 2, 10, 21, 22, 95, 96);
  allInFuncFail(ir, -10000, -20, 11, 20, 97, 100000);
  EXPECT_EQ(2, ir.size());
  auto const &kv = ir.getMap();
  EXPECT_EQ(2, kv.size());
  EXPECT_EQ(-19, kv.at(10));
  EXPECT_EQ(21, kv.at(96));

  ir.clear();
  EXPECT_TRUE(ir.empty());
  EXPECT_TRUE(kv.empty());
}

TEST(RangeTest, int_test_same_put) {
  IntRange ir;
  ir.put(2, 30);
  EXPECT_EQ(1, ir.size());
  EXPECT_FALSE(ir.empty());

  ir.put(2, 30);
  EXPECT_EQ(1, ir.size());
  EXPECT_FALSE(ir.empty());
  auto const &kv = ir.getMap();
  EXPECT_EQ(2, kv.at(30));
}

TEST(RangeTest, int_test_diffrent_put_situation) {
  IntRange ir;

  // put a new one,which is biggest
  {
    ir.clear();
    ir.put(2, 90);
    ir.put(100, 96);
    EXPECT_FALSE(ir.empty());
    EXPECT_EQ(2, ir.size());
    allInFuncPass(ir, 2, 3, 50, 89, 90, 96, 99, 100);
    allInFuncFail(ir, -1, 0, 1, 91, 95, 101, 500);
    auto const &kv = ir.getMap();
    EXPECT_EQ(2, kv.at(90));
    EXPECT_EQ(96, kv.at(100));
  }

  // put a new one, which cover all the range of the old ones
  {
    ir.clear();
    ir.put(1, 9);
    ir.put(30, 87);
    EXPECT_FALSE(ir.empty());
    allInFuncPass(ir, 1, 8, 9, 30, 86, 87);
    allInFuncFail(ir, -1, 0,10, 29, 88, 90);
    auto const &kv = ir.getMap();
    EXPECT_EQ(1, kv.at(9));
    EXPECT_EQ(30, kv.at(87));
    EXPECT_EQ(2, ir.size());

    ir.put(0, 90);
    EXPECT_FALSE(ir.empty());
    EXPECT_EQ(0, kv.at(90));
    EXPECT_EQ(1, ir.size());
    allInFuncPass(ir, 0, 1, 10, 21, 40, 70, 90);
    allInFuncFail(ir, -1, 91, 99, 200);
  }

  // put a new one, which is sub-set of an old new, and make no difference
  {
    ir.clear();
    ir.put(1, 9);
    ir.put(30, 87);
    EXPECT_FALSE(ir.empty());
    EXPECT_EQ(2, ir.size());
    allInFuncPass(ir, 1, 8, 9, 30, 55, 77, 86, 87);
    allInFuncFail(ir, -1, 0, 88, 90);
    auto const &kv = ir.getMap();
    EXPECT_EQ(1, kv.at(9));
    EXPECT_EQ(30, kv.at(87));

    ir.put(50, 60);
    EXPECT_EQ(2, ir.size());
    EXPECT_EQ(1, kv.at(9));
    EXPECT_EQ(30, kv.at(87));
    allInFuncPass(ir, 1, 8, 9, 30, 55, 77, 86, 87);
    allInFuncFail(ir, -1, 0, 88, 90);
  }

  // cross-cover
  {
    ir.clear();
    ir.put(1, 9);
    ir.put(30, 87);
    EXPECT_FALSE(ir.empty());
    EXPECT_EQ(2, ir.size());
    auto const &kv = ir.getMap();
    EXPECT_EQ(1, kv.at(9));
    EXPECT_EQ(30, kv.at(87));
    allInFuncPass(ir, 1, 8, 9, 30, 55, 77, 86, 87);
    allInFuncFail(ir, -1, 0, 10, 15, 29, 88, 90);
    ir.put(9, 31);
    EXPECT_EQ(1, ir.size());
    EXPECT_EQ(1, kv.at(87));
    allInFuncPass(ir, 1, 8, 9, 15, 29, 55, 77, 86, 87);
    allInFuncFail(ir, -1, 0, 88, 90);
  }

  // cross-cover again
  {
    ir.clear();
    ir.put(1, 9);
    ir.put(30, 87);
    EXPECT_FALSE(ir.empty());
    EXPECT_EQ(2, ir.size());
    auto const &kv = ir.getMap();
    EXPECT_EQ(1, kv.at(9));
    EXPECT_EQ(30, kv.at(87));
    allInFuncPass(ir, 1, 8, 9, 30, 55, 77, 86, 87);
    allInFuncFail(ir, -1, 0, 10, 15, 29, 88, 90, 120);
    ir.put(50, 150);
    EXPECT_EQ(2, ir.size());
    EXPECT_EQ(1, kv.at(9));
    EXPECT_EQ(30, kv.at(150));
    allInFuncPass(ir, 1, 8, 9, 30, 31, 55, 77, 86, 87, 100, 149, 150);
    allInFuncFail(ir, -1, 0, 151, 200);
  }

  // cross-cover again and again
  {
    ir.clear();
    ir.put(1, 9);
    ir.put(30, 87);
    EXPECT_FALSE(ir.empty());
    EXPECT_EQ(2, ir.size());
    auto const &kv = ir.getMap();
    EXPECT_EQ(1, kv.at(9));
    EXPECT_EQ(30, kv.at(87));
    allInFuncPass(ir, 1, 8, 9, 30, 55, 77, 86, 87);
    allInFuncFail(ir, -1, 0, 10, 15, 29, 88, 90, 120);
    ir.put(21, 50);
    EXPECT_EQ(2, ir.size());
    EXPECT_EQ(1, kv.at(9));
    EXPECT_EQ(21, kv.at(87));
    allInFuncPass(ir, 1, 8, 9, 21, 29, 49, 55, 77, 86, 87);
    allInFuncFail(ir, -1, 0, 10, 20, 88, 10000);
  }
}

