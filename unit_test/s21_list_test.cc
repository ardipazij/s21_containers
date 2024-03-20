#include <list>

#include "s21_containers_test.h"

// List Functions
TEST(List_Constructor, ListConstructor_ObjectTypeListWhenArgNullptr) {
  std::list<int> list;
  s21::list<int> s21_list;

  EXPECT_EQ(list.empty(), true);
  EXPECT_EQ(s21_list.empty(), true);

  EXPECT_EQ(list.size(), 0);
  EXPECT_EQ(s21_list.size(), 0);

  EXPECT_EQ(list.size(), 0);
  EXPECT_EQ(s21_list.size(), 0);

  EXPECT_EQ(s21_list.getPointHead(), nullptr);
  EXPECT_EQ(s21_list.getPointTail(), nullptr);
}

TEST(List_Constructor, ListConstructorSizeN) {
  std::list<int> list(10);
  s21::list<int> s21_list(10);

  EXPECT_EQ(list.empty(), false);
  EXPECT_EQ(s21_list.empty(), false);

  EXPECT_EQ(list.size(), 10);
  EXPECT_EQ(s21_list.size(), 10);
}

TEST(List_Constructor, ListInitializerList) {
  std::list<int> list{1, 2, 3};
  s21::list<int> s21_list{1, 2, 3};

  EXPECT_EQ(list.empty(), false);
  EXPECT_EQ(s21_list.empty(), false);

  EXPECT_EQ(list.size(), 3);
  EXPECT_EQ(s21_list.size(), 3);

  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(s21_list.front(), 1);

  EXPECT_EQ(list.front() + 1, 2);
  EXPECT_EQ(s21_list.front() + 1, 2);

  EXPECT_EQ(list.front() + 2, 3);
  EXPECT_EQ(s21_list.front() + 2, 3);

  std::list<int> list_00{};
  s21::list<int> s21_list_00{};

  EXPECT_EQ(list_00.empty(), true);
  EXPECT_EQ(s21_list_00.empty(), true);

  EXPECT_EQ(list_00.size(), 0);
  EXPECT_EQ(s21_list_00.size(), 0);
}

TEST(List_Constructor, ListRevers) {
  std::list<int> list{1, 2, 3, 4, 5};
  s21::list<int> s21_list{1, 2, 3, 4, 5};

  auto iterListBegin = list.begin();
  auto iterListEnd = --list.end();

  auto iterS21_ListBegin = s21_list.begin();
  auto iterS21_ListEnd = --s21_list.end();

  list.reverse();
  s21_list.reverse();

  EXPECT_EQ(*iterListBegin, 1);
  EXPECT_EQ(*iterListEnd, 5);
  EXPECT_EQ(*iterS21_ListBegin, 1);
  EXPECT_EQ(*iterS21_ListEnd, 5);
}

TEST(List_Constructor, ListRevers_01) {
  std::list<int> list{1};
  s21::list<int> s21_list{1};

  auto iterListBegin = list.begin();
  auto iterListEnd = --list.end();

  auto iterS21_ListBegin = s21_list.begin();
  auto iterS21_ListEnd = --s21_list.end();

  list.reverse();
  s21_list.reverse();

  EXPECT_EQ(*iterListBegin, 1);
  EXPECT_EQ(*iterListEnd, 1);
  EXPECT_EQ(*iterS21_ListBegin, 1);
  EXPECT_EQ(*iterS21_ListEnd, 1);
}

TEST(List_Constructor, ListRevers_02) {
  std::list<int> list{};
  s21::list<int> s21_list{};

  list.reverse();
  s21_list.reverse();
}

TEST(List_Constructor, ListCopy) {
  std::list<int> list{1, 2, 3};
  std::list<int> list_00(list);

  s21::list<int> s21_list{1, 2, 3};
  s21::list<int> s21_list_00(s21_list);

  EXPECT_EQ(list_00.size(), 3);
  EXPECT_EQ(s21_list.size(), 3);

  EXPECT_EQ(list_00.front(), 1);
  EXPECT_EQ(s21_list.front(), 1);

  EXPECT_EQ(list_00.front() + 1, 2);
  EXPECT_EQ(s21_list_00.front() + 1, 2);

  EXPECT_EQ(list_00.front() + 2, 3);
  EXPECT_EQ(s21_list_00.front() + 2, 3);
}

TEST(List_Constructor, ListMove) {
  std::list<int> list{1, 2, 3};
  std::list<int> list_00(std::move(list));

  s21::list<int> s21_list{1, 2, 3};
  s21::list<int> s21_list_00(std::move(s21_list));

  EXPECT_EQ(list_00.size(), 3);
  EXPECT_EQ(s21_list_00.size(), 3);

  EXPECT_EQ(list_00.front(), 1);
  EXPECT_EQ(s21_list_00.front(), 1);

  EXPECT_EQ(list_00.front() + 1, 2);
  EXPECT_EQ(s21_list_00.front() + 1, 2);

  EXPECT_EQ(list_00.front() + 2, 3);
  EXPECT_EQ(s21_list_00.front() + 2, 3);

  EXPECT_EQ(list.size(), 0);
  EXPECT_EQ(s21_list.size(), 0);

  EXPECT_EQ(s21_list.getPointHead(), nullptr);
  EXPECT_EQ(s21_list.getPointTail(), nullptr);
}

TEST(List_Constructor, ListMove_01) {
  std::list<int> list{1, 2, 3};
  std::list<int> list_00{3, 2, 1};

  list_00 = std::move(list);

  s21::list<int> s21_list{1, 2, 3};
  s21::list<int> s21_list_00{3, 2, 1};

  s21_list_00 = std::move(s21_list);

  EXPECT_EQ(list_00.size(), 3);
  EXPECT_EQ(s21_list_00.size(), 3);

  EXPECT_EQ(list_00.front(), 1);
  EXPECT_EQ(s21_list_00.front(), 1);

  EXPECT_EQ(list_00.front() + 1, 2);
  EXPECT_EQ(s21_list_00.front() + 1, 2);

  EXPECT_EQ(list_00.front() + 2, 3);
  EXPECT_EQ(s21_list_00.front() + 2, 3);

  EXPECT_EQ(list.size(), 0);
  EXPECT_EQ(s21_list.size(), 0);

  EXPECT_EQ(s21_list.getPointHead(), nullptr);
  EXPECT_EQ(s21_list.getPointTail(), nullptr);
}

// Vector Iterators
TEST(Vector_Iterator, ListIteratorAllFunction) {
  std::vector<int> vector_00 = {1, 2, 3};
  s21::list<int> s21_list_00 = {1, 2, 3};

  EXPECT_EQ(*vector_00.begin(), 1);
  EXPECT_EQ(*s21_list_00.begin(), 1);

  EXPECT_EQ(*vector_00.begin() + 1, 2);
  EXPECT_EQ(*s21_list_00.begin() + 1, 2);

  EXPECT_EQ(*vector_00.begin() + 2, 3);
  EXPECT_EQ(*s21_list_00.begin() + 2, 3);

  EXPECT_EQ(*(vector_00.begin()++), 1);
  EXPECT_EQ(*(s21_list_00.begin()++), 1);

  EXPECT_EQ(*(++vector_00.begin()), 2);
  EXPECT_EQ(*(++s21_list_00.begin()), 2);

  EXPECT_EQ(*(vector_00.end() - 1), 3);
  EXPECT_EQ(*(s21_list_00.end() - 1), 3);

  EXPECT_EQ(vector_00.end(), (vector_00.begin() + 3));
  EXPECT_EQ(s21_list_00.end(), (s21_list_00.begin() + 3));

  //    EXPECT_EQ(vector_00.end()--, (vector_00.begin() + 3));
  //    EXPECT_EQ(s21_list_00.end()--, (s21_list_00.begin() + 3));
  //
  EXPECT_EQ(*(--vector_00.end()), 3);
  EXPECT_EQ(*(--s21_list_00.end()), 3);

  EXPECT_EQ(s21_list_00.end() == s21_list_00.end(), true);
  EXPECT_EQ(s21_list_00.end() != --s21_list_00.end(), true);
}
// List Element access
TEST(List_Constructor, ListFront) {
  std::list<int> list{1, 2, 3};
  s21::list<int> s21_list{1, 2, 3};

  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(s21_list.front(), 1);
}

TEST(List_Constructor, ListBack) {
  std::list<int> list{1, 2, 3};
  s21::list<int> s21_list{1, 2, 3};

  EXPECT_EQ(list.back(), 3);
  EXPECT_EQ(s21_list.back(), 3);
}

// List Iterators
TEST(List_Constructor, ListBegin) {
  std::list<int> list{1, 2, 3};
  s21::list<int> s21_list{1, 2, 3};

  EXPECT_EQ(*list.begin(), 1);
  EXPECT_EQ(*s21_list.begin(), 1);

  std::list<int> list_00{};
  s21::list<int> s21_list_00{};
}

TEST(List_Constructor, ListEnd) {
  std::list<int> list{1, 2, 3};
  s21::list<int> s21_list{1, 2, 3};

  EXPECT_EQ(*(--list.end()), 3);
  EXPECT_EQ(*(--s21_list.end()), 3);

  std::list<int> list_00{};
  s21::list<int> s21_list_00{};
}

TEST(List_Constructor, ListCbegin) {
  std::list<int> list{1, 2, 3};
  s21::list<int> s21_list{1, 2, 3};

  EXPECT_EQ(*list.cbegin(), 1);
  EXPECT_EQ(*s21_list.cbegin(), 1);

  std::list<int> list_00{};
  s21::list<int> s21_list_00{};
}

TEST(List_Constructor, ListCend) {
  std::list<int> list{1, 2, 3};
  s21::list<int> s21_list{1, 2, 3};

  EXPECT_EQ(*(--list.cend()), 3);
  EXPECT_EQ(*(--s21_list.cend()), 3);

  std::list<int> list_00{};
  s21::list<int> s21_list_00{};
}

// List Capacity
TEST(List_Constructor, ListSize) {
  std::list<int> list{1, 2, 3};
  s21::list<int> s21_list{1, 2, 3};

  EXPECT_EQ(list.size(), 3);
  EXPECT_EQ(s21_list.size(), 3);

  std::list<int> list_00{};
  s21::list<int> s21_list_00{};

  EXPECT_EQ(list_00.size(), 0);
  EXPECT_EQ(s21_list_00.size(), 0);
}

TEST(List_Constructor, ListMaxSize) {
  s21::list<int> s21_list{1, 2, 3};
  s21::list<int> s21_list_00{};

  EXPECT_EQ(s21_list.max_size(), s21_list_00.max_size());
}

// List Modifiers
TEST(List_Constructor, ListEmty) {
  std::list<int> list{1, 2, 3};
  s21::list<int> s21_list{1, 2, 3};

  EXPECT_EQ(list.empty(), false);
  EXPECT_EQ(s21_list.empty(), false);

  std::list<int> list_00{};
  s21::list<int> s21_list_00{};

  EXPECT_EQ(list_00.empty(), true);
  EXPECT_EQ(s21_list_00.empty(), true);
}

TEST(List_Constructor, ListInsert) {
  std::list<int> list{1, 2, 3};
  s21::list<int> s21_list{1, 2, 3};

  list.insert(list.begin(), 0);
  s21_list.insert(s21_list.begin(), 0);

  EXPECT_EQ(list.front(), 0);
  EXPECT_EQ(s21_list.front(), 0);

  list.insert(list.begin()++, 1);
  s21_list.insert(s21_list.begin()++, 1);

  EXPECT_EQ(*(list.begin()++), 1);
  EXPECT_EQ(*(s21_list.begin()++), 1);

  list.insert(--list.end(), 5);
  s21_list.insert((s21_list.end() - 1), 5);

  EXPECT_EQ(*(--list.end()), 3);
  EXPECT_EQ(*(s21_list.end() - 1), 3);

  EXPECT_EQ(list.size(), 6);
  EXPECT_EQ(s21_list.size(), 6);
}

TEST(List_Constructor, ListInsertNullList) {
  std::list<int> list{};
  s21::list<int> s21_list{};

  list.insert(list.begin(), 0);
  s21_list.insert(s21_list.begin(), 0);

  EXPECT_EQ(list.front(), 0);
  EXPECT_EQ(s21_list.front(), 0);

  list.insert(list.begin()++, 1);
  s21_list.insert(s21_list.begin()++, 1);

  EXPECT_EQ(*(list.begin()++), 1);
  EXPECT_EQ(*(s21_list.begin()++), 1);

  list.insert(--list.end(), 5);
  s21_list.insert((s21_list.end() - 1), 5);

  EXPECT_EQ(*(--list.end()), 0);
  EXPECT_EQ(*(s21_list.end() - 1), 0);

  EXPECT_EQ(list.size(), 3);
  EXPECT_EQ(s21_list.size(), 3);
}

TEST(List_Constructor, ListErase) {
  std::list<int> list{1, 2, 3, 4, 5};
  s21::list<int> s21_list{1, 2, 3, 4, 5};

  list.erase(list.begin());
  list.erase(++list.begin());
  list.erase(--list.end());

  s21_list.erase(s21_list.begin());
  s21_list.erase(++s21_list.begin());
  s21_list.erase(--s21_list.end());

  EXPECT_EQ(list.front(), s21_list.front());
  EXPECT_EQ(list.back(), s21_list.back());

  EXPECT_ANY_THROW(s21_list.erase(s21_list.end()));
}

TEST(List_Constructor, ListSwap) {
  std::list<int> list{1, 2, 3, 4, 5};
  s21::list<int> s21_list{1, 2, 3, 4, 5};

  std::list<int> list_00{5, 4, 3, 2, 1};
  s21::list<int> s21_list_00{5, 4, 3, 2, 1};

  list.swap(list_00);
  s21_list.swap(s21_list_00);

  EXPECT_EQ(list.front(), s21_list.front());
  EXPECT_EQ(list.back(), s21_list.back());
}

TEST(List_Constructor, ListSwapNallList) {
  std::list<int> list{};
  s21::list<int> s21_list{};

  std::list<int> list_00{5, 4, 3, 2, 1};
  s21::list<int> s21_list_00{5, 4, 3, 2, 1};

  list.swap(list_00);
  s21_list.swap(s21_list_00);

  EXPECT_EQ(list.front(), s21_list.front());
  EXPECT_EQ(list.back(), s21_list.back());
}

TEST(List_Constructor, ListSwapNallList_02) {
  std::list<int> list{5, 4, 3, 2, 1};
  s21::list<int> s21_list{5, 4, 3, 2, 1};

  std::list<int> list_00{};
  s21::list<int> s21_list_00{};

  list.swap(list_00);
  s21_list.swap(s21_list_00);

  EXPECT_EQ(list_00.front(), s21_list_00.front());
  EXPECT_EQ(list_00.back(), s21_list_00.back());
}

TEST(List_Constructor, ListSwapNallList_03) {
  std::list<int> list{};
  s21::list<int> s21_list{};

  std::list<int> list_00{};
  s21::list<int> s21_list_00{};

  list.swap(list_00);
  s21_list.swap(s21_list_00);
}

TEST(List_Constructor, ListMerge) {
  std::list<int> list{1, 2, 3, 4, 5};
  s21::list<int> s21_list{1, 2, 3, 4, 5};

  std::list<int> list_00{5, 4, 3, 2, 1};
  s21::list<int> s21_list_00{5, 4, 3, 2, 1};

  list.merge(list_00);
  s21_list.merge(s21_list_00);

  EXPECT_EQ(list.front(), s21_list.front());
  EXPECT_EQ(list.back(), s21_list.back());

  EXPECT_EQ(list_00.empty(), true);
  EXPECT_EQ(s21_list_00.empty(), true);
}

TEST(List_Constructor, ListMergeNallList) {
  std::list<int> list{};
  s21::list<int> s21_list{};

  std::list<int> list_00{5, 4, 3, 2, 1};
  s21::list<int> s21_list_00{5, 4, 3, 2, 1};

  list.merge(list_00);
  s21_list.merge(s21_list_00);

  EXPECT_EQ(list.front(), s21_list.front());
  EXPECT_EQ(list.back(), s21_list.back());

  EXPECT_EQ(list_00.empty(), true);
  EXPECT_EQ(s21_list_00.empty(), true);
}

TEST(List_Constructor, ListMergeNallList_02) {
  std::list<int> list{5, 4, 3, 2, 1};
  s21::list<int> s21_list{5, 4, 3, 2, 1};

  std::list<int> list_00{};
  s21::list<int> s21_list_00{};

  list.merge(list_00);
  s21_list.merge(s21_list_00);

  EXPECT_EQ(list.front(), s21_list.front());
  EXPECT_EQ(list.back(), s21_list.back());

  EXPECT_EQ(list_00.empty(), true);
  EXPECT_EQ(s21_list_00.empty(), true);
}

TEST(List_Constructor, ListMergeNallList_03) {
  std::list<int> list{};
  s21::list<int> s21_list{};

  std::list<int> list_00{};
  s21::list<int> s21_list_00{};

  list.merge(list_00);
  s21_list.merge(s21_list_00);

  EXPECT_EQ(list.empty(), s21_list.empty());
}

TEST(List_Constructor, ListSpliceBegin) {
  std::list<int> list{1, 2, 3, 4, 5};
  s21::list<int> s21_list{1, 2, 3, 4, 5};

  std::list<int> list_00{5, 4, 3, 2, 1};
  s21::list<int> s21_list_00{5, 4, 3, 2, 1};

  auto iterListBegin = list.begin();
  auto iterListEnd = --list.end();
  auto iterList_00Begin = list_00.begin();
  auto iterList_00End = --list_00.end();

  auto iterS21_ListBegin = s21_list.begin();
  auto iterS21_ListEnd = --s21_list.end();
  auto iterS21_List_00Begin = s21_list_00.begin();
  auto iterS21_List_00End = --s21_list_00.end();

  list.splice(list.begin(), list_00);
  s21_list.splice(s21_list.begin(), s21_list_00);

  EXPECT_EQ(*iterListBegin, 1);
  EXPECT_EQ(*iterListEnd, 5);
  EXPECT_EQ(*iterList_00Begin, 5);
  EXPECT_EQ(*iterList_00End, 1);

  EXPECT_EQ(*iterS21_ListBegin, 1);
  EXPECT_EQ(*iterS21_ListEnd, 5);
  EXPECT_EQ(*iterS21_List_00Begin, 5);
  EXPECT_EQ(*iterS21_List_00End, 1);

  EXPECT_EQ(list.front(), s21_list.front());
  EXPECT_EQ(list.back(), s21_list.back());

  EXPECT_EQ(list_00.empty(), true);
  EXPECT_EQ(s21_list_00.empty(), true);
}

TEST(List_Constructor, ListSpliceEnd) {
  std::list<int> list{1, 2, 3, 4, 5};
  s21::list<int> s21_list{1, 2, 3, 4, 5};

  std::list<int> list_00{5, 4, 3, 2, 1};
  s21::list<int> s21_list_00{5, 4, 3, 2, 1};

  auto iterListBegin = list.begin();
  auto iterListEnd = --list.end();
  auto iterList_00Begin = list_00.begin();
  auto iterList_00End = --list_00.end();

  auto iterS21_ListBegin = s21_list.begin();
  auto iterS21_ListEnd = --s21_list.end();
  auto iterS21_List_00Begin = s21_list_00.begin();
  auto iterS21_List_00End = --s21_list_00.end();

  list.splice(list.end(), list_00);
  s21_list.splice(s21_list.end(), s21_list_00);

  EXPECT_EQ(*iterListBegin, 1);
  EXPECT_EQ(*iterListEnd, 5);
  EXPECT_EQ(*iterList_00Begin, 5);
  EXPECT_EQ(*iterList_00End, 1);

  EXPECT_EQ(*iterS21_ListBegin, 1);
  EXPECT_EQ(*iterS21_ListEnd, 5);
  EXPECT_EQ(*iterS21_List_00Begin, 5);
  EXPECT_EQ(*iterS21_List_00End, 1);

  EXPECT_EQ(list.front(), s21_list.front());
  EXPECT_EQ(list.back(), s21_list.back());

  EXPECT_EQ(list_00.empty(), true);
  EXPECT_EQ(s21_list_00.empty(), true);
}

TEST(List_Constructor, ListSpliceBetween) {
  std::list<int> list{1, 2, 3, 4, 5};
  s21::list<int> s21_list{1, 2, 3, 4, 5};

  std::list<int> list_00{5, 4, 3, 2, 1};
  s21::list<int> s21_list_00{5, 4, 3, 2, 1};

  auto iterListBegin = list.begin();
  auto iterListEnd = --list.end();
  auto iterList_00Begin = list_00.begin();
  auto iterList_00End = --list_00.end();

  auto iterS21_ListBegin = s21_list.begin();
  auto iterS21_ListEnd = --s21_list.end();
  auto iterS21_List_00Begin = s21_list_00.begin();
  auto iterS21_List_00End = --s21_list_00.end();

  list.splice(--list.end(), list_00);
  s21_list.splice(--s21_list.end(), s21_list_00);

  EXPECT_EQ(*iterListBegin, 1);
  EXPECT_EQ(*iterListEnd, 5);
  EXPECT_EQ(*iterList_00Begin, 5);
  EXPECT_EQ(*iterList_00End, 1);

  EXPECT_EQ(*iterS21_ListBegin, 1);
  EXPECT_EQ(*iterS21_ListEnd, 5);
  EXPECT_EQ(*iterS21_List_00Begin, 5);
  EXPECT_EQ(*iterS21_List_00End, 1);

  EXPECT_EQ(list.front(), s21_list.front());
  EXPECT_EQ(list.back(), s21_list.back());

  EXPECT_EQ(list_00.empty(), true);
  EXPECT_EQ(s21_list_00.empty(), true);
}

TEST(List_Constructor, ListSpliceBeginNullList) {
  std::list<int> list{};
  s21::list<int> s21_list{};

  std::list<int> list_00{5, 4, 3, 2, 1};
  s21::list<int> s21_list_00{5, 4, 3, 2, 1};

  auto iterList_00Begin = list_00.begin();
  auto iterList_00End = --list_00.end();

  auto iterS21_List_00Begin = s21_list_00.begin();
  auto iterS21_List_00End = --s21_list_00.end();

  list.splice(list.begin(), list_00);
  s21_list.splice(s21_list.begin(), s21_list_00);

  EXPECT_EQ(*iterList_00Begin, 5);
  EXPECT_EQ(*iterList_00End, 1);

  EXPECT_EQ(*iterS21_List_00Begin, 5);
  EXPECT_EQ(*iterS21_List_00End, 1);

  EXPECT_EQ(list.front(), s21_list.front());
  EXPECT_EQ(list.back(), s21_list.back());

  EXPECT_EQ(list_00.empty(), true);
  EXPECT_EQ(s21_list_00.empty(), true);
}

TEST(List_Constructor, ListSpliceEndNullList) {
  std::list<int> list{};
  s21::list<int> s21_list{};

  std::list<int> list_00{5, 4, 3, 2, 1};
  s21::list<int> s21_list_00{5, 4, 3, 2, 1};

  auto iterList_00Begin = list_00.begin();
  auto iterList_00End = --list_00.end();

  auto iterS21_List_00Begin = s21_list_00.begin();
  auto iterS21_List_00End = --s21_list_00.end();

  list.splice(list.end(), list_00);
  s21_list.splice(s21_list.end(), s21_list_00);

  EXPECT_EQ(*iterList_00Begin, 5);
  EXPECT_EQ(*iterList_00End, 1);

  EXPECT_EQ(*iterS21_List_00Begin, 5);
  EXPECT_EQ(*iterS21_List_00End, 1);

  EXPECT_EQ(list.front(), s21_list.front());
  EXPECT_EQ(list.back(), s21_list.back());

  EXPECT_EQ(list_00.empty(), true);
  EXPECT_EQ(s21_list_00.empty(), true);
}

TEST(List_Constructor, ListSpliceBeginList_00Null) {
  std::list<int> list{1, 2, 3, 4, 5};
  s21::list<int> s21_list{1, 2, 3, 4, 5};

  std::list<int> list_00{};
  s21::list<int> s21_list_00{};

  auto iterListBegin = list.begin();
  auto iterListEnd = --list.end();

  auto iterS21_ListBegin = s21_list.begin();
  auto iterS21_ListEnd = --s21_list.end();

  list.splice(list.begin(), list_00);
  s21_list.splice(s21_list.begin(), s21_list_00);

  EXPECT_EQ(*iterListBegin, 1);
  EXPECT_EQ(*iterListEnd, 5);

  EXPECT_EQ(*iterS21_ListBegin, 1);
  EXPECT_EQ(*iterS21_ListEnd, 5);

  EXPECT_EQ(list.front(), s21_list.front());
  EXPECT_EQ(list.back(), s21_list.back());

  EXPECT_EQ(list_00.empty(), true);
  EXPECT_EQ(s21_list_00.empty(), true);
}

TEST(List_Constructor, ListSpliceEndList_00Null) {
  std::list<int> list{1, 2, 3, 4, 5};
  s21::list<int> s21_list{1, 2, 3, 4, 5};

  std::list<int> list_00{};
  s21::list<int> s21_list_00{};

  auto iterListBegin = list.begin();
  auto iterListEnd = --list.end();

  auto iterS21_ListBegin = s21_list.begin();
  auto iterS21_ListEnd = --s21_list.end();

  list.splice(list.end(), list_00);
  s21_list.splice(s21_list.end(), s21_list_00);

  EXPECT_EQ(*iterListBegin, 1);
  EXPECT_EQ(*iterListEnd, 5);

  EXPECT_EQ(*iterS21_ListBegin, 1);
  EXPECT_EQ(*iterS21_ListEnd, 5);

  EXPECT_EQ(list.front(), s21_list.front());
  EXPECT_EQ(list.back(), s21_list.back());

  EXPECT_EQ(list_00.empty(), true);
  EXPECT_EQ(s21_list_00.empty(), true);
}

TEST(List_Constructor, ListSpliceBetweenList_00Null) {
  std::list<int> list{1, 2, 3, 4, 5};
  s21::list<int> s21_list{1, 2, 3, 4, 5};

  std::list<int> list_00{};
  s21::list<int> s21_list_00{};

  auto iterListBegin = list.begin();
  auto iterListEnd = --list.end();

  auto iterS21_ListBegin = s21_list.begin();
  auto iterS21_ListEnd = --s21_list.end();

  list.splice(--list.end(), list_00);
  s21_list.splice(--s21_list.end(), s21_list_00);

  EXPECT_EQ(*iterListBegin, 1);
  EXPECT_EQ(*iterListEnd, 5);

  EXPECT_EQ(*iterS21_ListBegin, 1);
  EXPECT_EQ(*iterS21_ListEnd, 5);

  EXPECT_EQ(list.front(), s21_list.front());
  EXPECT_EQ(list.back(), s21_list.back());

  EXPECT_EQ(list_00.empty(), true);
  EXPECT_EQ(s21_list_00.empty(), true);
}

TEST(List_Constructor, ListSpliceBTwoListNull) {
  std::list<int> list{};
  s21::list<int> s21_list{};

  std::list<int> list_00{};
  s21::list<int> s21_list_00{};

  list.splice(list.end(), list_00);
  s21_list.splice(s21_list.end(), s21_list_00);

  EXPECT_EQ(list_00.empty(), true);
  EXPECT_EQ(s21_list_00.empty(), true);
}

TEST(List_Constructor, ListRevers_00) {
  std::list<int> list{1, 2, 3, 4, 5};
  s21::list<int> s21_list{1, 2, 3, 4, 5};

  auto iterListBegin = list.begin();
  auto iterListEnd = --list.end();

  auto iterS21_ListBegin = s21_list.begin();
  auto iterS21_ListEnd = --s21_list.end();

  list.reverse();
  s21_list.reverse();

  EXPECT_EQ(*iterListBegin, 1);
  EXPECT_EQ(*iterListEnd, 5);
  EXPECT_EQ(*iterS21_ListBegin, 1);
  EXPECT_EQ(*iterS21_ListEnd, 5);
}

TEST(List_Constructor, ListUnique) {
  std::list<int> list{1, 2, 3};
  s21::list<int> s21_list{1, 2, 3};

  list.unique();
  s21_list.unique();

  EXPECT_EQ(list.size(), 3);
  EXPECT_EQ(s21_list.size(), 3);

  EXPECT_EQ(*list.begin(), 1);
  EXPECT_EQ(*s21_list.begin(), 1);

  EXPECT_EQ(*(++list.begin()), 2);
  EXPECT_EQ(*(++s21_list.begin()), 2);

  EXPECT_EQ(*(--list.end()), 3);
  EXPECT_EQ(*(--s21_list.end()), 3);
}

TEST(List_Constructor, ListUnique_2) {
  std::list<int> list{1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3};
  s21::list<int> s21_list{1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3};

  list.unique();
  s21_list.unique();

  EXPECT_EQ(list.size(), 3);
  EXPECT_EQ(s21_list.size(), 3);

  EXPECT_EQ(*list.begin(), 1);
  EXPECT_EQ(*s21_list.begin(), 1);

  EXPECT_EQ(*(++list.begin()), 2);
  EXPECT_EQ(*(++s21_list.begin()), 2);

  EXPECT_EQ(*(--list.end()), 3);
  EXPECT_EQ(*(--s21_list.end()), 3);
}

TEST(List_Constructor, ListSort) {
  std::list<int> list{1, 2, 3, 4, 5};
  s21::list<int> s21_list{1, 2, 3, 4, 5};

  list.sort();
  s21_list.sort();

  EXPECT_EQ(list.size(), 5);
  EXPECT_EQ(s21_list.size(), 5);

  EXPECT_EQ(*list.begin(), 1);
  EXPECT_EQ(*s21_list.begin(), 1);

  EXPECT_EQ(*(++list.begin()), 2);
  EXPECT_EQ(*(++s21_list.begin()), 2);

  EXPECT_EQ(*(--list.end()), 5);
  EXPECT_EQ(*(--s21_list.end()), 5);
}

TEST(List_Constructor, ListSort_2) {
  std::list<int> list{5, 4, 3, 2, 1};
  s21::list<int> s21_list{5, 4, 3, 2, 1};

  list.sort();
  s21_list.sort();

  EXPECT_EQ(list.size(), 5);
  EXPECT_EQ(s21_list.size(), 5);

  EXPECT_EQ(*list.begin(), 1);
  EXPECT_EQ(*s21_list.begin(), 1);

  EXPECT_EQ(*(++list.begin()), 2);
  EXPECT_EQ(*(++s21_list.begin()), 2);

  EXPECT_EQ(*(--list.end()), 5);
  EXPECT_EQ(*(--s21_list.end()), 5);
}

TEST(List_Constructor, ListSort_3) {
  std::list<int> list{};
  s21::list<int> s21_list{};

  list.sort();
  s21_list.sort();

  EXPECT_EQ(list.size(), 0);
  EXPECT_EQ(s21_list.size(), 0);
}

TEST(List_Constructor, ListPopBack) {
  std::list<int> list{1, 2, 3};
  s21::list<int> s21_list{1, 2, 3};

  list.pop_back();
  s21_list.pop_back();

  EXPECT_EQ(list.size(), 2);
  EXPECT_EQ(s21_list.size(), 2);

  EXPECT_EQ(list.back(), 2);
  EXPECT_EQ(s21_list.back(), 2);

  list.pop_back();
  s21_list.pop_back();

  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(s21_list.size(), 1);

  EXPECT_EQ(list.back(), 1);
  EXPECT_EQ(s21_list.back(), 1);

  list.pop_back();
  s21_list.pop_back();

  EXPECT_EQ(list.size(), 0);
  EXPECT_EQ(s21_list.size(), 0);

  EXPECT_EQ(s21_list.getPointHead(), nullptr);
  EXPECT_EQ(s21_list.getPointTail(), nullptr);
}

TEST(List_Constructor, ListPopFront) {
  std::list<int> list{1, 2, 3};
  s21::list<int> s21_list{1, 2, 3};

  list.pop_front();
  s21_list.pop_front();

  EXPECT_EQ(list.size(), 2);
  EXPECT_EQ(s21_list.size(), 2);

  EXPECT_EQ(list.back(), 3);
  EXPECT_EQ(s21_list.back(), 3);

  list.pop_front();
  s21_list.pop_front();

  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(s21_list.size(), 1);

  EXPECT_EQ(list.back(), 3);
  EXPECT_EQ(s21_list.back(), 3);

  list.pop_front();
  s21_list.pop_front();

  EXPECT_EQ(list.size(), 0);
  EXPECT_EQ(s21_list.size(), 0);

  EXPECT_EQ(s21_list.getPointHead(), nullptr);
  EXPECT_EQ(s21_list.getPointTail(), nullptr);
}

TEST(List_Constructor, ListInsertMany) {
  s21::list<int> s21_list{5, 6, 7, 8};

  s21_list.insert_many(s21_list.cend(), 0, 1, 2, 3);

  EXPECT_EQ(s21_list.size(), 8);
  EXPECT_EQ(s21_list.front(), 5);
  EXPECT_EQ(s21_list.back(), 3);
}

TEST(List_Constructor, ListInsertMany_01) {
  s21::list<int> s21_list{5, 6, 7, 8};

  s21_list.insert_many(--s21_list.cend(), 0, 1, 2, 3);

  EXPECT_EQ(s21_list.size(), 8);
  EXPECT_EQ(s21_list.front(), 5);
  EXPECT_EQ(s21_list.back(), 8);
}

TEST(List_Constructor, ListInsertMany_02) {
  s21::list<int> s21_list{5, 6, 7, 8};

  s21_list.insert_many(s21_list.begin(), 0, 1, 2, 3);

  EXPECT_EQ(s21_list.size(), 8);
  EXPECT_EQ(s21_list.front(), 0);
  EXPECT_EQ(s21_list.back(), 8);
}

TEST(List_Constructor, ListInsertMany_03) {
  s21::list<int> s21_list{};

  s21_list.insert_many(s21_list.begin(), 0, 1, 2, 3);

  EXPECT_EQ(s21_list.size(), 4);
  EXPECT_EQ(s21_list.front(), 0);
  EXPECT_EQ(s21_list.back(), 3);
}

TEST(List_Constructor, ListInsertManyFront) {
  s21::list<int> s21_list{};

  s21_list.insert_many_front(0, 1, 2, 3);

  EXPECT_EQ(s21_list.size(), 4);
  EXPECT_EQ(s21_list.front(), 0);
  EXPECT_EQ(s21_list.back(), 3);
}

TEST(List_Constructor, ListInsertManyFront_01) {
  s21::list<int> s21_list{1, 2};

  s21_list.insert_many_front(0, 1, 2, 3);

  EXPECT_EQ(s21_list.size(), 6);
  EXPECT_EQ(s21_list.front(), 0);
  EXPECT_EQ(s21_list.back(), 2);
}

TEST(List_Constructor, ListInsertManyBack) {
  s21::list<int> s21_list{};

  s21_list.insert_many_back(0, 1, 2, 3);

  EXPECT_EQ(s21_list.size(), 4);
  EXPECT_EQ(s21_list.front(), 0);
  EXPECT_EQ(s21_list.back(), 3);
}

TEST(List_Constructor, ListInsertManyBack_01) {
  s21::list<int> s21_list{1, 2};

  s21_list.insert_many_back(0, 1, 2, 3);

  EXPECT_EQ(s21_list.size(), 6);
  EXPECT_EQ(s21_list.front(), 1);
  EXPECT_EQ(s21_list.back(), 3);
}
