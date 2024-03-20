#include <queue>

#include "s21_containers_test.h"

TEST(S21_queue, Constructor) {
  s21::queue<int> s21_que;
  std::queue<int> std_que;
  EXPECT_EQ(s21_que.empty(), std_que.empty());
  EXPECT_EQ(s21_que.size(), std_que.size());
}

TEST(S21_queue, Constructor_initializer_list) {
  s21::queue<int> s21_que = {0, 5, 10, 15};
  std::queue<int> std_que;
  for (int i = 0; i <= 15; i += 5) std_que.push(i);

  EXPECT_EQ(s21_que.empty(), std_que.empty());
  EXPECT_EQ(s21_que.size(), std_que.size());
  EXPECT_EQ(s21_que.front(), std_que.front());
}

TEST(S21_queue, Constructor_copy) {
  s21::queue<int> s21_que = {0, 5, 10, 15};
  s21::queue<int> s21_que_copy(s21_que);
  std::queue<int> std_que;
  for (int i = 0; i <= 15; i += 5) std_que.push(i);
  std::queue<int> std_que_copy(std_que);

  EXPECT_EQ(s21_que.empty(), std_que.empty());
  EXPECT_EQ(s21_que.size(), std_que.size());
  EXPECT_EQ(s21_que.front(), std_que.front());

  EXPECT_EQ(s21_que_copy.empty(), std_que_copy.empty());
  EXPECT_EQ(s21_que_copy.size(), std_que_copy.size());
  EXPECT_EQ(s21_que_copy.front(), std_que_copy.front());
}

TEST(S21_queue, Constructor_move) {
  s21::queue<int> s21_que = {0, 5, 10, 15};
  s21::queue<int> s21_que_move(std::move(s21_que));
  std::queue<int> std_que;
  for (int i = 0; i <= 15; i += 5) std_que.push(i);
  std::queue<int> std_que_move(std::move(std_que));

  EXPECT_EQ(s21_que.empty(), std_que.empty());
  EXPECT_EQ(s21_que.size(), std_que.size());

  EXPECT_EQ(s21_que_move.empty(), std_que_move.empty());
  EXPECT_EQ(s21_que_move.size(), std_que_move.size());
  EXPECT_EQ(s21_que_move.back(), std_que_move.back());
}

TEST(S21_queue, Operator_copy) {
  s21::queue<int> s21_que = {0, 5, 10, 15};
  s21::queue<int> s21_que_copy = s21_que;
  std::queue<int> std_que;
  for (int i = 0; i <= 15; i += 5) std_que.push(i);
  std::queue<int> std_que_copy = std_que;

  EXPECT_EQ(s21_que.empty(), std_que.empty());
  EXPECT_EQ(s21_que.size(), std_que.size());
  EXPECT_EQ(s21_que.front(), std_que.front());

  EXPECT_EQ(s21_que_copy.empty(), std_que_copy.empty());
  EXPECT_EQ(s21_que_copy.size(), std_que_copy.size());
  EXPECT_EQ(s21_que_copy.front(), std_que_copy.front());
}

TEST(S21_queue, Operator_move) {
  s21::queue<int> s21_que = {0, 5, 10, 15};
  s21::queue<int> s21_que_move = std::move(s21_que);
  std::queue<int> std_que;
  for (int i = 0; i <= 15; i += 5) std_que.push(i);
  std::queue<int> std_que_move = std::move(std_que);

  EXPECT_EQ(s21_que.empty(), std_que.empty());
  EXPECT_EQ(s21_que.size(), std_que.size());

  EXPECT_EQ(s21_que_move.empty(), std_que_move.empty());
  EXPECT_EQ(s21_que_move.size(), std_que_move.size());
  EXPECT_EQ(s21_que_move.front(), std_que_move.front());
}

TEST(S21_queue, Push_int) {
  s21::queue<int> s21_que;
  std::queue<int> std_que;
  for (int i = 0; i <= 15; i += 5) {
    s21_que.push(i);
    std_que.push(i);
  }

  EXPECT_EQ(s21_que.size(), std_que.size());
  EXPECT_EQ(s21_que.front(), std_que.front());
}

TEST(S21_queue, Push_float) {
  s21::queue<float> s21_que;
  std::queue<float> std_que;
  float x = 0.001;
  s21_que.push(x);
  std_que.push(x);

  s21_que.push(8.1);
  std_que.push(8.1);

  s21_que.push(17.1);
  std_que.push(17.1);

  EXPECT_EQ(s21_que.size(), std_que.size());
  EXPECT_EQ(s21_que.front(), std_que.front());
}

TEST(S21_queue, Push_double) {
  s21::queue<double> s21_que;
  std::queue<double> std_que;
  double x = 0.001;
  s21_que.push(x);
  std_que.push(x);

  s21_que.push(8.1);
  std_que.push(8.1);

  s21_que.push(17.1);
  std_que.push(17.1);

  EXPECT_EQ(s21_que.size(), std_que.size());
  EXPECT_EQ(s21_que.front(), std_que.front());
}

TEST(S21_queue, Push_char) {
  s21::queue<double> s21_que;
  std::queue<double> std_que;
  char x = '0';
  s21_que.push(x);
  std_que.push(x);

  s21_que.push(x + 3);
  std_que.push(x + 3);

  s21_que.push(x + 10);
  std_que.push(x + 10);

  EXPECT_EQ(s21_que.size(), std_que.size());
  EXPECT_EQ(s21_que.front(), std_que.front());
}

TEST(S21_queue, Push_string) {
  s21::queue<std::string> s21_que;
  std::queue<std::string> std_que;
  char x[5] = "123";
  std_que.push(x);
  s21_que.push(x);

  s21_que.push("boba");
  std_que.push("boba");

  s21_que.push("Hello world!");
  std_que.push("Hello world!");

  EXPECT_EQ(s21_que.size(), std_que.size());
  EXPECT_EQ(s21_que.front(), std_que.front());
}

TEST(S21_queue, Pop_int) {
  s21::queue<int> s21_que;
  std::queue<int> std_que;
  for (int i = 0; i <= 15; i += 5) {
    s21_que.push(i);
    std_que.push(i);
  }
  s21_que.pop();
  std_que.pop();

  EXPECT_EQ(s21_que.size(), std_que.size());
  EXPECT_EQ(s21_que.front(), std_que.front());
  while (!s21_que.empty()) {
    s21_que.pop();
    std_que.pop();
  }
  EXPECT_EQ(s21_que.size(), std_que.size());
  EXPECT_EQ(s21_que.empty(), std_que.empty());
}

TEST(S21_queue, Pop_float) {
  s21::queue<float> s21_que;
  std::queue<float> std_que;
  float x = 0.001;
  s21_que.push(x);
  std_que.push(x);

  s21_que.push(8.1);
  std_que.push(8.1);

  s21_que.push(17.1);
  std_que.push(17.1);

  s21_que.pop();
  std_que.pop();

  EXPECT_EQ(s21_que.size(), std_que.size());
  EXPECT_EQ(s21_que.front(), std_que.front());

  while (!s21_que.empty()) {
    s21_que.pop();
    std_que.pop();
  }
  EXPECT_EQ(s21_que.size(), std_que.size());
  EXPECT_EQ(s21_que.empty(), std_que.empty());
}

TEST(S21_queue, Pop_double) {
  s21::queue<double> s21_que;
  std::queue<double> std_que;
  double x = 0.001;
  s21_que.push(x);
  std_que.push(x);

  s21_que.push(8.1);
  std_que.push(8.1);

  s21_que.push(17.1);
  std_que.push(17.1);

  s21_que.pop();
  std_que.pop();
  EXPECT_EQ(s21_que.size(), std_que.size());
  EXPECT_EQ(s21_que.front(), std_que.front());
  while (!s21_que.empty()) {
    s21_que.pop();
    std_que.pop();
  }
  EXPECT_EQ(s21_que.size(), std_que.size());
  EXPECT_EQ(s21_que.empty(), std_que.empty());
}

TEST(S21_queue, Pop_char) {
  s21::queue<double> s21_que;
  std::queue<double> std_que;
  char x = '0';
  s21_que.push(x);
  std_que.push(x);

  s21_que.push(x + 3);
  std_que.push(x + 3);

  s21_que.push(x + 10);
  std_que.push(x + 10);

  s21_que.pop();
  std_que.pop();
  EXPECT_EQ(s21_que.size(), std_que.size());
  EXPECT_EQ(s21_que.front(), std_que.front());
  while (!s21_que.empty()) {
    s21_que.pop();
    std_que.pop();
  }
  EXPECT_EQ(s21_que.size(), std_que.size());
  EXPECT_EQ(s21_que.empty(), std_que.empty());
}

TEST(S21_queue, Pop_string) {
  s21::queue<std::string> s21_que;
  std::queue<std::string> std_que;
  char x[5] = "123";
  std_que.push(x);
  s21_que.push(x);

  s21_que.push("boba");
  std_que.push("boba");

  s21_que.push("Hello world!");
  std_que.push("Hello world!");

  s21_que.pop();
  std_que.pop();
  EXPECT_EQ(s21_que.size(), std_que.size());
  EXPECT_EQ(s21_que.front(), std_que.front());
  while (!s21_que.empty()) {
    s21_que.pop();
    std_que.pop();
  }
  EXPECT_EQ(s21_que.size(), std_que.size());
  EXPECT_EQ(s21_que.empty(), std_que.empty());
}

TEST(S21_queue, Push_s21marix) {
  s21::queue<s21::S21Matrix> s21_que;
  std::queue<s21::S21Matrix> std_que;
  s21::S21Matrix x;
  s21::S21Matrix y(5, 5);
  s21_que.push(x);
  std_que.push(x);

  s21_que.push(x);
  std_que.push(x);

  s21_que.push(y);
  std_que.push(y);

  x = s21_que.front();
  y = std_que.front();
  EXPECT_EQ(s21_que.size(), std_que.size());
  EXPECT_TRUE(x == y);
}

TEST(S21_queue, Pop_s21marix) {
  s21::queue<s21::S21Matrix> s21_que;
  std::queue<s21::S21Matrix> std_que;
  s21::S21Matrix x;
  s21::S21Matrix y(2, 2);
  s21::S21Matrix c(10, 10);
  s21_que.push(x);
  std_que.push(x);
  s21_que.push(y);
  std_que.push(y);
  s21_que.push(c);
  std_que.push(c);

  s21_que.pop();
  std_que.pop();

  x = s21_que.front();
  y = std_que.front();
  EXPECT_EQ(s21_que.size(), std_que.size());
  EXPECT_EQ(s21_que.front(), std_que.front());
  while (!s21_que.empty()) {
    s21_que.pop();
    std_que.pop();
  }
  EXPECT_EQ(s21_que.size(), std_que.size());
  EXPECT_EQ(s21_que.empty(), std_que.empty());
}

TEST(S21_queue, Swap_container) {
  s21::queue<int> s21_que;
  std::queue<int> std_que;
  for (int i = 0; i <= 15; i += 5) {
    s21_que.push(i);
    std_que.push(i);
  }

  s21::queue<int> s21_que_swap = {100};
  std::queue<int> std_que_swap;
  std_que_swap.push(100);

  s21_que.swap(s21_que_swap);
  std_que.swap(std_que_swap);

  EXPECT_EQ(s21_que.size(), std_que.size());
  EXPECT_EQ(s21_que.front(), std_que.front());

  EXPECT_EQ(s21_que_swap.size(), std_que_swap.size());
  EXPECT_EQ(s21_que_swap.front(), std_que_swap.front());
}

TEST(S21_queue, Insert_many_back) {
  s21::queue<int> s21_que;
  std::queue<int> std_que;
  s21_que.insert_many_back(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
  for (int i{1}; i < 11; ++i) {
    EXPECT_EQ(i, s21_que.front());
    s21_que.pop();
  }
}
