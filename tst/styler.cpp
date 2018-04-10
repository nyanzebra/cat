#include "gtest/gtest.h"

#include "output/styler.hpp"

#include "deps/std.hpp"

TEST(colour, colour) {
  output::colour test;

  std::stringstream stream;
  stream << test;

  EXPECT_EQ(std::string("0;0;0"), stream.str());

  stream.str(std::string());
  stream.clear();
  test = output::colour(1,2,3);
  stream << test;

  EXPECT_EQ(std::string("1;2;3"), stream.str());

  stream.str(std::string());
  stream.clear();
  test = output::colour(0xFFFFFF);
  stream << test;

  EXPECT_EQ(std::string("255;255;255"), stream.str());
}

TEST(styler, styler) {
  output::styler test;

  EXPECT_EQ(std::string("\x1b[38;2;0;0;0m\x1b[48;2;0;0;0m\x1b[0m\x1b[0m"), test.style(""));

  test.foreground(0x55AAFF);
  test.background(0xFFAA55);
  EXPECT_EQ(std::string("\x1b[38;2;85;170;255m\x1b[48;2;255;170;85m\x1b[0m\x1b[0m"), test.style(""));

  test.is_bold(true);
  test.is_underlined(true);
  test.foreground(0xFF0000);
  test.background(0x00CC33);
  std::cout << test.style("Hello, World!") << std::endl;
}
