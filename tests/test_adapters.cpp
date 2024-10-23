#include <gtest/gtest.h>
#include <cstdint>
#include <random>

#include "lib/ranges.h"

TEST(TransformAdapterTest, TransformFunctionWorksCorrectly) {
  const std::vector input = {1, 2, 3, 4};
  const std::vector ans = {2, 4, 6, 8};

  auto result = input | ranges::transform([](const int x) { return x * 2; });
  auto iterator = result.begin();

  for (auto r : result) {
    EXPECT_EQ(r, *iterator);
    ++iterator;
  }
}

TEST(FilterAdapterTest, FilterByCondition) {
  const std::vector input = {1, 2, 3, 4};
  const std::vector ans = {2, 4};

  auto result = input | ranges::filter([](const int x) { return x % 2 == 0; });
  auto iterator = result.begin();

  for (auto r : result) {
    EXPECT_EQ(r, *iterator);
    ++iterator;
  }
}

TEST(TakeAdapterTest, TakeFirstNElements) {
  const std::vector input = {1, 2, 3, 4};
  const std::vector ans = {1, 2};

  auto result = input | ranges::take(2);
  auto iterator = result.begin();

  for (auto r : result) {
    EXPECT_EQ(r, *iterator);
    ++iterator;
  }
}

TEST(DropAdapterTest, DropFirstNElements) {
  const std::vector input = {1, 2, 3, 4};
  const std::vector ans = {3, 4};

  auto result = input | ranges::drop(2);
  auto iterator = result.begin();

  for (auto r : result) {
    EXPECT_EQ(r, *iterator);
    ++iterator;
  }
}

TEST(ReverseAdapterTest, ReverseContainer) {
  const std::vector input = {1, 2, 3, 4};
  const std::vector ans = {4, 3, 2, 1};

  auto result = input | ranges::reverse();
  auto iterator = result.begin();

  for (auto r : result) {
    EXPECT_EQ(r, *iterator);
    ++iterator;
  }
}

TEST(KeysAdapterTest, GetKeysFromMap) {
  const std::map<int, std::string> input = {{1, "one"}, {2, "two"}};
  const std::vector<int> ans = {1, 2};

  auto result = input | ranges::keys();
  auto iterator = result.begin();

  for (auto r : result) {
    EXPECT_EQ(r, *iterator);
    ++iterator;
  }
}

TEST(ValuesAdapterTest, GetValuesFromMap) {
  const std::map<int, std::string> input = {{1, "one"}, {2, "two"}};
  std::vector<std::string> ans = {"one", "two"};

  auto result = input | ranges::values();
  auto iterator = result.begin();

  for (auto r : result) {
    EXPECT_EQ(r, *iterator);
    ++iterator;
  }
}
