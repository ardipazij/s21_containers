#include <map>

#include "s21_containers_test.h"

namespace s21 {
void s21ContainersMapTest::SetUp() {
  s21_map = new map<int, std::string>;
  s21_map->insert({1, "one"});
  s21_map->insert({2, "two"});
  s21_map->insert({3, "three"});
  s21_map->insert({4, "four"});
  s21_map->insert({5, "five"});

  std_map = new std::map<int, std::string>;
  std_map->insert({1, "one"});
  std_map->insert({2, "two"});
  std_map->insert({3, "three"});
  std_map->insert({4, "four"});
  std_map->insert({5, "five"});
}

void s21ContainersMapTest::TearDown() {
  delete std_map;
  delete s21_map;
}

void random_insert(const int insert_count, int random,
                   s21::map<int, std::string> &s21_s,
                   std::map<int, std::string> &std_s) {
  std::string s = "hello";
  for (int i = 0; i < insert_count; i++) {
    int x = rand() % random;
    s21_s.insert({x, s});
    std_s.insert({x, s});
  }
}

TEST_F(s21ContainersMapTest, SpeedTest) {
  s21::map<int, std::string> s21_map;
  std::map<int, std::string> std_map;
  random_insert(5000, 100099, s21_map, std_map);
  EXPECT_EQ(s21_map.empty(), std_map.empty());
  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ((s21_map.begin()->first), (std_map.begin()->first));
  EXPECT_EQ((s21_map.begin()->second), (std_map.begin()->second));
}

TEST_F(s21ContainersMapTest, DefaultConstructorTest) {
  std::map<std::string, int> def;
  map<std::string, int> custom;
  EXPECT_EQ(def.size(), 0);
  EXPECT_EQ(def.size(), custom.size());
}

TEST_F(s21ContainersMapTest, ConstructorInitializerListTest) {
  s21::map<int, std::string> s21_map_temp{
      {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"}};
  EXPECT_EQ("one", s21_map_temp.at(1));
  EXPECT_EQ("two", s21_map_temp.at(2));
  EXPECT_EQ("three", s21_map_temp.at(3));
  EXPECT_EQ("four", s21_map_temp.at(4));
  EXPECT_EQ("five", s21_map_temp.at(5));
}

TEST_F(s21ContainersMapTest, CopyConstructorTest) {
  map<int, std::string> s21_map_c{
      {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"}};
  map<int, std::string> s21_map_copy(s21_map_c);
  EXPECT_EQ(s21_map_copy.size(), s21_map_c.size());
  EXPECT_EQ(s21_map_c.at(1), s21_map_copy.at(1));
  EXPECT_EQ(s21_map_c.at(2), s21_map_copy.at(2));
}

TEST_F(s21ContainersMapTest, OperatorCopy) {
  map<int, std::string> s21m_c = *s21_map;

  EXPECT_EQ(s21_map->size(), s21m_c.size());
  EXPECT_EQ(s21_map->at(1), s21m_c.at(1));
  EXPECT_EQ(s21_map->at(2), s21m_c.at(2));
  EXPECT_EQ(s21_map->at(3), s21m_c.at(3));
  EXPECT_EQ(s21_map->at(4), s21m_c.at(4));
  EXPECT_EQ(s21_map->at(5), s21m_c.at(5));
}

TEST_F(s21ContainersMapTest, OperatorMove) {
  map<int, std::string> s21m{
      {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"}};
  size_t s = s21m.size();
  map<int, std::string> s21m_moved = std::move(s21m);
  EXPECT_EQ(s, s21m_moved.size());
  EXPECT_EQ("one", s21m_moved.at(1));
  EXPECT_EQ("two", s21m_moved.at(2));
  EXPECT_EQ("three", s21m_moved.at(3));
  EXPECT_EQ("four", s21m_moved.at(4));
  EXPECT_EQ("five", s21m_moved.at(5));
}

TEST_F(s21ContainersMapTest, OperatorInitializerListTest) {
  s21::map<int, std::string> s21_map_temp = {
      {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"}};
  EXPECT_EQ("one", s21_map_temp.at(1));
  EXPECT_EQ("two", s21_map_temp.at(2));
  EXPECT_EQ("three", s21_map_temp.at(3));
  EXPECT_EQ("four", s21_map_temp.at(4));
  EXPECT_EQ("five", s21_map_temp.at(5));
  EXPECT_EQ(s21_map_temp.size(), 5);
}

TEST_F(s21ContainersMapTest, OperatorEqual) {
  map<int, std::string> s21m (*s21_map);
  EXPECT_TRUE(*s21_map == s21m);
}

TEST_F(s21ContainersMapTest, OperatorNotEqual) {
  map<int, std::string> s21m{{1, "one"}, {2, "two"}};
  EXPECT_TRUE(*s21_map != s21m);
}

TEST_F(s21ContainersMapTest, SizeMethodTest) {
  EXPECT_EQ(5, s21_map->size());

  s21_map->insert({10, "ten"});
  EXPECT_EQ(6, s21_map->size());

  s21_map->insert({20, "twenty"});
  EXPECT_EQ(7, s21_map->size());
}

TEST_F(s21ContainersMapTest, MaxSizeMethodTest) {
  EXPECT_EQ(std_map->max_size(), s21_map->max_size());
}

TEST_F(s21ContainersMapTest, MaxSizeMethodTestTwo) {
  map<std::string, double> s21_m{{"one", 1.0}, {"two", 2.0}, {"three", 3.0}};
  std::map<std::string, double> std_m{
      {"one", 1.0}, {"two", 2.0}, {"three", 3.0}};
  EXPECT_EQ(std_m.max_size(), s21_m.max_size());
}

TEST_F(s21ContainersMapTest, MaxSizeMethodTestThree) {
  map<char, int> s21_m{{'a', 1}, {'b', 2}};
  std::map<char, int> std_m{{'a', 1}, {'b', 2}};
  EXPECT_EQ(std_m.max_size(), s21_m.max_size());
}

TEST_F(s21ContainersMapTest, MethodAtTest) {
  EXPECT_EQ("one", std_map->at(1));
  EXPECT_EQ("one", s21_map->at(1));

  std_map->at(1) = "updated one";
  s21_map->at(1) = "updated one";
  EXPECT_EQ("updated one", s21_map->at(1));
  EXPECT_EQ("updated one", std_map->at(1));

  std_map->at(2) = "updated two";
  s21_map->at(2) = "updated two";
  EXPECT_EQ("updated two", s21_map->at(2));
  EXPECT_EQ("updated two", std_map->at(2));
}

TEST_F(s21ContainersMapTest, ConstMethodAtTest) {
  EXPECT_EQ("one", std_map->at(1));
  EXPECT_EQ("one", s21_map->at(1));

  std_map->at(1) = "updated one";
  s21_map->at(1) = "updated one";
  EXPECT_EQ("updated one", s21_map->at(1));
  EXPECT_EQ("updated one", std_map->at(1));

  std_map->at(2) = "updated two";
  s21_map->at(2) = "updated two";
  EXPECT_EQ("updated two", s21_map->at(2));
  EXPECT_EQ("updated two", std_map->at(2));

  const std::string saved_s21_str = s21_map->at(1);
  const std::string saved_std_str = std_map->at(1);
}

TEST_F(s21ContainersMapTest, OperatorIndexTest) {
  EXPECT_EQ((*s21_map)[1], (*std_map)[1]);
  EXPECT_EQ("one", s21_map->at(1));

  (*std_map)[1] = "updated one";
  (*s21_map)[1] = "updated one";
  EXPECT_EQ("updated one", (*std_map)[1]);
  EXPECT_EQ("updated one", (*s21_map)[1]);

  (*std_map)[2] = "updated two";
  (*s21_map)[2] = "updated two";
  EXPECT_EQ("updated two", (*std_map)[2]);
  EXPECT_EQ("updated two", (*s21_map)[2]);
}

TEST_F(s21ContainersMapTest, InsertMethodTest) {
  std_map->insert({6, "six"});
  s21_map->insert({6, "six"});

  EXPECT_EQ(std_map->size(), s21_map->size());
  EXPECT_EQ((*std_map)[6], (*s21_map)[6]);
}

TEST_F(s21ContainersMapTest, FindMethodTest) {
  auto std_find = std_map->find(2);
  auto s21_find = s21_map->find(2);

  EXPECT_EQ((*std_find).second, (*s21_find).second);
}

TEST_F(s21ContainersMapTest, ClearMethodTest) {
  std_map->clear();
  s21_map->clear();

  EXPECT_TRUE(std_map->empty());
  EXPECT_TRUE(s21_map->empty());
}

TEST_F(s21ContainersMapTest, CountMethodTest) {
  int std_count = std_map->count(2);
  int s21_count = s21_map->count(2);

  EXPECT_EQ(std_count, s21_count);
}

TEST_F(s21ContainersMapTest, SwapMethodTest) {
  s21::map<int, std::string> s21_map1{{1, "one"}, {2, "two"}};
  s21::map<int, std::string> s21_map2{{3, "three"}, {4, "four"}};

  s21_map1.swap(s21_map2);

  EXPECT_EQ(2, s21_map2.size());
  EXPECT_EQ(2, s21_map1.size());
  EXPECT_EQ(s21_map1.at(3), "three");
  EXPECT_EQ(s21_map1.at(4), "four");
  EXPECT_EQ(s21_map2.at(1), "one");
  EXPECT_EQ(s21_map2.at(2), "two");
}

TEST_F(s21ContainersMapTest, MergeMethodTest) {
  std::map<int, std::string> std_map1{{1, "one"}, {2, "two"}};
  std::map<int, std::string> std_map2{{3, "three"}, {4, "four"}};

  s21::map<int, std::string> s21_map1{{1, "one"}, {2, "two"}};
  s21::map<int, std::string> s21_map2{{3, "three"}, {4, "four"}};

  std_map1.merge(std_map2);
  s21_map1.merge(s21_map2);

  EXPECT_EQ(4, s21_map1.size());
  EXPECT_EQ(std_map1.size(), s21_map1.size());
}

TEST_F(s21ContainersMapTest, ContainsMethodTest) {
  EXPECT_TRUE(s21_map->contains(1));
  EXPECT_TRUE(s21_map->contains(2));
  EXPECT_TRUE(s21_map->contains(3));
  EXPECT_TRUE(s21_map->contains(4));
  EXPECT_TRUE(s21_map->contains(5));
}

TEST_F(s21ContainersMapTest, InsertOrAssign_KeyValue) {
  s21_map->insert_or_assign(10, "ten");
  std_map->insert_or_assign(10, "ten");
  EXPECT_EQ("ten", s21_map->at(10));
  EXPECT_EQ(s21_map->size(), 6);
  EXPECT_EQ(s21_map->at(10), std_map->at(10));

  s21_map->insert_or_assign(11, "eleven");
  std_map->insert_or_assign(11, "eleven");
  EXPECT_EQ("eleven", s21_map->at(11));
  EXPECT_EQ(s21_map->size(), 7);
  EXPECT_EQ(s21_map->at(11), std_map->at(11));

  s21_map->insert_or_assign(11, "assign new value");
  std_map->insert_or_assign(11, "assign new value");
  EXPECT_EQ(s21_map->size(), 7);
  EXPECT_EQ(s21_map->at(11), std_map->at(11));
}

TEST_F(s21ContainersMapTest, Insert_KeyValue) {
  s21_map->insert(10, "ten");
  std_map->insert({10, "ten"});
  EXPECT_EQ("ten", s21_map->at(10));
  EXPECT_EQ(s21_map->size(), 6);
  EXPECT_EQ(s21_map->at(10), std_map->at(10));

  s21_map->insert(11, "eleven");
  std_map->insert({11, "eleven"});
  EXPECT_EQ("eleven", s21_map->at(11));
  EXPECT_EQ(s21_map->size(), 7);
  EXPECT_EQ(s21_map->at(11), std_map->at(11));

  s21_map->insert(12, "twelve");
  std_map->insert({12, "twelve"});
  EXPECT_EQ(s21_map->size(), 8);
  EXPECT_EQ(s21_map->at(12), std_map->at(12));
}

TEST_F(s21ContainersMapTest, InsertOrAssign_WithPair) {
  s21_map->insert_or_assign({10, "ten"});
  std_map->insert_or_assign(10, "ten");
  EXPECT_EQ("ten", s21_map->at(10));
  EXPECT_EQ(s21_map->size(), 6);
  EXPECT_EQ(s21_map->at(10), std_map->at(10));

  s21_map->insert_or_assign({11, "eleven"});
  std_map->insert_or_assign(11, "eleven");
  EXPECT_EQ("eleven", s21_map->at(11));
  EXPECT_EQ(s21_map->size(), 7);
  EXPECT_EQ(s21_map->at(11), std_map->at(11));

  s21_map->insert_or_assign({12, "twelve"});
  std_map->insert_or_assign(12, "twelve");
  EXPECT_EQ(s21_map->size(), 8);
  EXPECT_EQ(s21_map->at(12), std_map->at(12));
}

TEST_F(s21ContainersMapTest, IteratorBeginTest) {
  auto stdit = std_map->begin();
  for (auto it = s21_map->begin(); it != s21_map->end(); ++it, ++stdit) {
    EXPECT_EQ((*stdit).first, (*it).first);
    EXPECT_EQ((*stdit).second, (*it).second);
  }
}

TEST_F(s21ContainersMapTest, IteratorEndTest) {
  auto stdit = std_map->end();
  auto it = s21_map->end();
  for (; it != s21_map->begin();) {
    --stdit;
    --it;
    EXPECT_EQ((*stdit).first, (*it).first);
    EXPECT_EQ((*stdit).second, (*it).second);
  }
}

TEST_F(s21ContainersMapTest, IteratorCBeginTest) {
  const auto stdit = std_map->cbegin();
  const auto it = s21_map->cbegin();
  EXPECT_EQ(*stdit, *it);
}

TEST_F(s21ContainersMapTest, EraseMethodTest) {
  std_map->erase(1);
  s21_map->erase(1);

  EXPECT_EQ(std_map->size(), s21_map->size());
  for (int i = 2; i < 6; i++) {
    EXPECT_EQ(std_map->at(i), s21_map->at(i));
  }

  std_map->erase(4);
  s21_map->erase(4);
  EXPECT_EQ(std_map->at(2), s21_map->at(2));
  EXPECT_EQ(std_map->at(3), s21_map->at(3));
  EXPECT_EQ(std_map->at(5), s21_map->at(5));
}

TEST_F(s21ContainersMapTest, InsertManyMethodTest) {
  s21_map->insert_many(std::make_pair(10, "ten"), std::make_pair(11, "eleven"),
                       std::make_pair(12, "twelve"));
  EXPECT_EQ(s21_map->size(), 8);
  EXPECT_EQ(s21_map->at(10), "ten");
  EXPECT_EQ(s21_map->at(11), "eleven");
  EXPECT_EQ(s21_map->at(12), "twelve");
}

void random_delete(s21::map<int, std::string> &s21_map,
                   std::map<int, std::string> &std_map) {
  size_t count_delete_elements = rand() % s21_map.size();
  for (size_t i = 0; i < count_delete_elements; i++) {
    auto s21_x = s21_map.begin();
    auto std_x = std_map.begin();
    for (int a = rand() % s21_map.size(); a != 0; a--) {
      ++s21_x;
      ++std_x;
    }
    s21_map.erase(s21_x);
    std_map.erase(std_x);
  }
}

TEST_F(s21ContainersMapTest, random_erase_1) {
  s21::map<int, std::string> s21_map;
  std::map<int, std::string> std_map;
  random_insert(5000, 500, s21_map, std_map);
  random_delete(s21_map, std_map);
}

TEST_F(s21ContainersMapTest, random_erase_2) {
  for (int i = random() % 50; i != 0; --i) {
    s21::map<int, std::string> s21_map;
    std::map<int, std::string> std_map;

    EXPECT_EQ(s21_map.max_size(), s21_map.max_size());

    random_insert(5000, 500, s21_map, std_map);

    random_delete(s21_map, std_map);

    s21::map<int, std::string> s21_map_copy = s21_map;
    std::map<int, std::string> std_map_copy = std_map;

    s21::map<int, std::string> s21_map_move = s21_map;
    std::map<int, std::string> std_map_move = std_map;

    auto s21_x = s21_map.begin();
    auto std_x = std_map.begin();
    for (; s21_x != s21_map.end() && std_x != std_map.end(); ++s21_x, ++std_x) {
      EXPECT_EQ(*s21_x, *std_x);
    }

    auto s21_x_copy = s21_map_copy.begin();
    auto std_x_copy = std_map_copy.begin();
    for (; s21_x_copy != s21_map_copy.end() && std_x_copy != std_map_copy.end();
         ++s21_x_copy, ++std_x_copy) {
      EXPECT_EQ(*s21_x_copy, *std_x_copy);
    }

    auto s21_x_move = s21_map_move.begin();
    auto std_x_move = std_map_move.begin();
    for (; s21_x_move != s21_map_move.end() && std_x_move != std_map_move.end();
         ++s21_x_move, ++std_x_move) {
      EXPECT_EQ(*s21_x_move, *std_x_move);
    }
  }
}

}  // namespace s21