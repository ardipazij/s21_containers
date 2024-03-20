#ifndef CPP2_S21_CONTAINERS_UNIT_TEST_S21_ARRAY_TEST_H
#define CPP2_S21_CONTAINERS_UNIT_TEST_S21_ARRAY_TEST_H

#include <gtest/gtest.h>

#include "../src/s21_containers.h"
#include "../src/s21_containersplus.h"

namespace s21 {
class s21ContainersMapTest : public testing::Test {
 protected:
  std::map<int, std::string>* std_map;
  map<int, std::string>* s21_map;

  void SetUp();
  void TearDown();
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_UNIT_TEST_S21_ARRAY_TEST_H