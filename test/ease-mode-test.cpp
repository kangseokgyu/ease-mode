#include <gtest/gtest.h>

#include "ease-mode/ease-mode.hpp"

enum class test_mode {
  _1 = 1,
  _2 = 2,

  defval = _1,
};

TEST(ease_mode_test, mt_test) {
  ease::mode_mt<test_mode> m;

  auto checked = m.check();
  EXPECT_FALSE(checked.first);
}

TEST(ease_mode_test, check_test) {
  ease::mode_mt<test_mode> m;

  {
    auto checked = m.check();
    EXPECT_FALSE(checked.first);
    EXPECT_EQ(checked.second, test_mode::_1);
  }

  m.change(test_mode::_2);

  {
    auto checked = m.check();
    EXPECT_TRUE(checked.first);
    EXPECT_EQ(checked.second, test_mode::_2);
  }
}

TEST(ease_mode_test, change_test) {
  ease::mode_mt<test_mode> m;

  auto res1 = m.change(test_mode::_2);
  EXPECT_TRUE(res1);

  auto res2 = m.change(test_mode::_2);
  EXPECT_FALSE(res2);
}
