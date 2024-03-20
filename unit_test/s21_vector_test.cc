#include <exception>
#include <vector>

#include "s21_containers_test.h"

void printVector(const std::vector<int>& vec) {
  for (const auto& element : vec) {
    std::cout << element << " ";
  }
  std::cout << std::endl;
}

void printVectorValueAndAdress(const std::vector<int>& vec) {
  for (const auto& element : vec) {
    std::cout << &element << " = " << element << " ";
  }
  std::cout << std::endl;
}

// Vector Member functions
TEST(Vector_Constructor,
     VectorDefualtConstructor_ObjectTypeListWhenArgNullptr) {
  std::vector<int> vector;
  s21::vector<int> s21_vector;

  EXPECT_EQ(vector.empty(), s21_vector.empty());
  EXPECT_EQ(vector.size(), s21_vector.size());
  EXPECT_EQ(vector.max_size(), s21_vector.max_size());
  EXPECT_EQ(vector.capacity(), s21_vector.capacity());
}

TEST(Vector_Constructor, VectorInitializerListConstructor_ObjectEmpty) {
  std::vector<int> vector{};
  s21::vector<int> s21_vector{};

  EXPECT_EQ(vector.empty(), s21_vector.empty());
  EXPECT_EQ(vector.size(), s21_vector.size());
  EXPECT_EQ(vector.max_size(), s21_vector.max_size());
  EXPECT_EQ(vector.capacity(), s21_vector.capacity());
}

TEST(Vector_Constructor, VectorInitializerListConstructor_ObjectWithOneArg) {
  std::vector<int> vector{1};
  s21::vector<int> s21_vector{1};

  EXPECT_EQ(*vector.data(), *s21_vector.data());
  EXPECT_EQ(vector.empty(), s21_vector.empty());
  EXPECT_EQ(vector.size(), s21_vector.size());
  EXPECT_EQ(vector.max_size(), s21_vector.max_size());
  EXPECT_EQ(vector.capacity(), s21_vector.capacity());
}

TEST(Vector_Constructor, VectorInitializerListConstructor_ObjectWithTwoArg) {
  std::vector<int> vector{1, 2, 3, 4};
  s21::vector<int> s21_vector{1, 2, 3, 4};

  EXPECT_EQ(*vector.data(), *s21_vector.data());
  EXPECT_EQ(*(vector.data() + 1), *(s21_vector.data() + 1));
  EXPECT_EQ(*(vector.data() + 2), *(s21_vector.data() + 2));
  EXPECT_EQ(*(vector.data() + 3), *(s21_vector.data() + 3));

  EXPECT_EQ(vector.empty(), s21_vector.empty());
  EXPECT_EQ(vector.size(), s21_vector.size());
  EXPECT_EQ(vector.max_size(), s21_vector.max_size());
  EXPECT_EQ(vector.capacity(), s21_vector.capacity());
}

TEST(Vector_Constructor, VectorCopyConstructor_CopyObjectWithNullhArg) {
  std::vector<int> vector_00;
  s21::vector<int> s21_vector_00;

  std::vector<int> vector_01 = vector_00;
  s21::vector<int> s21_vector_01(s21_vector_00);

  EXPECT_EQ(vector_01.empty(), s21_vector_01.empty());
  EXPECT_EQ(vector_01.size(), s21_vector_01.size());
  EXPECT_EQ(vector_01.max_size(), s21_vector_01.max_size());
  EXPECT_EQ(vector_01.capacity(), s21_vector_01.capacity());
}

TEST(Vector_Constructor, VectorCopyConstructor_CopyObjectOnehTwoArg) {
  std::vector<int> vector_00 = {1};
  s21::vector<int> s21_vector_00 = {1};

  std::vector<int> vector_01 = vector_00;
  s21::vector<int> s21_vector_01(s21_vector_00);

  EXPECT_EQ(vector_01.empty(), s21_vector_01.empty());
  EXPECT_EQ(vector_01.size(), s21_vector_01.size());
  EXPECT_EQ(vector_01.max_size(), s21_vector_01.max_size());
  EXPECT_EQ(vector_01.capacity(), s21_vector_01.capacity());

  EXPECT_EQ(*vector_01.data(), *s21_vector_01.data());
  EXPECT_EQ(*vector_01.data(), *s21_vector_01.data());
}

TEST(Vector_Constructor, VectorCopyConstructor_CopyObjectTwoTwoArg) {
  std::vector<int> vector_00 = {1, 2};
  s21::vector<int> s21_vector_00 = {1, 2};

  std::vector<int> vector_01 = vector_00;
  s21::vector<int> s21_vector_01(s21_vector_00);

  EXPECT_EQ(vector_01.empty(), s21_vector_01.empty());
  EXPECT_EQ(vector_01.size(), s21_vector_01.size());
  EXPECT_EQ(vector_01.max_size(), s21_vector_01.max_size());
  EXPECT_EQ(vector_01.capacity(), s21_vector_01.capacity());

  EXPECT_EQ(*vector_01.data(), *s21_vector_01.data());
  EXPECT_EQ(*(vector_01.data() + 1), *(s21_vector_01.data() + 1));
}

TEST(Vector_Constructor, VectorMoveConstructor_MoveObjectWithNullArg) {
  std::vector<int> vector_00 = {};
  s21::vector<int> s21_vector_00 = {};

  std::vector<int> vector_01 = std::move(vector_00);
  s21::vector<int> s21_vector_01 = std::move(s21_vector_00);

  EXPECT_EQ(vector_01.empty(), s21_vector_01.empty());
  EXPECT_EQ(vector_01.size(), s21_vector_01.size());
  EXPECT_EQ(vector_01.max_size(), s21_vector_01.max_size());
  EXPECT_EQ(vector_01.capacity(), s21_vector_01.capacity());

  EXPECT_EQ(vector_01.data(), nullptr);
  EXPECT_EQ(s21_vector_01.data(), nullptr);
}

TEST(Vector_Constructor, VectorMoveConstructor_MoveObjectWithOneArg) {
  std::vector<int> vector_00 = {1};
  s21::vector<int> s21_vector_00 = {1};

  int* array_vector_00 = vector_00.data();
  int* array_s21_vector_00 = s21_vector_00.data();

  std::vector<int> vector_01 = std::move(vector_00);
  s21::vector<int> s21_vector_01 = std::move(s21_vector_00);

  EXPECT_EQ(vector_01.empty(), s21_vector_01.empty());
  EXPECT_EQ(vector_01.size(), s21_vector_01.size());
  EXPECT_EQ(vector_01.max_size(), s21_vector_01.max_size());
  EXPECT_EQ(vector_01.capacity(), s21_vector_01.capacity());

  EXPECT_EQ(s21_vector_00.data(), nullptr);
  EXPECT_EQ(vector_00.data(), nullptr);

  EXPECT_EQ(s21_vector_01.data(), array_s21_vector_00);
  EXPECT_EQ(vector_01.data(), array_vector_00);

  EXPECT_EQ(*(s21_vector_01.data()), 1);
  EXPECT_EQ(*(vector_01.data()), 1);
}

TEST(Vector_Constructor, VectorMoveConstructor_MoveObjectWithTwoArg) {
  std::vector<int> vector_00 = {1, 2};
  s21::vector<int> s21_vector_00 = {1, 2};

  int* array_vector_00 = vector_00.data();
  int* array_s21_vector_00 = s21_vector_00.data();

  std::vector<int> vector_01 = std::move(vector_00);
  s21::vector<int> s21_vector_01 = std::move(s21_vector_00);

  EXPECT_EQ(vector_01.empty(), s21_vector_01.empty());
  EXPECT_EQ(vector_01.size(), s21_vector_01.size());
  EXPECT_EQ(vector_01.max_size(), s21_vector_01.max_size());
  EXPECT_EQ(vector_01.capacity(), s21_vector_01.capacity());

  EXPECT_EQ(s21_vector_00.data(), nullptr);
  EXPECT_EQ(vector_00.data(), nullptr);

  EXPECT_EQ(s21_vector_01.data(), array_s21_vector_00);
  EXPECT_EQ(vector_01.data(), array_vector_00);

  EXPECT_EQ(*(s21_vector_01.data()), 1);
  EXPECT_EQ(*(vector_01.data()), 1);

  EXPECT_EQ(*(s21_vector_01.data() + 1), 2);
  EXPECT_EQ(*(vector_01.data() + 1), 2);
}

// Vector Iterators

TEST(Vector_Iterator, VectorIteratorAllFunction) {
  std::vector<int> vector_00 = {1, 2, 3};
  s21::vector<int> s21_vector_00 = {1, 2, 3};

  EXPECT_EQ(*vector_00.begin(), 1);
  EXPECT_EQ(*s21_vector_00.begin(), 1);

  EXPECT_EQ(*vector_00.begin() + 1, 2);
  EXPECT_EQ(*s21_vector_00.begin() + 1, 2);

  EXPECT_EQ(*vector_00.begin() + 2, 3);
  EXPECT_EQ(*s21_vector_00.begin() + 2, 3);

  EXPECT_EQ(*(vector_00.begin()++), 1);
  EXPECT_EQ(*(s21_vector_00.begin()++), 1);

  EXPECT_EQ(*(++vector_00.begin()), 2);
  EXPECT_EQ(*(++s21_vector_00.begin()), 2);

  EXPECT_EQ(*(vector_00.end() - 1), 3);
  EXPECT_EQ(*(s21_vector_00.end() - 1), 3);

  EXPECT_EQ(vector_00.end(), (vector_00.begin() + 3));
  EXPECT_EQ(s21_vector_00.end(), (s21_vector_00.begin() + 3));

  EXPECT_EQ((vector_00.end()--), (vector_00.begin() + 3));
  EXPECT_EQ((s21_vector_00.end()--), (s21_vector_00.begin() + 3));

  EXPECT_EQ(*(--vector_00.end()), 3);
  EXPECT_EQ(*(--s21_vector_00.end()), 3);

  EXPECT_EQ(s21_vector_00.end() < --s21_vector_00.end(), false);
  EXPECT_EQ(s21_vector_00.end() == s21_vector_00.end(), true);
  EXPECT_EQ(s21_vector_00.end() != --s21_vector_00.end(), true);
}
// Vector Element access
TEST(Vector_Capacity, VectorAtThrow) {
  std::vector<int> vector_00 = {1, 2, 3};
  s21::vector<int> s21_vector_00 = {1, 2, 3};

  std::vector<int> vector_01 = {};
  s21::vector<int> s21_vector_01 = {};

  EXPECT_ANY_THROW(vector_01.at(0));
  EXPECT_ANY_THROW(s21_vector_01.at(0));

  EXPECT_ANY_THROW(vector_00.at(5));
  EXPECT_ANY_THROW(s21_vector_00.at(5));

  EXPECT_EQ(vector_00.at(0), 1);
  EXPECT_EQ(s21_vector_00.at(0), 1);

  EXPECT_EQ(vector_00.at(1), 2);
  EXPECT_EQ(s21_vector_00.at(1), 2);

  EXPECT_EQ(vector_00.at(2), 3);
  EXPECT_EQ(s21_vector_00.at(2), 3);
}

TEST(Vector_Capacity, VectorFrontAndBack) {
  std::vector<int> vector_00 = {1, 2, 3};
  s21::vector<int> s21_vector_00 = {1, 2, 3};

  std::vector<int> vector_01 = {};
  s21::vector<int> s21_vector_01 = {};

  EXPECT_EQ(vector_00.front(), 1);
  EXPECT_EQ(s21_vector_00.front(), 1);

  EXPECT_EQ(vector_00.back(), 3);
  EXPECT_EQ(s21_vector_00.back(), 3);

  EXPECT_ANY_THROW(s21_vector_01.front());
  EXPECT_ANY_THROW(s21_vector_01.back());
}

TEST(Vector_Capacity, VectorData) {
  std::vector<int> vector_00 = {1, 2, 3};
  s21::vector<int> s21_vector_00 = {1, 2, 3};

  std::vector<int> vector_01 = {};
  s21::vector<int> s21_vector_01 = {};

  auto iterVector_00 = vector_00.begin().base();
  int* iterS21_vector_00 = s21_vector_00.getPointerBegin();

  EXPECT_EQ(vector_00.data(), iterVector_00);
  EXPECT_EQ(s21_vector_00.data(), iterS21_vector_00);
}

TEST(Vector_Capacity, VectorOperator) {
  std::vector<int> vector_00 = {1, 2, 3};

  EXPECT_EQ(vector_00[0], 1);
  EXPECT_EQ(vector_00[0], 1);

  EXPECT_EQ(vector_00[1], 2);
  EXPECT_EQ(vector_00[1], 2);

  EXPECT_EQ(vector_00[2], 3);
  EXPECT_EQ(vector_00[2], 3);
}

// Vector Capacity
TEST(Vector_Capacity, AllVariantCombinations_Part_1) {
  std::vector<int> vector;
  s21::vector<int> s21_vector;

  EXPECT_EQ(vector.empty(), s21_vector.empty());
  EXPECT_EQ(vector.size(), s21_vector.size());
  EXPECT_EQ(vector.max_size(), s21_vector.max_size());
  EXPECT_EQ(vector.capacity(), s21_vector.capacity());

  vector.reserve(10);
  s21_vector.reserve(10);

  EXPECT_EQ(vector.empty(), s21_vector.empty());
  EXPECT_EQ(vector.size(), s21_vector.size());
  EXPECT_EQ(vector.capacity(), s21_vector.capacity());

  vector.shrink_to_fit();
  s21_vector.shrink_to_fit();

  EXPECT_EQ(vector.empty(), s21_vector.empty());
  EXPECT_EQ(vector.size(), s21_vector.size());
  EXPECT_EQ(vector.capacity(), s21_vector.capacity());
}

TEST(Vector_Capacity, AllVariantCombinations_Part_2) {
  std::vector<int> vector;
  s21::vector<int> s21_vector;

  vector.push_back(1);
  vector.push_back(2);

  s21_vector.push_back(1);
  s21_vector.push_back(2);

  EXPECT_EQ(vector.empty(), s21_vector.empty());
  EXPECT_EQ(vector.size(), s21_vector.size());
  EXPECT_EQ(vector.max_size(), s21_vector.max_size());
  EXPECT_EQ(vector.capacity(), s21_vector.capacity());

  vector.reserve(10);
  s21_vector.reserve(10);

  EXPECT_EQ(vector.empty(), s21_vector.empty());
  EXPECT_EQ(vector.size(), s21_vector.size());
  EXPECT_EQ(vector.capacity(), s21_vector.capacity());

  vector.shrink_to_fit();
  s21_vector.shrink_to_fit();

  EXPECT_EQ(vector.empty(), s21_vector.empty());
  EXPECT_EQ(vector.size(), s21_vector.size());
  EXPECT_EQ(vector.capacity(), s21_vector.capacity());
}

TEST(Vector_Capacity, AllVariantCombinations_CheckListVector_1) {
  s21::vector<int> s21_vector;

  s21_vector.push_back(1);
  s21_vector.push_back(2);

  s21_vector.reserve(10);

  int* A = s21_vector.getPointerBegin();

  s21_vector.shrink_to_fit();

  int* B = s21_vector.getPointerBegin();

  EXPECT_NE(A, B);
}

TEST(Vector_Capacity, Reserve) {
  s21::vector<int> s21_vector{1, 2, 3};

  EXPECT_EQ(*s21_vector.data(), 1);
  EXPECT_EQ(*(s21_vector.data() + 1), 2);
  EXPECT_EQ(*(s21_vector.data() + 2), 3);

  s21_vector.reserve(10);

  EXPECT_EQ(*s21_vector.data(), 1);
  EXPECT_EQ(*(s21_vector.data() + 1), 2);
  EXPECT_EQ(*(s21_vector.data() + 2), 3);

  int* A = s21_vector.getPointerBegin();

  s21_vector.shrink_to_fit();

  int* B = s21_vector.getPointerBegin();

  EXPECT_NE(A, B);
}

TEST(Vector_Capacity, ReserveThrow) {
  s21::vector<int> s21_vector{1, 2, 3, 4, 5};
  EXPECT_ANY_THROW(s21_vector.reserve(s21_vector.max_size() + 1));
}

TEST(Vector_Capacity, ReserveReturn) {
  s21::vector<int> s21_vector{1, 2, 3, 4, 5};

  size_t size = s21_vector.size();
  size_t capacity = s21_vector.capacity();

  s21_vector.reserve(2);

  EXPECT_EQ(s21_vector.size(), size);
  EXPECT_EQ(s21_vector.capacity(), capacity);
}

// Vector Modifiers
TEST(Vector_Capacity, VectorClear) {
  std::vector<int> vector{1, 2, 3};
  s21::vector<int> s21_vector{1, 2, 3};

  vector.clear();
  s21_vector.clear();

  EXPECT_EQ(vector.empty(), s21_vector.empty());
  EXPECT_EQ(vector.size(), s21_vector.size());
  EXPECT_EQ(vector.max_size(), s21_vector.max_size());
  EXPECT_EQ(vector.capacity(), s21_vector.capacity());

  std::vector<int> vector_00{};
  s21::vector<int> s21_vector_00{};

  vector_00.clear();
  s21_vector_00.clear();

  EXPECT_EQ(vector_00.empty(), s21_vector_00.empty());
  EXPECT_EQ(vector_00.size(), s21_vector_00.size());
  EXPECT_EQ(vector_00.max_size(), s21_vector_00.max_size());
  EXPECT_EQ(vector_00.capacity(), s21_vector_00.capacity());
}

TEST(Vector_Capacity, VectorInsert) {
  std::vector<int> vector{1, 2, 3};
  s21::vector<int> s21_vector{1, 2, 3};

  vector.reserve(10);
  s21_vector.reserve(10);

  auto iterVector_00 = vector.insert(vector.begin(), 4);
  EXPECT_EQ(4, *vector.data());
  EXPECT_EQ(vector.begin(), iterVector_00);

  auto iters21_Vector_00 = s21_vector.insert(s21_vector.begin(), 4);
  EXPECT_EQ(4, *s21_vector.data());
  EXPECT_EQ(s21_vector.begin(), iters21_Vector_00);

  auto iterVector_01 = vector.insert(vector.begin() + 2, 5);
  EXPECT_EQ(5, *(vector.data() + 2));
  EXPECT_EQ(vector.begin() + 2, iterVector_01);

  auto iters21_Vector_01 = s21_vector.insert(s21_vector.begin() + 2, 5);
  EXPECT_EQ(5, *(s21_vector.data() + 2));
  EXPECT_EQ(s21_vector.begin() + 2, iters21_Vector_01);

  auto iterVector_02 = vector.insert(--vector.end(), 6);
  EXPECT_EQ(6, *(vector.data() + 4));
  EXPECT_EQ(vector.begin() + 4, iterVector_02);

  auto iters21_Vector_02 = s21_vector.insert(--s21_vector.end(), 6);
  EXPECT_EQ(6, *(s21_vector.data() + 4));
  EXPECT_EQ(s21_vector.begin() + 4, iters21_Vector_02);
}

TEST(Vector_Capacity, VectorInsert_01) {
  std::vector<int> vector{};
  s21::vector<int> s21_vector{};

  vector.reserve(10);
  s21_vector.reserve(10);

  auto iterVector_00 = vector.insert(vector.begin(), 4);
  EXPECT_EQ(4, *vector.data());
  EXPECT_EQ(vector.begin(), iterVector_00);

  auto iters21_Vector_00 = s21_vector.insert(s21_vector.begin(), 4);
  EXPECT_EQ(4, *s21_vector.data());
  EXPECT_EQ(s21_vector.begin(), iters21_Vector_00);
}

TEST(Vector_Capacity, VectorInsert_02) {
  std::vector<int> vector{};
  s21::vector<int> s21_vector{};

  vector.reserve(10);
  s21_vector.reserve(10);

  auto iterVector_00 = vector.insert(vector.end(), 4);
  EXPECT_EQ(4, *vector.data());
  EXPECT_EQ(vector.begin(), iterVector_00);

  auto iters21_Vector_00 = s21_vector.insert(s21_vector.end(), 4);
  EXPECT_EQ(4, *s21_vector.data());
  EXPECT_EQ(s21_vector.begin(), iters21_Vector_00);
}

TEST(Vector_Capacity, VectorErase) {
  std::vector<int> vector{1, 2, 3, 4, 5};
  s21::vector<int> s21_vector{1, 2, 3, 4, 5};

  vector.erase(vector.begin());
  s21_vector.erase(s21_vector.begin());

  EXPECT_EQ(*vector.data(), 2);
  EXPECT_EQ(*s21_vector.data(), 2);

  vector.erase(vector.end() - 1);
  s21_vector.erase(s21_vector.end() - 1);
  EXPECT_EQ(*(vector.data() + 2), 4);
  EXPECT_EQ(*(s21_vector.data() + 2), 4);

  vector.erase(vector.begin());
  s21_vector.erase(s21_vector.begin());
  EXPECT_EQ(*(vector.data()), 3);
  EXPECT_EQ(*(s21_vector.data()), 3);

  vector.erase(vector.begin());
  s21_vector.erase(s21_vector.begin());
  EXPECT_EQ(*(vector.data()), 4);
  EXPECT_EQ(*(s21_vector.data()), 4);

  EXPECT_EQ(s21_vector.empty(), vector.empty());
}

TEST(Vector_Capacity, VectorEraseAndReverce) {
  std::vector<int> vector{1, 2, 3, 4, 5};
  s21::vector<int> s21_vector{1, 2, 3, 4, 5};

  vector.reserve(10);
  s21_vector.reserve(10);

  vector.erase(vector.begin());
  s21_vector.erase(s21_vector.begin());
  EXPECT_EQ(*vector.data(), 2);
  EXPECT_EQ(*s21_vector.data(), 2);

  vector.erase(vector.end() - 1);
  s21_vector.erase(s21_vector.end() - 1);
  EXPECT_EQ(*(vector.data() + 2), 4);
  EXPECT_EQ(*(s21_vector.data() + 2), 4);

  vector.erase(vector.begin());
  s21_vector.erase(s21_vector.begin());
  EXPECT_EQ(*(vector.data()), 3);
  EXPECT_EQ(*(s21_vector.data()), 3);

  vector.erase(vector.begin());
  s21_vector.erase(s21_vector.begin());
  EXPECT_EQ(*(vector.data()), 4);
  EXPECT_EQ(*(s21_vector.data()), 4);

  EXPECT_EQ(s21_vector.empty(), vector.empty());
}

TEST(Vector_Capacity, VectorPushBack) {
  std::vector<int> vector{1, 2, 3, 4, 5};
  s21::vector<int> s21_vector{1, 2, 3, 4, 5};

  vector.push_back(6);
  s21_vector.push_back(6);

  EXPECT_EQ(*(vector.data() + 5), 6);
  EXPECT_EQ(*(s21_vector.data() + 5), 6);

  vector.reserve(10);
  s21_vector.reserve(10);

  vector.push_back(7);
  s21_vector.push_back(7);

  EXPECT_EQ(*(vector.data() + 6), 7);
  EXPECT_EQ(*(s21_vector.data() + 6), 7);

  vector.shrink_to_fit();
  s21_vector.shrink_to_fit();

  vector.push_back(8);
  s21_vector.push_back(8);

  EXPECT_EQ(*(vector.data() + 7), 8);
  EXPECT_EQ(*(s21_vector.data() + 7), 8);
}

TEST(Vector_Capacity, VectorPopBack) {
  std::vector<int> vector{1, 2, 3, 4, 5};
  s21::vector<int> s21_vector{1, 2, 3, 4, 5};

  vector.pop_back();
  s21_vector.pop_back();

  EXPECT_EQ(*(vector.data() + 3), 4);
  EXPECT_EQ(*(s21_vector.data() + 3), 4);

  vector.reserve(10);
  s21_vector.reserve(10);

  vector.pop_back();
  s21_vector.pop_back();

  EXPECT_EQ(*(vector.data() + 2), 3);
  EXPECT_EQ(*(s21_vector.data() + 2), 3);
}

TEST(Vector_Capacity, VectorSwap) {
  std::vector<int> vector{1, 2, 3, 4, 5};
  std::vector<int> vector_sw{5, 4, 3, 2, 1};

  vector.reserve(10);

  s21::vector<int> s21_vector{1, 2, 3, 4, 5};
  s21::vector<int> s21_vector_sw{5, 4, 3, 2, 1};

  s21_vector.reserve(10);

  vector_sw.swap(vector);
  s21_vector_sw.swap(s21_vector);

  EXPECT_EQ(*(vector.data()), 5);
  EXPECT_EQ(*(s21_vector.data()), 5);

  EXPECT_EQ(vector.empty(), s21_vector.empty());
  EXPECT_EQ(vector.size(), s21_vector.size());
  EXPECT_EQ(vector.max_size(), s21_vector.max_size());
  EXPECT_EQ(vector.capacity(), s21_vector.capacity());
}

TEST(Vector_Capacity, VectorInsertMany) {
  s21::vector<int> s21_vector{1, 2, 3};
  s21_vector.reserve(25);
  auto iter = s21_vector.insert_many(s21_vector.cbegin(), 1, 2, 3);
  EXPECT_EQ(false, s21_vector.empty());
  EXPECT_EQ(6, s21_vector.size());
  EXPECT_EQ(*s21_vector.begin(), 1);
  EXPECT_EQ(*(--s21_vector.end()), 3);
  EXPECT_EQ(*iter, 3);
}

TEST(Vector_Capacity, VectorInsertMany_01) {
  s21::vector<int> s21_vector{};
  s21_vector.reserve(10);
  auto iter = s21_vector.insert_many(s21_vector.cbegin(), 1);
  EXPECT_EQ(false, s21_vector.empty());
  EXPECT_EQ(1, s21_vector.size());
  EXPECT_EQ(*s21_vector.begin(), 1);
  EXPECT_EQ(*(--s21_vector.end()), 1);
  EXPECT_EQ(*iter, 1);
}

TEST(Vector_Capacity, VectorInsertManyBack) {
  s21::vector<int> s21_vector{1};

  s21_vector.reserve(25);

  s21_vector.insert_many_back(2, 3);

  EXPECT_EQ(s21_vector.empty(), false);
  EXPECT_EQ(*s21_vector.begin(), 1);
  EXPECT_EQ(*(--s21_vector.end()), 3);
  EXPECT_EQ(s21_vector.size(), 3);
}

TEST(Vector_Capacity, VectorInsertManyBack_01) {
  s21::vector<int> s21_vector{};

  s21_vector.reserve(25);

  s21_vector.insert_many_back(1, 2, 3);

  EXPECT_EQ(s21_vector.empty(), false);
  EXPECT_EQ(*s21_vector.begin(), 1);
  EXPECT_EQ(*(--s21_vector.end()), 3);
  EXPECT_EQ(s21_vector.size(), 3);
}

TEST(Vector_Capacity, VectorInsertManyBack_02) {
  s21::vector<int> s21_vector{0, 1, 2};

  s21_vector.reserve(25);

  s21_vector.insert_many_back(1, 2, 3);

  EXPECT_EQ(s21_vector.empty(), false);
  EXPECT_EQ(*s21_vector.begin(), 0);
  EXPECT_EQ(*(--s21_vector.end()), 3);
  EXPECT_EQ(s21_vector.size(), 6);
}
