#include <stack>
#include <vector>

#include "s21_containers_test.h"

TEST(S21_Stack, Constructor) {
  s21::stack<int> s21_stk;
  std::stack<int> std_stk;
  EXPECT_EQ(s21_stk.empty(), std_stk.empty());
  EXPECT_EQ(s21_stk.size(), std_stk.size());
}

TEST(S21_Stack, Constructor_initializer_list) {
  s21::stack<int> s21_stk = {0, 5, 10, 15};
  std::stack<int> std_stk;
  for (int i = 0; i <= 15; i += 5) std_stk.push(i);

  EXPECT_EQ(s21_stk.empty(), std_stk.empty());
  EXPECT_EQ(s21_stk.size(), std_stk.size());
  EXPECT_EQ(s21_stk.top(), std_stk.top());
}

TEST(S21_Stack, Constructor_copy) {
  s21::stack<int> s21_stk = {0, 5, 10, 15};
  s21::stack<int> s21_stk_copy(s21_stk);
  std::stack<int> std_stk;
  for (int i = 0; i <= 15; i += 5) std_stk.push(i);
  std::stack<int> std_stk_copy(std_stk);

  EXPECT_EQ(s21_stk.empty(), std_stk.empty());
  EXPECT_EQ(s21_stk.size(), std_stk.size());
  EXPECT_EQ(s21_stk.top(), std_stk.top());

  EXPECT_EQ(s21_stk_copy.empty(), std_stk_copy.empty());
  EXPECT_EQ(s21_stk_copy.size(), std_stk_copy.size());
  EXPECT_EQ(s21_stk_copy.top(), std_stk_copy.top());
}

TEST(S21_Stack, Constructor_move) {
  s21::stack<int> s21_stk = {0, 5, 10, 15};
  s21::stack<int> s21_stk_move(std::move(s21_stk));
  std::stack<int> std_stk;
  for (int i = 0; i <= 15; i += 5) std_stk.push(i);
  std::stack<int> std_stk_move(std::move(std_stk));

  EXPECT_EQ(s21_stk.empty(), std_stk.empty());
  EXPECT_EQ(s21_stk.size(), std_stk.size());

  EXPECT_EQ(s21_stk_move.empty(), std_stk_move.empty());
  EXPECT_EQ(s21_stk_move.size(), std_stk_move.size());
  EXPECT_EQ(s21_stk_move.top(), std_stk_move.top());
}

TEST(S21_Stack, Operator_copy_1) {
  s21::stack<int> s21_stk = {0, 5, 10, 15};
  s21::stack<int> s21_stk_copy;
  std::stack<int> std_stk;
  for (int i = 0; i <= 15; i += 5) std_stk.push(i);
  std::stack<int> std_stk_copy;

  s21_stk_copy = s21_stk;
  std_stk_copy = std_stk;

  EXPECT_EQ(s21_stk.empty(), std_stk.empty());
  EXPECT_EQ(s21_stk.size(), std_stk.size());
  EXPECT_EQ(s21_stk.top(), std_stk.top());

  EXPECT_EQ(s21_stk_copy.empty(), std_stk_copy.empty());
  EXPECT_EQ(s21_stk_copy.size(), std_stk_copy.size());
  EXPECT_EQ(s21_stk_copy.top(), std_stk_copy.top());

  EXPECT_EQ(s21_stk_copy.empty(), s21_stk.empty());
  EXPECT_EQ(s21_stk_copy.size(), s21_stk.size());
  EXPECT_EQ(s21_stk_copy.top(), s21_stk.top());
}

TEST(S21_Stack, Operator_copy_2) {
  s21::stack<int> s21_stk = {0, 5, 10, 15};
  s21::stack<int> s21_stk_copy;
  std::stack<int> std_stk;
  for (int i = 0; i <= 15; i += 5) std_stk.push(i);
  std::stack<int> std_stk_copy;

  s21_stk_copy = s21_stk;
  std_stk_copy = std_stk;

  EXPECT_EQ(s21_stk.empty(), std_stk.empty());
  EXPECT_EQ(s21_stk.size(), std_stk.size());
  EXPECT_EQ(s21_stk.top(), std_stk.top());

  EXPECT_EQ(s21_stk_copy.empty(), std_stk_copy.empty());
  EXPECT_EQ(s21_stk_copy.size(), std_stk_copy.size());
  EXPECT_EQ(s21_stk_copy.top(), std_stk_copy.top());

  EXPECT_TRUE(s21_stk_copy.empty() == s21_stk.empty());
  EXPECT_TRUE(s21_stk_copy.size() == s21_stk.size());
  EXPECT_TRUE(s21_stk_copy.top() == s21_stk.top());
}

TEST(S21_Stack, Operator_move) {
  s21::stack<int> s21_stk = {0, 5, 10, 15};
  s21::stack<int> s21_stk_move = std::move(s21_stk);
  std::stack<int> std_stk;
  for (int i = 0; i <= 15; i += 5) std_stk.push(i);
  std::stack<int> std_stk_move = std::move(std_stk);

  EXPECT_EQ(s21_stk.empty(), std_stk.empty());
  EXPECT_EQ(s21_stk.size(), std_stk.size());

  EXPECT_EQ(s21_stk_move.empty(), std_stk_move.empty());
  EXPECT_EQ(s21_stk_move.size(), std_stk_move.size());
  EXPECT_EQ(s21_stk_move.top(), std_stk_move.top());
}

TEST(S21_Stack, Push_int) {
  s21::stack<int> s21_stk;
  std::stack<int> std_stk;
  for (int i = 0; i <= 15; i += 5) {
    s21_stk.push(i);
    std_stk.push(i);
  }

  EXPECT_EQ(s21_stk.size(), std_stk.size());
  EXPECT_EQ(s21_stk.top(), std_stk.top());
}

TEST(S21_Stack, Insert_many_front) {
  s21::stack<int> s21_stk;
  std::stack<int> std_stk;
  for (int i = 0; i <= 15; i += 5) {
    std_stk.push(i);
  }
  s21_stk.insert_many_front(0, 5, 10, 15);

  EXPECT_EQ(s21_stk.size(), std_stk.size());
  EXPECT_EQ(s21_stk.top(), std_stk.top());
}

TEST(S21_Stack, Push_float) {
  s21::stack<float> s21_stk;
  std::stack<float> std_stk;
  float x = 0.001;
  s21_stk.push(x);
  std_stk.push(x);

  s21_stk.push(8.1);
  std_stk.push(8.1);

  s21_stk.push(17.1);
  std_stk.push(17.1);

  EXPECT_EQ(s21_stk.size(), std_stk.size());
  EXPECT_EQ(s21_stk.top(), std_stk.top());
}

TEST(S21_Stack, Push_double) {
  s21::stack<double> s21_stk;
  std::stack<double> std_stk;
  double x = 0.001;
  s21_stk.push(x);
  std_stk.push(x);

  s21_stk.push(8.1);
  std_stk.push(8.1);

  s21_stk.push(17.1);
  std_stk.push(17.1);

  EXPECT_EQ(s21_stk.size(), std_stk.size());
  EXPECT_EQ(s21_stk.top(), std_stk.top());
}

TEST(S21_Stack, Push_char) {
  s21::stack<double> s21_stk;
  std::stack<double> std_stk;
  char x = '0';
  s21_stk.push(x);
  std_stk.push(x);

  s21_stk.push(x + 3);
  std_stk.push(x + 3);

  s21_stk.push(x + 10);
  std_stk.push(x + 10);

  EXPECT_EQ(s21_stk.size(), std_stk.size());
  EXPECT_EQ(s21_stk.top(), std_stk.top());
}

TEST(S21_Stack, Push_string) {
  s21::stack<std::string> s21_stk;
  std::stack<std::string> std_stk;
  char x[5] = "123";
  std_stk.push(x);
  s21_stk.push(x);

  s21_stk.push("boba");
  std_stk.push("boba");

  s21_stk.push("Hello world!");
  std_stk.push("Hello world!");

  EXPECT_EQ(s21_stk.size(), std_stk.size());
  EXPECT_EQ(s21_stk.top(), std_stk.top());
}

TEST(S21_Stack, Pop_int) {
  s21::stack<int> s21_stk;
  std::stack<int> std_stk;
  for (int i = 0; i <= 15; i += 5) {
    s21_stk.push(i);
    std_stk.push(i);
  }
  s21_stk.pop();
  std_stk.pop();

  EXPECT_EQ(s21_stk.size(), std_stk.size());
  EXPECT_EQ(s21_stk.top(), std_stk.top());
  while (!s21_stk.empty()) {
    s21_stk.pop();
    std_stk.pop();
  }
  EXPECT_EQ(s21_stk.size(), std_stk.size());
  EXPECT_EQ(s21_stk.empty(), std_stk.empty());
}

TEST(S21_Stack, Pop_float) {
  s21::stack<float> s21_stk;
  std::stack<float> std_stk;
  float x = 0.001;
  s21_stk.push(x);
  std_stk.push(x);

  s21_stk.push(8.1);
  std_stk.push(8.1);

  s21_stk.push(17.1);
  std_stk.push(17.1);

  s21_stk.pop();
  std_stk.pop();

  EXPECT_EQ(s21_stk.size(), std_stk.size());
  EXPECT_EQ(s21_stk.top(), std_stk.top());

  while (!s21_stk.empty()) {
    s21_stk.pop();
    std_stk.pop();
  }
  EXPECT_EQ(s21_stk.size(), std_stk.size());
  EXPECT_EQ(s21_stk.empty(), std_stk.empty());
}

TEST(S21_Stack, Pop_double) {
  s21::stack<double> s21_stk;
  std::stack<double> std_stk;
  double x = 0.001;
  s21_stk.push(x);
  std_stk.push(x);

  s21_stk.push(8.1);
  std_stk.push(8.1);

  s21_stk.push(17.1);
  std_stk.push(17.1);

  s21_stk.pop();
  std_stk.pop();
  EXPECT_EQ(s21_stk.size(), std_stk.size());
  EXPECT_EQ(s21_stk.top(), std_stk.top());
  while (!s21_stk.empty()) {
    s21_stk.pop();
    std_stk.pop();
  }
  EXPECT_EQ(s21_stk.size(), std_stk.size());
  EXPECT_EQ(s21_stk.empty(), std_stk.empty());
}

TEST(S21_Stack, Pop_char) {
  s21::stack<double> s21_stk;
  std::stack<double> std_stk;
  char x = '0';
  s21_stk.push(x);
  std_stk.push(x);

  s21_stk.push(x + 3);
  std_stk.push(x + 3);

  s21_stk.push(x + 10);
  std_stk.push(x + 10);

  s21_stk.pop();
  std_stk.pop();
  EXPECT_EQ(s21_stk.size(), std_stk.size());
  EXPECT_EQ(s21_stk.top(), std_stk.top());
  while (!s21_stk.empty()) {
    s21_stk.pop();
    std_stk.pop();
  }
  EXPECT_EQ(s21_stk.size(), std_stk.size());
  EXPECT_EQ(s21_stk.empty(), std_stk.empty());
}

TEST(S21_Stack, Pop_string) {
  s21::stack<std::string> s21_stk;
  std::stack<std::string> std_stk;
  char x[5] = "123";
  std_stk.push(x);
  s21_stk.push(x);

  s21_stk.push("boba");
  std_stk.push("boba");

  s21_stk.push("Hello world!");
  std_stk.push("Hello world!");

  s21_stk.pop();
  std_stk.pop();
  EXPECT_EQ(s21_stk.size(), std_stk.size());
  EXPECT_EQ(s21_stk.top(), std_stk.top());
  while (!s21_stk.empty()) {
    s21_stk.pop();
    std_stk.pop();
  }
  EXPECT_EQ(s21_stk.size(), std_stk.size());
  EXPECT_EQ(s21_stk.empty(), std_stk.empty());
}

TEST(S21_Stack, Push_s21marix) {
  s21::stack<s21::S21Matrix> s21_stk;
  std::stack<s21::S21Matrix> std_stk;
  s21::S21Matrix x;
  s21::S21Matrix y(5, 5);
  s21_stk.push(x);
  std_stk.push(x);

  s21_stk.push(x);
  std_stk.push(x);

  s21_stk.push(y);
  std_stk.push(y);

  x = s21_stk.top();
  y = std_stk.top();
  EXPECT_EQ(s21_stk.size(), std_stk.size());
  EXPECT_TRUE(x == y);
}

TEST(S21_Stack, Emplace_s21marix) {
  s21::stack<s21::S21Matrix> s21_stk;
  std::stack<s21::S21Matrix> std_stk;
  s21::S21Matrix x;
  s21::S21Matrix y(2, 2);
  s21::S21Matrix c(10, 10);
  s21_stk.push(x);
  std_stk.push(x);

  s21_stk.emplace(2, 2);
  std_stk.push(y);

  s21_stk.emplace(10, 10);
  std_stk.push(c);

  x = s21_stk.top();
  y = std_stk.top();
  EXPECT_EQ(s21_stk.size(), std_stk.size());
  EXPECT_EQ(s21_stk.top(), std_stk.top());
}

TEST(S21_Stack, Pop_s21marix) {
  s21::stack<s21::S21Matrix> s21_stk;
  std::stack<s21::S21Matrix> std_stk;
  s21::S21Matrix x;
  s21::S21Matrix y(2, 2);
  s21::S21Matrix c(10, 10);
  s21_stk.push(x);
  std_stk.push(x);

  s21_stk.emplace(2, 2);
  std_stk.push(y);

  s21_stk.emplace(10, 10);
  std_stk.push(c);

  s21_stk.pop();
  std_stk.pop();

  x = s21_stk.top();
  y = std_stk.top();
  EXPECT_EQ(s21_stk.size(), std_stk.size());
  EXPECT_EQ(s21_stk.top(), std_stk.top());
  while (!s21_stk.empty()) {
    s21_stk.pop();
    std_stk.pop();
  }
  EXPECT_EQ(s21_stk.size(), std_stk.size());
  EXPECT_EQ(s21_stk.empty(), std_stk.empty());
}

TEST(S21_Stack, Swap_container) {
  s21::stack<int> s21_stk;
  std::stack<int> std_stk;
  for (int i = 0; i <= 15; i += 5) {
    s21_stk.push(i);
    std_stk.push(i);
  }

  s21::stack<int> s21_stk_swap = {100};
  std::stack<int> std_stk_swap;
  std_stk_swap.push(100);

  s21_stk.swap(s21_stk_swap);
  std_stk.swap(std_stk_swap);

  EXPECT_EQ(s21_stk.size(), std_stk.size());
  EXPECT_EQ(s21_stk.top(), std_stk.top());

  EXPECT_EQ(s21_stk_swap.size(), std_stk_swap.size());
  EXPECT_EQ(s21_stk_swap.top(), std_stk_swap.top());
}

TEST(S21_Stack, Another_container) {
  s21::stack<int, std::vector<int>> s21_stk;
  std::stack<int, std::vector<int>> std_stk;
  for (int i = 0; i <= 15; i += 5) {
    s21_stk.push(i);
    std_stk.push(i);
  }

  EXPECT_EQ(s21_stk.size(), std_stk.size());
  EXPECT_EQ(s21_stk.top(), std_stk.top());
}
