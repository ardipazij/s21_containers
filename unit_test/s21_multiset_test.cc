#include <set>

#include "s21_containers_test.h"

void random_insert(const int insert_count, int random,
                   s21::multiset<int> &s21_s, std::multiset<int> &std_s) {
  for (int i = 0; i < insert_count; i++) {
    int x = rand() % random;
    s21_s.insert(x);
    std_s.insert(x);
  }
}

TEST(S21_multiset, Constructor) {
  s21::multiset<int> s21_multiset;
  std::multiset<int> std_multiset;
  EXPECT_EQ(s21_multiset.empty(), std_multiset.empty());
  EXPECT_EQ(s21_multiset.size(), std_multiset.size());
}

TEST(S21_multiset, Constructor_initializer_list) {
  s21::multiset<int> s21_multiset = {0, 15, 14, 20, 20, 15, 20};
  EXPECT_FALSE(s21_multiset.empty());
  EXPECT_TRUE(s21_multiset.size() == 7);
  int arr[] = {0, 14, 15, 15, 20, 20, 20};
  auto it = s21_multiset.begin();
  for (size_t i = 0; i < s21_multiset.size(); i++, ++it) {
    EXPECT_EQ(*it, arr[i]);
  }
}

TEST(S21_multiset, Constructor_copy) {
  s21::multiset<int> s21_multiset = {0, 5, 10, 15};
  s21::multiset<int> s21_multiset_copy(s21_multiset);
  std::multiset<int> std_multiset;
  for (int i = 0; i <= 15; i += 5) std_multiset.insert(i);
  std::multiset<int> std_multiset_copy(std_multiset);

  EXPECT_EQ(s21_multiset.empty(), std_multiset.empty());
  EXPECT_EQ(s21_multiset.size(), std_multiset.size());
  EXPECT_EQ(*s21_multiset.begin(), *std_multiset.begin());

  EXPECT_EQ(s21_multiset_copy.empty(), std_multiset_copy.empty());
  EXPECT_EQ(s21_multiset_copy.size(), std_multiset_copy.size());
  EXPECT_EQ(*(s21_multiset_copy.begin()), *(std_multiset_copy.begin()));
}

TEST(S21_multiset, Constructor_move) {
  s21::multiset<int> s21_multiset = {0, 5, 10, 15};
  s21::multiset<int> s21_multiset_move(std::move(s21_multiset));
  std::multiset<int> std_multiset;
  for (int i = 0; i <= 15; i += 5) std_multiset.insert(i);
  std::multiset<int> std_multiset_move(std::move(std_multiset));

  EXPECT_EQ(s21_multiset.empty(), std_multiset.empty());
  EXPECT_EQ(s21_multiset.size(), std_multiset.size());

  EXPECT_EQ(s21_multiset_move.empty(), std_multiset_move.empty());
  EXPECT_EQ(s21_multiset_move.size(), std_multiset_move.size());
  EXPECT_EQ(*(s21_multiset_move.begin()), *(std_multiset_move.begin()));
}

TEST(S21_multiset, Operator_copy) {
  s21::multiset<int> s21_multiset = {0, 5, 10, 15};
  s21::multiset<int> s21_multiset_cp = {0, -5, -10, -15, 5};

  s21_multiset_cp = s21_multiset;

  EXPECT_EQ(s21_multiset.size(), s21_multiset_cp.size());

  for (auto s21_it_2 = s21_multiset_cp.begin(), s21_it = s21_multiset.begin();
       s21_it != s21_multiset.end(); s21_it++, s21_it_2++) {
    EXPECT_EQ(*s21_it, *s21_it_2);
  }
  EXPECT_FALSE(s21_multiset_cp.contains(-10));
}

TEST(S21_multiset, Operator_move) {
  s21::multiset<int> s21_multiset = {0, 5, 10, 15};
  s21::multiset<int> s21_multiset_mv = {0, -5, -10, -15};
  EXPECT_EQ(s21_multiset.size(), s21_multiset_mv.size());

  s21_multiset_mv = std::move(s21_multiset);

  EXPECT_EQ(s21_multiset.size(), 0);

  EXPECT_TRUE(s21_multiset_mv.contains(10));
  EXPECT_FALSE(s21_multiset_mv.contains(-10));
}

TEST(S21_multiset, insert_5000_random) {
  s21::multiset<int> s21_multiset;
  std::multiset<int> std_multiset;
  size_t size_mset = 5000;
  random_insert(size_mset, 100099, s21_multiset, std_multiset);

  EXPECT_EQ(s21_multiset.empty(), std_multiset.empty());
  EXPECT_EQ(s21_multiset.size(), std_multiset.size());
  EXPECT_EQ(s21_multiset.size(), size_mset);
  EXPECT_EQ(*(s21_multiset.begin()), *(std_multiset.begin()));
  EXPECT_TRUE(s21_multiset.BLM());
  EXPECT_FALSE(s21_multiset.RedAlert());
}

TEST(S21_multiset, insert_many) {
  s21::multiset<int> s21_multiset;
  std::multiset<int> std_multiset;
  auto it_b = s21_multiset.insert_many(2, 1, 3, 5, 6, 4, 8, 7, 8, 0);

  for (size_t i = 0; i < s21_multiset.size(); i++) {
    std_multiset.insert(*(it_b.at(i).first));
  }

  EXPECT_EQ(s21_multiset.size(), std_multiset.size());
  EXPECT_EQ(*(s21_multiset.begin()), *(std_multiset.begin()));
  EXPECT_TRUE(s21_multiset.BLM());
  EXPECT_FALSE(s21_multiset.RedAlert());
}

TEST(S21_multiset, erase) {
  std::vector<int> vector{1, 2, 100, 5, 6, -1, 100, -2, 100};
  s21::multiset<int> s21_multiset;
  std::multiset<int> std_multiset;
  for (size_t i = 0; i < vector.size(); i++) {
    std_multiset.insert(vector[i]);
    s21_multiset.insert(vector[i]);
  }
  int one_hungred = 100;
  std_multiset.erase(one_hungred);
  s21_multiset.erase(one_hungred);

  EXPECT_EQ(s21_multiset.size(), std_multiset.size());
  EXPECT_EQ(s21_multiset.end(), s21_multiset.find(one_hungred));
  EXPECT_FALSE(s21_multiset.contains(one_hungred));

  EXPECT_TRUE(s21_multiset.BLM());
  EXPECT_FALSE(s21_multiset.RedAlert());
}

TEST(S21_multiset, erase_it) {
  std::vector<int> vector{1, 2, 100, 5, 6, -1, 100, -2, 100};
  s21::multiset<int> s21_multiset;
  std::multiset<int> std_multiset;
  for (size_t i = 0; i < vector.size(); i++) {
    std_multiset.insert(vector[i]);
    s21_multiset.insert(vector[i]);
  }
  int one_hungred = 100;

  auto s21_it_hundred = s21_multiset.find(one_hungred);
  auto std_it_hundred = std_multiset.find(one_hungred);

  std_multiset.erase(std_it_hundred);
  s21_multiset.erase(s21_it_hundred);

  EXPECT_EQ(s21_multiset.size(), std_multiset.size());

  EXPECT_TRUE(s21_multiset.contains(one_hungred));
}

TEST(S21_multiset, clean) {
  s21::multiset<int> s21_multiset_1 = {5, 3, 5, 5, 5};
  EXPECT_EQ(s21_multiset_1.size(), 5);

  s21_multiset_1.clear();
  EXPECT_EQ(s21_multiset_1.size(), 0);
  EXPECT_EQ(s21_multiset_1.begin(), s21_multiset_1.end());
}

TEST(S21_multiset, merge) {
  s21::multiset<int> s21_multiset_1 = {5, 3, 5, 5, 5};
  s21::multiset<int> s21_multiset_2 = {1, 1, 2, 2, 0};
  size_t old_size_mset_1 = s21_multiset_1.size();
  EXPECT_EQ(s21_multiset_1.size(), s21_multiset_2.size());

  s21_multiset_1.merge(s21_multiset_2);
  EXPECT_EQ(s21_multiset_1.size(), s21_multiset_2.size() + old_size_mset_1);
  EXPECT_EQ(*(s21_multiset_1.begin()), *(s21_multiset_2.begin()));
  EXPECT_TRUE(s21_multiset_1.BLM());
  EXPECT_FALSE(s21_multiset_1.RedAlert());
}

TEST(S21_multiset, swap) {
  s21::multiset<int> s21_multiset = {0, 5, 10, 15};
  s21::multiset<int> s21_multiset_2 = {0, -5, -10, -15, 5};

  s21_multiset_2.swap(s21_multiset);

  EXPECT_FALSE(s21_multiset_2.contains(-10));
  EXPECT_TRUE(s21_multiset.contains(-10));
  EXPECT_TRUE(s21_multiset_2.contains(10));
}

TEST(S21_multiset, count) {
  s21::multiset<int> s21_multiset_1 = {3, 5, 3, 5, 5, 5};
  EXPECT_EQ(s21_multiset_1.size(), 6);

  EXPECT_EQ(*(s21_multiset_1.begin()), 3);
  EXPECT_EQ(s21_multiset_1.count(3), 2);
  EXPECT_EQ(s21_multiset_1.count(5), 4);
  EXPECT_EQ(s21_multiset_1.count(100), 0);
}

TEST(S21_multiset, lower_bound_1) {
  s21::multiset<int> s21_multiset_1 = {3, 5, 3, 5, 5, 5};
  EXPECT_EQ(s21_multiset_1.size(), 6);

  EXPECT_EQ(s21_multiset_1.begin(), s21_multiset_1.lower_bound(3));
  EXPECT_EQ(*(s21_multiset_1.begin()), *(s21_multiset_1.lower_bound(3)));
  EXPECT_EQ(*(++s21_multiset_1.lower_bound(3)), 3);
}

TEST(S21_multiset, lower_bound_2) {
  s21::multiset<int> s21_multiset_1 = {3, 5, 3, 5, 5, 5};
  std::multiset<int> std_multiset_1 = {3, 5, 3, 5, 5, 5};

  EXPECT_EQ(*(std_multiset_1.lower_bound(3)), *(s21_multiset_1.lower_bound(3)));
}

TEST(S21_multiset, upper_bound_1) {
  s21::multiset<int> s21_multiset_1 = {3, 5, 3, 5, 5, 5};
  EXPECT_EQ(s21_multiset_1.size(), 6);

  EXPECT_FALSE(s21_multiset_1.begin() == s21_multiset_1.upper_bound(3));
  EXPECT_EQ((s21_multiset_1.lower_bound(5)), (s21_multiset_1.upper_bound(3)));
  EXPECT_EQ(*(s21_multiset_1.find(5)), *(s21_multiset_1.upper_bound(3)));
  EXPECT_EQ(*(++s21_multiset_1.upper_bound(3)), 5);
}

TEST(S21_multiset, upper_bound_2) {
  s21::multiset<int> s21_multiset_1 = {3, 5, 3, 5, 5, 5};
  std::multiset<int> std_multiset_1 = {3, 5, 3, 5, 5, 5};

  EXPECT_EQ(*(std_multiset_1.upper_bound(3)), *(s21_multiset_1.upper_bound(3)));
}

TEST(S21_multiset, equal_range_1) {
  s21::multiset<int> s21_multiset_1 = {3, 5, 3, 5, 5, 5};
  auto up_it = s21_multiset_1.upper_bound(5);
  auto lw_it = s21_multiset_1.lower_bound(5);

  EXPECT_EQ(s21_multiset_1.equal_range(3).first, s21_multiset_1.lower_bound(3));
  EXPECT_EQ(s21_multiset_1.equal_range(3).second,
            s21_multiset_1.upper_bound(3));
}

TEST(S21_multiset, equal_range_2) {
  s21::multiset<int> s21_multiset_1 = {3, 5, 3, 5, 5, 5};
  std::multiset<int> std_multiset_1 = {3, 5, 3, 5, 5, 5};

  EXPECT_EQ(*s21_multiset_1.equal_range(3).first,
            *std_multiset_1.equal_range(3).first);
  EXPECT_EQ(*s21_multiset_1.equal_range(3).second,
            *std_multiset_1.equal_range(3).second);
}

TEST(S21_multiset, max_size_int) {
  s21::multiset<int> s21_multiset_1 = {3, 5, 3, 5, 5, 5};
  std::multiset<int> std_multiset_1 = {3, 5, 3, 5, 5, 5};

  EXPECT_EQ(s21_multiset_1.max_size(), std_multiset_1.max_size());
}

TEST(S21_multiset, max_size_double) {
  s21::multiset<double> s21_multiset_1 = {3, 5, 3, 5, 5, 5};
  std::multiset<double> std_multiset_1 = {3, 5, 3, 5, 5, 5};

  EXPECT_EQ(s21_multiset_1.max_size(), std_multiset_1.max_size());
}

TEST(S21_multiset, max_size_char) {
  s21::multiset<char> s21_multiset_1 = {3, 5, 3, 5, 5, 5};
  std::multiset<char> std_multiset_1 = {3, 5, 3, 5, 5, 5};

  EXPECT_EQ(s21_multiset_1.max_size(), std_multiset_1.max_size());
}
