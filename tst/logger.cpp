#include "gtest/gtest.h"

#include "output/logger.hpp"

TEST(logger, test) {
  output::logger l(output::output_type::kSTANDARD_OUTPUT);
  l.debug("test");
  l.info("test");
  l.error("test");
  l.warning("test");
}
