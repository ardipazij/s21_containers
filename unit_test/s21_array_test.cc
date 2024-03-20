#include <array>
#include <exception>

#include "s21_containers_test.h"

TEST(s21ArrayTest, ConstructorTest) {
  s21::array<int, 5> s21_array;
  std::array<int, 5> std_array;
  EXPECT_EQ(s21_array.size(), 5);

  EXPECT_EQ(s21_array.size(), std_array.size());
  for (size_t i = 0; i < s21_array.size(); ++i) {
    EXPECT_EQ(s21_array[i], 0);
  }
}

TEST(s21ArrayTest, ConstructorInitializerList) {
  s21::array<double, 5> s21_array_double{3.1, 4.2, 5.3, 7.4, 8.5};
  std::array<double, 5> std_array_double{3.1, 4.2, 5.3, 7.4, 8.5};
  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(s21_array_double[i], std_array_double[i]);
  }
  EXPECT_EQ((s21_array_double)[0], 3.1);
  EXPECT_EQ((s21_array_double)[1], 4.2);
  EXPECT_EQ((s21_array_double)[2], 5.3);
  EXPECT_EQ((s21_array_double)[3], 7.4);
  EXPECT_EQ((s21_array_double)[4], 8.5);
}

TEST(s21ArrayTest, CopyConstructor) {
  s21::array<int, 4> arr = {2, 8, 9, 11};
  s21::array<int, 4> arr2(arr);
  EXPECT_EQ(arr2.at(0), 2);
  EXPECT_EQ(arr2.at(1), 8);
  EXPECT_EQ(arr2.at(2), 9);
  EXPECT_EQ(arr2.at(3), 11);
}

TEST(s21ArrayTest, OperatorCopy) {
  const s21::array<int, 4> arr = {2, 8, 9, 11};
  s21::array<int, 4> arr2 = arr;
  EXPECT_EQ(arr2.at(0), 2);
  EXPECT_EQ(arr2.at(1), 8);
  EXPECT_EQ(arr2.at(2), 9);
  EXPECT_EQ(arr2.at(3), 11);
}

TEST(s21ArrayTest, MoveConstructor) {
  s21::array<int, 4> arr = {2, 8, 9, 11};
  s21::array<int, 4> arr2(std::move(arr));
  EXPECT_EQ(arr2.at(0), 2);
  EXPECT_EQ(arr2.at(1), 8);
  EXPECT_EQ(arr2.at(2), 9);
  EXPECT_EQ(arr2.at(3), 11);
}

TEST(s21ArrayTest, OperatorMove) {
  const s21::array<int, 4> arr = {2, 8, 9, 11};
  s21::array<int, 4> arr2 = std::move(arr);
  EXPECT_EQ(arr2.at(0), 2);
  EXPECT_EQ(arr2.at(1), 8);
  EXPECT_EQ(arr2.at(2), 9);
  EXPECT_EQ(arr2.at(3), 11);
}

TEST(s21ArrayTest, IsEmptyArray) {
  const s21::array<int, 0> arr;
  EXPECT_TRUE(arr.empty());
}

TEST(s21ArrayTest, ArraySize) {
  s21::array<std::string, 3> s21_arr = {"aa", "bb", "cc"};
  std::array<std::string, 3> std_arr = {"aa", "bb", "cc"};
  EXPECT_EQ(s21_arr.size(), 3);
  EXPECT_EQ(s21_arr.size(), std_arr.size());
}

TEST(s21ArrayTest, ArrayMaxSize) {
  s21::array<std::string, 4> s21_arr = {"aa", "bb", "cc"};
  std::array<std::string, 4> std_arr = {"aa", "bb", "cc"};
  EXPECT_EQ(s21_arr.max_size(), 4);
  EXPECT_EQ(s21_arr.max_size(), std_arr.max_size());
}

TEST(s21ArrayTest, ArrayAtIndex) {
  s21::array<std::string, 5> str_arr = {"aa", "bb", "cc", "dd", "ee"};
  str_arr.at(3) = "XX";
  EXPECT_EQ(str_arr.at(0), "aa");
  EXPECT_EQ(str_arr.at(1), "bb");
  EXPECT_EQ(str_arr.at(2), "cc");
  EXPECT_EQ(str_arr.at(3), "XX");
  EXPECT_EQ(str_arr.at(4), "ee");

  EXPECT_THROW(str_arr.at(10), std::out_of_range);
}

TEST(s21ArrayTest, ArrayConstAtIndex) {
  const s21::array<std::string, 5> str_arr = {"aa", "bb", "cc", "dd", "ee"};
  EXPECT_EQ(str_arr.at(0), "aa");
  EXPECT_EQ(str_arr.at(1), "bb");
  EXPECT_EQ(str_arr.at(2), "cc");
  EXPECT_EQ(str_arr.at(3), "dd");
  EXPECT_EQ(str_arr.at(4), "ee");
  EXPECT_THROW(str_arr.at(10), std::out_of_range);
}

TEST(s21ArrayTest, ArrayAtIndexBraces) {
  s21::array<std::string, 5> str_arr = {"aa", "bb", "cc", "dd", "ee"};
  str_arr[3] = "XX";
  EXPECT_EQ(str_arr[0], "aa");
  EXPECT_EQ(str_arr[1], "bb");
  EXPECT_EQ(str_arr[2], "cc");
  EXPECT_EQ(str_arr[3], "XX");
  EXPECT_EQ(str_arr[4], "ee");
  EXPECT_THROW(str_arr[10], std::out_of_range);
}

TEST(s21ArrayTest, ArrayConstAtIndexBraces) {
  const s21::array<std::string, 5> str_arr = {"aa", "bb", "cc", "dd", "ee"};
  EXPECT_EQ(str_arr[0], "aa");
  EXPECT_EQ(str_arr[1], "bb");
  EXPECT_EQ(str_arr[2], "cc");
  EXPECT_EQ(str_arr[3], "dd");
  EXPECT_EQ(str_arr[4], "ee");
  EXPECT_THROW(str_arr[10], std::out_of_range);
}

TEST(s21ArrayTest, ArrayFrontTest) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  int front_val = arr.front();
  EXPECT_EQ(front_val, 1);
}

TEST(s21ArrayTest, ArrayBackTest) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(arr.back(), 5);
}

TEST(s21ArrayTest, ArrayEmptyFrontBackTest) {
  s21::array<int, 0> arr;
  EXPECT_THROW(arr.front(), std::logic_error);
  EXPECT_THROW(arr.back(), std::logic_error);
}

TEST(s21ArrayTest, ArrayDataTest) {
  s21::array<std::string, 4> s21_arr = {"aa", "bb", "cc"};
  std::array<std::string, 4> std_arr = {"aa", "bb", "cc"};
  s21_arr.data()[0] = "XX";
  std_arr.data()[0] = "XX";
  EXPECT_EQ(s21_arr.data()[0], "XX");
  EXPECT_EQ(std_arr.data()[0], s21_arr.data()[0]);
}

TEST(s21ArrayTest, ArrayConstDataTest) {
  const s21::array<std::string, 4> s21_arr = {"aa", "bb", "cc"};
  const std::array<std::string, 4> std_arr = {"aa", "bb", "cc"};
  EXPECT_EQ(s21_arr.data()[0], "aa");
  EXPECT_EQ(std_arr.data()[0], s21_arr.data()[0]);
}

TEST(s21ArrayTest, IteratorBeginTest) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  int* beginIter = arr.begin();
  EXPECT_EQ(*beginIter, 1);
  *beginIter = 10;
  EXPECT_EQ(*beginIter, 10);
  beginIter++;
  EXPECT_EQ(*beginIter, 2);
  beginIter += 2;
  EXPECT_EQ(*beginIter, 4);
}

TEST(s21ArrayTest, IteratorEndTest) {
  s21::array<int, 5> arr = {5, 6, 7, 8, 9};
  int* endIter = arr.end();
  endIter--;
  endIter--;
  EXPECT_EQ(*endIter, 8);
}

TEST(s21ArrayTest, ConstIteratorBeginTest) {
  const s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  const int* beginIter = arr.cbegin();
  EXPECT_EQ(*beginIter, 1);
}

TEST(s21ArrayTest, ConstIteratorEndTest) {
  const s21::array<int, 0> empty = {};
  const int* endIter = empty.cend();
  const int* beginIter = empty.cbegin();
  EXPECT_EQ(*endIter, *beginIter);
}

TEST(s21ArrayTest, ComparisonTest) {
  s21::array<std::string, 5> str_arr = {"aa", "bb", "cc", "dd", "ee"};
  s21::array<std::string, 5> str_arr2 = {"aa", "bb", "cc", "dd", "ee"};

  EXPECT_TRUE(str_arr == str_arr2);
}

TEST(s21ArrayTest, ComparisonTest2) {
  s21::array<std::string, 5> str_arr = {"aa", "bb", "cc", "dd", "ee"};
  s21::array<std::string, 5> str_arr2 = {"aa", "bb", "cc", "dd", "XX"};

  EXPECT_FALSE(str_arr == str_arr2);
}

TEST(s21ArrayTest, NotEqualTest) {
  s21::array<std::string, 5> str_arr = {"aa", "bb", "cc", "dd", "ee"};
  s21::array<std::string, 5> str_arr2 = {"aa", "bb", "cc", "dd", "XX"};

  EXPECT_TRUE(str_arr != str_arr2);
}

TEST(s21ArrayTest, OneObjectCompareTest) {
  s21::array<std::string, 5> str_arr = {"aa", "bb", "cc", "dd", "ee"};
  EXPECT_TRUE(str_arr == str_arr);
}

TEST(s21ArrayTest, ArraySwapTest) {
  s21::array<std::string, 5> str_arr = {"aa", "bb", "cc", "dd", "ee"};
  s21::array<std::string, 5> str_arr2 = {"ff", "gg", "hh", "ii", "jj"};

  str_arr.swap(str_arr2);

  EXPECT_EQ(str_arr2[0], "aa");
  EXPECT_EQ(str_arr2[1], "bb");
  EXPECT_EQ(str_arr2[2], "cc");
  EXPECT_EQ(str_arr2[3], "dd");
  EXPECT_EQ(str_arr2[4], "ee");
}

TEST(s21ArrayTest, ArrayFillTest) {
  s21::array<double, 5> arr;
  arr.fill(6.9);
  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(arr[i], 6.9);
  }
}

TEST(s21ArrayTest, MatrixTypeTest) {
  s21::array<s21::S21Matrix, 5> m;
  std::array<s21::S21Matrix, 5> stdm;
  for (int i = 0; i < 5; i++) {
    m[i].set_rows(2);
    m[i].set_cols(2);
    stdm[i].set_rows(2);
    stdm[i].set_cols(2);
    m[i](0, 0) = 5.0;
    m[i](0, 1) = 6.0;
    m[i](1, 0) = 7.0;
    m[i](1, 1) = 8.0;

    stdm[i](0, 0) = 5.0;
    stdm[i](0, 1) = 6.0;
    stdm[i](1, 0) = 7.0;
    stdm[i](1, 1) = 8.0;
  }
}

TEST(s21ArrayTest, PairOfStringsTest) {
  s21::array<std::pair<std::string, std::string>, 5> m;
  std::array<std::pair<std::string, std::string>, 5> stdm;
  m[0] = {"aa", "bb"};
  m[1] = {"cc", "dd"};
  m[2] = {"ee", "ff"};
  m[3] = {"gg", "hh"};
  m[4] = {"ii", "jj"};

  stdm[0] = {"aa", "bb"};
  stdm[1] = {"cc", "dd"};
  stdm[2] = {"ee", "ff"};
  stdm[3] = {"gg", "hh"};
  stdm[4] = {"ii", "jj"};

  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(m[i], stdm[i]);
  }
}