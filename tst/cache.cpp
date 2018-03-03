#include "gtest/gtest.h"

#include "utility/cache.hpp"

TEST(cache, insert) {
  cache<int, int> c;

  c.insert(1, 1);
  EXPECT_TRUE(c.has(1));
}

TEST(cache, erase) {
  cache<int, int> c;

  c.insert(1, 1);
  EXPECT_TRUE(c.has(1));

  c.erase(1);
  EXPECT_FALSE(c.has(1));
}

TEST(cache, at) {
  cache<int, int> c;

  c.insert(1, 1);
  EXPECT_TRUE(c.has(1));
  EXPECT_EQ(1, c.at(1));
}

TEST(cache, size) {
  cache<int, int> c;

  c.insert(1, 1);
  EXPECT_TRUE(c.has(1));
  EXPECT_EQ(1, c.size());

  c.erase(1);
  EXPECT_FALSE(c.has(1));
  EXPECT_EQ(0, c.size());
}
