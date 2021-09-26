#include <gtest/gtest.h>

#include "test_tmp.hh"

TEST(foo, bar) {
    ASSERT_EQ(f1(1), 0);
}

TEST(foo, bar2) {
    ASSERT_EQ(f1(-1), 1);
}

TEST(foo, bar3) {
    ASSERT_EQ(f1(0), -1);
}
