#include <gtest/gtest.h>
#include "CCircuitalBuffer.cpp"
#include "CCircuitalBufferExt.cpp"
#include <sstream>
#include <algorithm>

TEST(StableBufferTestSuite, EmptyBuffer) {
  CCircuitalBuffer<int> a;
  ASSERT_EQ(a.size(), 0);
}

TEST(StableBufferTestSuite, ZeroSizeBuffer) {
  CCircuitalBuffer<int> a(0);
  ASSERT_EQ(a.size(), 0);
}

TEST(StableBufferTestSuite, EmptyCheck1) {
  CCircuitalBuffer<int> a;
  ASSERT_TRUE(a.empty());
}

TEST(StableBufferTestSuite, EmptyCheck2) {
  CCircuitalBuffer<int> a = {1, 4, 5};
  ASSERT_FALSE(a.empty());
}

TEST(StableBufferTestSuite, EmptyCheck3) {
  CCircuitalBuffer<int> a = {7};
  ASSERT_FALSE(a.empty());
}

TEST(StableBufferTestSuite, CreateCheck1) {
  CCircuitalBuffer<int> a(5, 7);
  CCircuitalBuffer<int> b = {7, 7, 7, 7, 7};
  ASSERT_TRUE(a == b);
}

TEST(StableBufferTestSuite, CreateCheck2) {
  CCircuitalBuffer<int> a = {2, 3, 4};
  CCircuitalBuffer<int> b = {1, 2, 3, 4, 5};
  CCircuitalBuffer<int> c(b.begin() + 1, b.end() - 1);
  ASSERT_TRUE(a == c);
}

TEST(StableBufferTestSuite, SizeCheck1) {
  CCircuitalBuffer<int> a = {7, 4, 2};
  ASSERT_EQ(a.size(), 3);
}

TEST(StableBufferTestSuite, SizeCheck2) {
  CCircuitalBuffer<int> a(8);
  ASSERT_EQ(a.size(), 0);
}

TEST(StableBufferTestSuite, SizeCheck3) {
  CCircuitalBuffer<int> a = {7, 4, 2};
  ASSERT_EQ(a.size(), a.end() - a.begin());
}

TEST(StableBufferTestSuite, MaxSizeCheck1) {
  CCircuitalBuffer<int> a = {7, 4, 2};
  ASSERT_EQ(a.max_size(), 3);
}

TEST(StableBufferTestSuite, MaxSizeCheck2) {
  CCircuitalBuffer<int> a(8);
  ASSERT_EQ(a.max_size(), 8);
}

TEST(StableBufferTestSuite, FrontCheck) {
  CCircuitalBuffer<int> a = {9, 2, 3, 6, 8};
  ASSERT_TRUE(a.front() == *(a.cbegin()));
}

TEST(StableBufferTestSuite, BackCheck) {
  CCircuitalBuffer<int> a = {9, 2, 3, 6, 8};
  ASSERT_TRUE(a.back() == *(a.end() - 1));
}

TEST(StableBufferTestSuite, EqualityCheck) {
  CCircuitalBuffer<int> a = {9, 2, 3, 6, 8};
  ASSERT_TRUE(a == a);
}

TEST(StableBufferTestSuite, EqualityCheck2) {
  CCircuitalBuffer<int> a = {9, 2, 3, 6, 8};
  CCircuitalBuffer<int> b = {9, 3, 6, 8};
  ASSERT_FALSE(a == b);
}

TEST(StableBufferTestSuite, EqualityCheck3) {
  CCircuitalBuffer<int> a = {9, 2, 3, 6, 8};
  CCircuitalBuffer<int> b = {9, 2, 4, 6, 8};
  ASSERT_FALSE(a == b);
}

TEST(StableBufferTestSuite, EqualityCheck4) {
  CCircuitalBuffer<int> a = {9, 2, 3, 6, 8};
  CCircuitalBuffer<int> b = {9, 2, 4, 6, 8, 5};
  ASSERT_FALSE(a == b);
}

TEST(StableBufferTestSuite, NEqualityCheck) {
  CCircuitalBuffer<int> a = {9, 2, 3, 6, 8};
  ASSERT_FALSE(a != a);
}

TEST(StableBufferTestSuite, NEqualityCheck2) {
  CCircuitalBuffer<int> a = {9, 2, 3, 6, 8};
  CCircuitalBuffer<int> b = {9, 3, 6, 8};
  ASSERT_TRUE(a != b);
}

TEST(StableBufferTestSuite, NEqualityCheck3) {
  CCircuitalBuffer<int> a = {9, 2, 3, 6, 8};
  CCircuitalBuffer<int> b = {9, 2, 4, 6, 8};
  ASSERT_TRUE(a != b);
}

TEST(StableBufferTestSuite, NEqualityCheck4) {
  CCircuitalBuffer<int> a = {9, 2, 3, 6, 8};
  CCircuitalBuffer<int> b = {9, 2, 4, 6, 8, 5};
  ASSERT_TRUE(a != b);
}

TEST(StableBufferTestSuite, BeginCheck1) {
  CCircuitalBuffer<int> a = {9, 2, 3, 6, 8};
  ASSERT_EQ(*(a.begin()), 9);
}

TEST(StableBufferTestSuite, BeginCheck2) {
  CCircuitalBuffer<int> a = {8, 9, 2, 3, 6, 8};
  ASSERT_EQ(*(a.begin()), 8);
}

TEST(StableBufferTestSuite, EndCheck1) {
  CCircuitalBuffer<int> a = {9, 2, 3, 6, 8};
  ASSERT_EQ(*(a.end() - 1), 8);
}

TEST(StableBufferTestSuite, EndCheck2) {
  CCircuitalBuffer<int> a = {8, 9, 2, 3, 6, 8, 7};
  ASSERT_EQ(*(a.end() - 1), 7);
}

TEST(StableBufferTestSuite, PushBackCheck1) {
  CCircuitalBuffer<int> a(3);
  CCircuitalBuffer<int> b = {8, 9, 2};
  ASSERT_FALSE(a == b);
  a.push_back(8);
  ASSERT_FALSE(a == b);
  a.push_back(9);
  ASSERT_FALSE(a == b);
  a.push_back(2);
  ASSERT_TRUE(a == b);
}

TEST(StableBufferTestSuite, PushBackCheck2) {
  CCircuitalBuffer<int> a = {8, 9, 2, 3, 6, 8, 7};
  std::stringstream buffer;
  std::streambuf *old = std::cerr.rdbuf(buffer.rdbuf());

  a.push_back(5);

  std::cerr.rdbuf(old);

  std::string output = buffer.str();
  EXPECT_EQ(output, "Attempt to add amount of elements, that exceeds capacity\n");
}

TEST(StableBufferTestSuite, EmplaceBackCheck) {
  CCircuitalBuffer<char> a(3);
  CCircuitalBuffer<char> b = {'h', 'i', '!'};
  a.emplace_back('h');
  a.emplace_back('i');
  a.emplace_back('!');
  ASSERT_TRUE(a == b);
}

TEST(StableBufferTestSuite, EmplaceFrontCheck) {
  CCircuitalBuffer<char> a(3);
  CCircuitalBuffer<char> b = {'h', 'i', '!'};
  a.emplace_front('!');
  a.emplace_front('i');
  a.emplace_front('h');
  ASSERT_TRUE(a == b);
}

TEST(StableBufferTestSuite, EmplaceCheck) {
  CCircuitalBuffer<char> a(3);
  CCircuitalBuffer<char> b = {'h', 'i', '!'};
  a.emplace_back('h');
  a.emplace_back('!');
  a.emplace(a.begin() + 1, 'i');
  ASSERT_TRUE(a == b);
}

TEST(StableBufferTestSuite, PushFrontCheck1) {
  CCircuitalBuffer<int> a(3);
  CCircuitalBuffer<int> b = {8, 9, 2};
  ASSERT_FALSE(a == b);
  a.push_front(2);
  ASSERT_FALSE(a == b);
  a.push_front(9);
  ASSERT_FALSE(a == b);
  a.push_front(8);
  ASSERT_TRUE(a == b);
}

TEST(StableBufferTestSuite, PushFrontCheck2) {
  CCircuitalBuffer<int> a = {8, 9, 2, 3, 6, 8, 7};
  std::stringstream buffer;
  std::streambuf *old = std::cerr.rdbuf(buffer.rdbuf());

  a.push_front(5);

  std::cerr.rdbuf(old);

  std::string output = buffer.str();
  EXPECT_EQ(output, "Attempt to add amount of elements, that exceeds capacity\n");
}

TEST(StableBufferTestSuite, PopBackCheck1) {
  CCircuitalBuffer<int> a = {8, 9, 2, 3, 6, 8, 7};
  CCircuitalBuffer<int> b = {8, 9, 2, 3, 6, 8, 7, 5};
  b.pop_back();
  ASSERT_TRUE(a == b);
  b.pop_back();
  ASSERT_FALSE(a == b);
}

TEST(StableBufferTestSuite, PopBackCheck2) {
  CCircuitalBuffer<int> a = {};
  std::stringstream buffer;
  std::streambuf *old = std::cerr.rdbuf(buffer.rdbuf());

  a.pop_back();

  std::cerr.rdbuf(old);

  std::string output = buffer.str();
  EXPECT_EQ(output, "Attempt to delete an element from an empty buffer\n");
}

TEST(StableBufferTestSuite, PopFrontCheck1) {
  CCircuitalBuffer<int> a = {8, 9, 2, 3, 6, 8, 7};
  CCircuitalBuffer<int> b = {5, 8, 9, 2, 3, 6, 8, 7};
  b.pop_front();
  ASSERT_TRUE(a == b);
  b.pop_front();
  ASSERT_FALSE(a == b);
}

TEST(StableBufferTestSuite, PopFrontCheck2) {
  CCircuitalBuffer<int> a = {};
  std::stringstream buffer;
  std::streambuf *old = std::cerr.rdbuf(buffer.rdbuf());

  a.pop_front();

  std::cerr.rdbuf(old);

  std::string output = buffer.str();
  EXPECT_EQ(output, "Attempt to delete an element from an empty buffer\n");
}

TEST(StableBufferTestSuite, PushPopCheck1) {
  CCircuitalBuffer<int> a = {8, 9, 2, 3, 6, 8, 7};
  CCircuitalBuffer<int> b = {9, 2, 3, 6, 8, 4, 2};
  a.pop_back();
  a.pop_front();
  a.push_back(4);
  a.push_back(2);
  ASSERT_TRUE(a == b);
}

TEST(StableBufferTestSuite, PushPopCheck2) {
  CCircuitalBuffer<int> a = {8, 9, 2, 3, 6, 8, 7};
  CCircuitalBuffer<int> b = {2, 4, 9, 2, 3, 6, 8};
  a.pop_back();
  a.pop_front();
  a.push_front(4);
  a.push_front(2);
  ASSERT_TRUE(a == b);
}

TEST(StableBufferTestSuite, PushPopCheck3) {
  CCircuitalBuffer<int> a = {8, 9, 2, 3, 6, 8, 7};
  CCircuitalBuffer<int> b = {2, 9, 2, 3, 6, 8, 4};
  a.pop_back();
  a.pop_front();
  a.push_back(4);
  a.push_front(2);
  ASSERT_TRUE(a == b);
}

TEST(StableBufferTestSuite, PushPopCheck4) {
  CCircuitalBuffer<int> a = {8, 9, 2, 3, 6, 8, 7};
  CCircuitalBuffer<int> b = {3, 6, 8};
  a.pop_back();
  a.pop_front();
  a.pop_front();
  a.pop_front();
  ASSERT_TRUE(a == b);
}

TEST(StableBufferTestSuite, InsertCheck1) {
  CCircuitalBuffer<int> a(3);
  CCircuitalBuffer<int> b = {8, 6, 3};
  a.insert(a.begin(), 3);
  a.insert(a.begin(), 6);
  a.insert(a.begin(), 8);
  ASSERT_TRUE(a == b);
}

TEST(StableBufferTestSuite, InsertCheck2) {
  CCircuitalBuffer<int> a(6);
  CCircuitalBuffer<int> b = {4, 4, 3, 3, 1, 2};
  a.push_back(1);
  a.push_back(2);
  a.insert(a.begin(), 2, 3);
  a.insert(a.begin(), 2, 4);
  ASSERT_TRUE(a == b);
}

TEST(StableBufferTestSuite, InsertCheck3) {
  CCircuitalBuffer<int> a(6);
  CCircuitalBuffer<int> b = {3, 4, 4, 3, 1, 2};
  a.push_back(1);
  a.push_back(2);
  a.insert(a.begin(), 2, 3);
  a.insert(a.begin() + 1, 2, 4);
  ASSERT_TRUE(a == b);
}

TEST(StableBufferTestSuite, InsertCheck4) {
  CCircuitalBuffer<int> a(6);
  CCircuitalBuffer<int> b = {3, 3, 1, 2, 4, 4};
  a.push_back(1);
  a.push_back(2);
  a.insert(a.begin(), 2, 3);
  a.insert(a.end() - 1 + 1, 2, 4);
  ASSERT_TRUE(a == b);
}

TEST(StableBufferTestSuite, InsertCheck5) {
  CCircuitalBuffer<int> a(6);
  CCircuitalBuffer<int> b = {3, 3, 1, 2, 4, 4};
  CCircuitalBuffer<int> c = {1, 2, 4, 4, 5, 5};
  a.insert(a.begin(), b.begin() + 2, b.end());
  a.insert(a.end(), 2, 5);
  ASSERT_TRUE(a == c);
}

TEST(StableBufferTestSuite, InsertCheck6) {
  CCircuitalBuffer<int> a(6);
  CCircuitalBuffer<int> b = {3, 3, 1, 2, 4, 4};
  a.insert(a.begin(), b.begin(), b.end());
  ASSERT_TRUE(a == b);
  std::stringstream buffer;
  std::streambuf *old = std::cerr.rdbuf(buffer.rdbuf());

  a.insert(a.begin(), b.begin(), b.end());

  std::cerr.rdbuf(old);

  std::string output = buffer.str();
  EXPECT_EQ(output, "Out of size\n");
}

TEST(StableBufferTestSuite, InsertCheck7) {
  CCircuitalBuffer<int> a(6);
  CCircuitalBuffer<int> b = {3, 2, 1};
  a.insert(a.begin(), 3);
  a.insert(a.begin() + 1, 1);
  a.insert(a.begin() + 1, 2);
  ASSERT_TRUE(a == b);
}

TEST(StableBufferTestSuite, InsertCheck8) {
  CCircuitalBuffer<int> a(6);
  CCircuitalBuffer<int> b = {2, 3, 9};
  CCircuitalBuffer<int> c = {2, 2, 8, 3, 9};
  a.insert(a.begin(), {2, 3, 9});
  ASSERT_TRUE(a == b);
  a.insert(a.begin() + 1, {2, 8});
  ASSERT_TRUE(a == c);
}

TEST(StableBufferTestSuite, EraseCheck1) {
  CCircuitalBuffer<int> a = {1, 2, 3, 4, 5, 6};
  CCircuitalBuffer<int> b = {2, 3, 4, 5, 6};
  CCircuitalBuffer<int> c = {2, 3, 4, 6};
  CCircuitalBuffer<int> d = {2, 3, 4};

  a.erase(a.begin());
  ASSERT_TRUE(a == b);

  a.erase(a.end() - 2);
  ASSERT_TRUE(a == c);

  a.erase(a.begin() + 3);
  ASSERT_TRUE(a == d);
}

TEST(StableBufferTestSuite, EraseCheck2) {
  CCircuitalBuffer<int> a = {1, 2, 3, 4, 5, 6};

  a.erase(a.begin(), a.end());
  ASSERT_TRUE(a.empty());
}

TEST(StableBufferTestSuite, EraseCheck3) {
  CCircuitalBuffer<int> a = {1, 2, 3, 4, 5, 6};
  CCircuitalBuffer<int> b = {1, 5, 6};

  a.erase(a.begin() + 1, a.end() - 2);
  ASSERT_TRUE(a == b);
}

TEST(StableBufferTestSuite, ByIndexCheck) {
  CCircuitalBuffer<int> a = {1, 2, 3, 4, 5, 6};

  EXPECT_THROW(a[-1], std::out_of_range);
  ASSERT_EQ(a[0], 1);
  ASSERT_EQ(a[1], 2);
  ASSERT_EQ(a[2], 3);
  ASSERT_EQ(a[3], 4);
  ASSERT_EQ(a[4], 5);
  ASSERT_EQ(a[5], 6);
  EXPECT_THROW(a[6], std::out_of_range);

  EXPECT_THROW(a.at(-1), std::out_of_range);
  ASSERT_EQ(a.at(0), 1);
  ASSERT_EQ(a.at(1), 2);
  ASSERT_EQ(a.at(2), 3);
  ASSERT_EQ(a.at(3), 4);
  ASSERT_EQ(a.at(4), 5);
  ASSERT_EQ(a.at(5), 6);
  EXPECT_THROW(a.at(6), std::out_of_range);
}

TEST(StableBufferTestSuite, ClearCheck1) {
  CCircuitalBuffer<int> a = {1, 2, 3, 4, 5, 6};
  a.clear();
  ASSERT_TRUE(a.empty());
}

TEST(StableBufferTestSuite, ClearCheck2) {
  CCircuitalBuffer<int> a = {};
  a.clear();
  ASSERT_TRUE(a.empty());
}

TEST(StableBufferTestSuite, ClearCheck3) {
  CCircuitalBuffer<int> a;
  a.clear();
  ASSERT_TRUE(a.empty());
}

TEST(StableBufferTestSuite, AssignCheck1) {
  CCircuitalBuffer<int> a = {1, 2, 3};
  CCircuitalBuffer<int> b = {3, 4, 5};
  CCircuitalBuffer<int> c = {3, 4};

  a.assign(b.begin(), b.end() - 1);
  ASSERT_TRUE(a == c);

  CCircuitalBuffer<int> d = {3, 4, 6, 7};
  std::stringstream buffer;
  std::streambuf *old = std::cerr.rdbuf(buffer.rdbuf());

  a.assign(d.begin(), d.end());

  std::cerr.rdbuf(old);

  std::string output = buffer.str();
  EXPECT_EQ(output, "Out of size\n");
}

TEST(StableBufferTestSuite, AssignCheck2) {
  CCircuitalBuffer<int> a = {1, 2, 3};
  CCircuitalBuffer<int> b = {2, 7, 21};
  a.assign({2, 7, 21});
  ASSERT_TRUE(a == b);

  std::stringstream buffer;
  std::streambuf *old = std::cerr.rdbuf(buffer.rdbuf());

  a.assign({3, 4, 6, 7});

  std::cerr.rdbuf(old);

  std::string output = buffer.str();
  EXPECT_EQ(output, "Out of size\n");
}

TEST(StableBufferTestSuite, AssignCheck3) {
  CCircuitalBuffer<int> a = {1, 2, 3, 4};
  CCircuitalBuffer<int> b = {2, 2, 2};
  a.assign(3, 2);
  ASSERT_TRUE(a == b);

  std::stringstream buffer;
  std::streambuf *old = std::cerr.rdbuf(buffer.rdbuf());

  a.assign(5, 7);

  std::cerr.rdbuf(old);

  std::string output = buffer.str();
  EXPECT_EQ(output, "Out of size\n");
}

TEST(StableBufferTestSuite, SortCheck1) {
  CCircuitalBuffer<int> a = {1, 6, 2, 7, -1, 99, 3, -2, 4};
  CCircuitalBuffer<int> b = {-2, -1, 1, 2, 3, 4, 6, 7, 99};
  std::sort(a.begin(), a.end());
  ASSERT_TRUE(a == b);
}

TEST(StableBufferTestSuite, SortCheck2) {
  CCircuitalBuffer<int> a = {6, 4, 1, -10, 7, 22, 4, 0};
  CCircuitalBuffer<int> b = {22, 7, 6, 4, 4, 1, 0, -10};
  std::sort(a.begin(), a.end(), std::greater<>());
  ASSERT_TRUE(a == b);
}

TEST(StableBufferTestSuite, FindCheck1) {
  CCircuitalBuffer<int> a = {1, 6, 2, 7, -1, 99, 3, -2, 4};
  int ind = std::distance(a.begin(), std::find(a.begin(), a.end(), 99));
  ASSERT_EQ(ind, 5);
}

TEST(StableBufferTestSuite, FindCheck2) {
  CCircuitalBuffer<int> a = {6, 4, 1, -10, 7, 22, 4, 0};
  int ind = std::distance(a.begin(), std::find(a.begin(), a.end(), 6));
  ASSERT_EQ(ind, 0);
}

TEST(StableBufferTestSuite, RotateCheck1) {
  CCircuitalBuffer<int> a = {6, 4, 1, -10, 7, 22, 4, 0};
  CCircuitalBuffer<int> b = {1, -10, 7, 22, 4, 0, 6, 4};
  std::rotate(a.begin(), a.begin() + 2, a.end());
  ASSERT_TRUE(a == b);
}

TEST(StableBufferTestSuite, RotateCheck2) {
  CCircuitalBuffer<int> a = {6, 4, 1, -10, 7, 22, 4, 0};
  CCircuitalBuffer<int> b = {6, 4, 1, -10, 7, 22, 4, 0};
  std::rotate(a.begin(), a.end(), a.end());
  ASSERT_TRUE(a == b);
}

TEST(StableBufferTestSuite, EmptyBufferExt) {
  CCircuitalBufferExt<int> a;
  ASSERT_EQ(a.size(), 0);
}

TEST(StableBufferTestSuite, ZeroSizeBufferExt) {
  CCircuitalBufferExt<int> a(0);
  ASSERT_EQ(a.size(), 0);
}

TEST(StableBufferTestSuite, EmptyCheck1Ext) {
  CCircuitalBufferExt<int> a;
  ASSERT_TRUE(a.empty());
}

TEST(StableBufferTestSuite, EmptyCheck2Ext) {
  CCircuitalBufferExt<int> a = {1, 4, 5};
  ASSERT_FALSE(a.empty());
}

TEST(StableBufferTestSuite, EmptyCheck3Ext) {
  CCircuitalBufferExt<int> a = {7};
  ASSERT_FALSE(a.empty());
}

TEST(StableBufferTestSuite, CreateCheck1Ext) {
  CCircuitalBufferExt<int> a(5, 7);
  CCircuitalBufferExt<int> b = {7, 7, 7, 7, 7};
  ASSERT_TRUE(a == b);
}

TEST(StableBufferTestSuite, CreateCheck2Ext) {
  CCircuitalBufferExt<int> a = {2, 3, 4};
  CCircuitalBufferExt<int> b = {1, 2, 3, 4, 5};
  CCircuitalBufferExt<int> c(b.begin() + 1, b.end() - 1);
  ASSERT_TRUE(a == c);
}

TEST(StableBufferTestSuite, SizeCheck1Ext) {
  CCircuitalBufferExt<int> a = {7, 4, 2};
  ASSERT_EQ(a.size(), 3);
}

TEST(StableBufferTestSuite, SizeCheck2Ext) {
  CCircuitalBufferExt<int> a(8);
  ASSERT_EQ(a.size(), 0);
}

TEST(StableBufferTestSuite, SizeCheck3Ext) {
  CCircuitalBufferExt<int> a = {7, 4, 2};
  ASSERT_EQ(a.size(), a.end() - a.begin());
}

TEST(StableBufferTestSuite, MaxSizeCheck1Ext) {
  CCircuitalBufferExt<int> a = {7, 4, 2};
  ASSERT_EQ(a.max_size(), 3);
}

TEST(StableBufferTestSuite, MaxSizeCheck2Ext) {
  CCircuitalBufferExt<int> a(8);
  ASSERT_EQ(a.max_size(), 8);
}

TEST(StableBufferTestSuite, FrontCheckExt) {
  CCircuitalBufferExt<int> a = {9, 2, 3, 6, 8};
  ASSERT_TRUE(a.front() == *(a.cbegin()));
}

TEST(StableBufferTestSuite, BackCheckExt) {
  CCircuitalBufferExt<int> a = {9, 2, 3, 6, 8};
  ASSERT_TRUE(a.back() == *(a.end() - 1));
}

TEST(StableBufferTestSuite, EqualityCheckExt) {
  CCircuitalBufferExt<int> a = {9, 2, 3, 6, 8};
  ASSERT_TRUE(a == a);
}

TEST(StableBufferTestSuite, EqualityCheck2Ext) {
  CCircuitalBufferExt<int> a = {9, 2, 3, 6, 8};
  CCircuitalBufferExt<int> b = {9, 3, 6, 8};
  ASSERT_FALSE(a == b);
}

TEST(StableBufferTestSuite, EqualityCheck3Ext) {
  CCircuitalBufferExt<int> a = {9, 2, 3, 6, 8};
  CCircuitalBufferExt<int> b = {9, 2, 4, 6, 8};
  ASSERT_FALSE(a == b);
}

TEST(StableBufferTestSuite, EqualityCheck4Ext) {
  CCircuitalBufferExt<int> a = {9, 2, 3, 6, 8};
  CCircuitalBufferExt<int> b = {9, 2, 4, 6, 8, 5};
  ASSERT_FALSE(a == b);
}

TEST(StableBufferTestSuite, NEqualityCheckExt) {
  CCircuitalBufferExt<int> a = {9, 2, 3, 6, 8};
  ASSERT_FALSE(a != a);
}

TEST(StableBufferTestSuite, NEqualityCheck2Ext) {
  CCircuitalBufferExt<int> a = {9, 2, 3, 6, 8};
  CCircuitalBufferExt<int> b = {9, 3, 6, 8};
  ASSERT_TRUE(a != b);
}

TEST(StableBufferTestSuite, NEqualityCheck3Ext) {
  CCircuitalBufferExt<int> a = {9, 2, 3, 6, 8};
  CCircuitalBufferExt<int> b = {9, 2, 4, 6, 8};
  ASSERT_TRUE(a != b);
}

TEST(StableBufferTestSuite, NEqualityCheck4Ext) {
  CCircuitalBufferExt<int> a = {9, 2, 3, 6, 8};
  CCircuitalBufferExt<int> b = {9, 2, 4, 6, 8, 5};
  ASSERT_TRUE(a != b);
}

TEST(StableBufferTestSuite, BeginCheck1Ext) {
  CCircuitalBufferExt<int> a = {9, 2, 3, 6, 8};
  ASSERT_EQ(*(a.begin()), 9);
}

TEST(StableBufferTestSuite, BeginCheck2Ext) {
  CCircuitalBufferExt<int> a = {8, 9, 2, 3, 6, 8};
  ASSERT_EQ(*(a.begin()), 8);
}

TEST(StableBufferTestSuite, EndCheck1Ext) {
  CCircuitalBufferExt<int> a = {9, 2, 3, 6, 8};
  ASSERT_EQ(*(a.end() - 1), 8);
}

TEST(StableBufferTestSuite, EndCheck2Ext) {
  CCircuitalBufferExt<int> a = {8, 9, 2, 3, 6, 8, 7};
  ASSERT_EQ(*(a.end() - 1), 7);
}

TEST(StableBufferTestSuite, PushBackCheck1Ext) {
  CCircuitalBufferExt<int> a(3);
  CCircuitalBufferExt<int> b = {8, 9, 2};
  ASSERT_FALSE(a == b);
  a.push_back(8);
  ASSERT_FALSE(a == b);
  a.push_back(9);
  ASSERT_FALSE(a == b);
  a.push_back(2);
  ASSERT_TRUE(a == b);
}

TEST(StableBufferTestSuite, PushBackCheck2Ext) {
  CCircuitalBufferExt<int> a = {8, 9, 2, 3, 6, 8, 7};
  a.push_back(5);
  ASSERT_EQ(a.max_size(), 14);
}

TEST(StableBufferTestSuite, EmplaceBackCheckExt) {
  CCircuitalBufferExt<char> a(3);
  CCircuitalBufferExt<char> b = {'h', 'i', '!'};
  a.emplace_back('h');
  a.emplace_back('i');
  a.emplace_back('!');
  ASSERT_TRUE(a == b);
}

TEST(StableBufferTestSuite, EmplaceFrontCheckExt) {
  CCircuitalBufferExt<char> a(3);
  CCircuitalBufferExt<char> b = {'h', 'i', '!'};
  a.emplace_front('!');
  a.emplace_front('i');
  a.emplace_front('h');
  ASSERT_TRUE(a == b);
}

TEST(StableBufferTestSuite, EmplaceCheckExt) {
  CCircuitalBufferExt<char> a(3);
  CCircuitalBufferExt<char> b = {'h', 'i', '!'};
  a.emplace_back('h');
  a.emplace_back('!');
  a.emplace(a.begin() + 1, 'i');
  ASSERT_TRUE(a == b);
}

TEST(StableBufferTestSuite, PushFrontCheck1Ext) {
  CCircuitalBufferExt<int> a(3);
  CCircuitalBufferExt<int> b = {8, 9, 2};
  ASSERT_FALSE(a == b);
  a.push_front(2);
  ASSERT_FALSE(a == b);
  a.push_front(9);
  ASSERT_FALSE(a == b);
  a.push_front(8);
  ASSERT_TRUE(a == b);
}

TEST(StableBufferTestSuite, PushFrontCheck2Ext) {
  CCircuitalBufferExt<int> a = {8, 9, 2, 3, 6, 8, 7};
  a.push_front(5);
  ASSERT_EQ(a.max_size(), 14);
}

TEST(StableBufferTestSuite, PopBackCheck1Ext) {
  CCircuitalBufferExt<int> a = {8, 9, 2, 3, 6, 8, 7};
  CCircuitalBufferExt<int> b = {8, 9, 2, 3, 6, 8, 7, 5};
  b.pop_back();
  ASSERT_TRUE(a == b);
  b.pop_back();
  ASSERT_FALSE(a == b);
}

TEST(StableBufferTestSuite, PopBackCheck2Ext) {
  CCircuitalBufferExt<int> a = {};
  std::stringstream buffer;
  std::streambuf *old = std::cerr.rdbuf(buffer.rdbuf());

  a.pop_back();

  std::cerr.rdbuf(old);

  std::string output = buffer.str();
  EXPECT_EQ(output, "Attempt to delete an element from an empty buffer\n");
}

TEST(StableBufferTestSuite, PopFrontCheck1Ext) {
  CCircuitalBufferExt<int> a = {8, 9, 2, 3, 6, 8, 7};
  CCircuitalBufferExt<int> b = {5, 8, 9, 2, 3, 6, 8, 7};
  b.pop_front();
  ASSERT_TRUE(a == b);
  b.pop_front();
  ASSERT_FALSE(a == b);
}

TEST(StableBufferTestSuite, PopFrontCheck2Ext) {
  CCircuitalBufferExt<int> a = {};
  std::stringstream buffer;
  std::streambuf *old = std::cerr.rdbuf(buffer.rdbuf());

  a.pop_front();

  std::cerr.rdbuf(old);

  std::string output = buffer.str();
  EXPECT_EQ(output, "Attempt to delete an element from an empty buffer\n");
}

TEST(StableBufferTestSuite, PushPopCheck1Ext) {
  CCircuitalBufferExt<int> a = {8, 9, 2, 3, 6, 8, 7};
  CCircuitalBufferExt<int> b = {9, 2, 3, 6, 8, 4, 2};
  a.pop_back();
  a.pop_front();
  a.push_back(4);
  a.push_back(2);
  ASSERT_TRUE(a == b);
}

TEST(StableBufferTestSuite, PushPopCheck2Ext) {
  CCircuitalBufferExt<int> a = {8, 9, 2, 3, 6, 8, 7};
  CCircuitalBufferExt<int> b = {2, 4, 9, 2, 3, 6, 8};
  a.pop_back();
  a.pop_front();
  a.push_front(4);
  a.push_front(2);
  ASSERT_TRUE(a == b);
}

TEST(StableBufferTestSuite, PushPopCheck3Ext) {
  CCircuitalBufferExt<int> a = {8, 9, 2, 3, 6, 8, 7};
  CCircuitalBufferExt<int> b = {2, 9, 2, 3, 6, 8, 4};
  a.pop_back();
  a.pop_front();
  a.push_back(4);
  a.push_front(2);
  ASSERT_TRUE(a == b);
}

TEST(StableBufferTestSuite, PushPopCheck4Ext) {
  CCircuitalBufferExt<int> a = {8, 9, 2, 3, 6, 8, 7};
  CCircuitalBufferExt<int> b = {3, 6, 8};
  a.pop_back();
  a.pop_front();
  a.pop_front();
  a.pop_front();
  ASSERT_TRUE(a == b);
}

TEST(StableBufferTestSuite, InsertCheck1Ext) {
  CCircuitalBufferExt<int> a(3);
  CCircuitalBufferExt<int> b = {8, 6, 3};
  a.insert(a.begin(), 3);
  a.insert(a.begin(), 6);
  a.insert(a.begin(), 8);
  ASSERT_TRUE(a == b);
}

TEST(StableBufferTestSuite, InsertCheck2Ext) {
  CCircuitalBufferExt<int> a(6);
  CCircuitalBufferExt<int> b = {4, 4, 3, 3, 1, 2};
  a.push_back(1);
  a.push_back(2);
  a.insert(a.begin(), 2, 3);
  a.insert(a.begin(), 2, 4);
  ASSERT_TRUE(a == b);
}

TEST(StableBufferTestSuite, InsertCheck3Ext) {
  CCircuitalBufferExt<int> a(6);
  CCircuitalBufferExt<int> b = {3, 4, 4, 3, 1, 2};
  a.push_back(1);
  a.push_back(2);
  a.insert(a.begin(), 2, 3);
  a.insert(a.begin() + 1, 2, 4);
  ASSERT_TRUE(a == b);
}

TEST(StableBufferTestSuite, InsertCheck4Ext) {
  CCircuitalBufferExt<int> a(6);
  CCircuitalBufferExt<int> b = {3, 3, 1, 2, 4, 4};
  a.push_back(1);
  a.push_back(2);
  a.insert(a.begin(), 2, 3);
  a.insert(a.end() - 1 + 1, 2, 4);
  ASSERT_TRUE(a == b);
}

TEST(StableBufferTestSuite, InsertCheck5Ext) {
  CCircuitalBufferExt<int> a(6);
  CCircuitalBufferExt<int> b = {3, 3, 1, 2, 4, 4};
  CCircuitalBufferExt<int> c = {1, 2, 4, 4, 5, 5};
  a.insert(a.begin(), b.begin() + 2, b.end());
  a.insert(a.end(), 2, 5);
  ASSERT_TRUE(a == c);
}

TEST(StableBufferTestSuite, InsertCheck6Ext) {
  CCircuitalBufferExt<int> a(6);
  CCircuitalBufferExt<int> b = {3, 3, 1, 2, 4, 4};
  a.insert(a.begin(), b.begin(), b.end());
  ASSERT_TRUE(a == b);
  a.insert(a.begin(), b.begin(), b.end());
  ASSERT_EQ(a.size(), 12);
}

TEST(StableBufferTestSuite, InsertCheck7Ext) {
  CCircuitalBufferExt<int> a(6);
  CCircuitalBufferExt<int> b = {3, 2, 1};
  a.insert(a.begin(), 3);
  a.insert(a.begin() + 1, 1);
  a.insert(a.begin() + 1, 2);
  ASSERT_TRUE(a == b);
}

TEST(StableBufferTestSuite, InsertCheck8Ext) {
  CCircuitalBufferExt<int> a(6);
  CCircuitalBufferExt<int> b = {2, 3, 9};
  CCircuitalBufferExt<int> c = {2, 2, 8, 3, 9};
  a.insert(a.begin(), {2, 3, 9});
  ASSERT_TRUE(a == b);
  a.insert(a.begin() + 1, {2, 8});
  ASSERT_TRUE(a == c);
}

TEST(StableBufferTestSuite, EraseCheck1Ext) {
  CCircuitalBufferExt<int> a = {1, 2, 3, 4, 5, 6};
  CCircuitalBufferExt<int> b = {2, 3, 4, 5, 6};
  CCircuitalBufferExt<int> c = {2, 3, 4, 6};
  CCircuitalBufferExt<int> d = {2, 3, 4};

  a.erase(a.begin());
  ASSERT_TRUE(a == b);

  a.erase(a.end() - 2);
  ASSERT_TRUE(a == c);

  a.erase(a.begin() + 3);
  ASSERT_TRUE(a == d);
}

TEST(StableBufferTestSuite, EraseCheck2Ext) {
  CCircuitalBufferExt<int> a = {1, 2, 3, 4, 5, 6};

  a.erase(a.begin(), a.end());
  ASSERT_TRUE(a.empty());
}

TEST(StableBufferTestSuite, EraseCheck3Ext) {
  CCircuitalBufferExt<int> a = {1, 2, 3, 4, 5, 6};
  CCircuitalBufferExt<int> b = {1, 5, 6};

  a.erase(a.begin() + 1, a.end() - 2);
  ASSERT_TRUE(a == b);
}

TEST(StableBufferTestSuite, ByIndexCheckExt) {
  CCircuitalBufferExt<int> a = {1, 2, 3, 4, 5, 6};

  EXPECT_THROW(a[-1], std::out_of_range);
  ASSERT_EQ(a[0], 1);
  ASSERT_EQ(a[1], 2);
  ASSERT_EQ(a[2], 3);
  ASSERT_EQ(a[3], 4);
  ASSERT_EQ(a[4], 5);
  ASSERT_EQ(a[5], 6);
  EXPECT_THROW(a[6], std::out_of_range);

  EXPECT_THROW(a.at(-1), std::out_of_range);
  ASSERT_EQ(a.at(0), 1);
  ASSERT_EQ(a.at(1), 2);
  ASSERT_EQ(a.at(2), 3);
  ASSERT_EQ(a.at(3), 4);
  ASSERT_EQ(a.at(4), 5);
  ASSERT_EQ(a.at(5), 6);
  EXPECT_THROW(a.at(6), std::out_of_range);
}

TEST(StableBufferTestSuite, ClearCheck1Ext) {
  CCircuitalBufferExt<int> a = {1, 2, 3, 4, 5, 6};
  a.clear();
  ASSERT_TRUE(a.empty());
}

TEST(StableBufferTestSuite, ClearCheck2Ext) {
  CCircuitalBufferExt<int> a = {};
  a.clear();
  ASSERT_TRUE(a.empty());
}

TEST(StableBufferTestSuite, ClearCheck3Ext) {
  CCircuitalBufferExt<int> a;
  a.clear();
  ASSERT_TRUE(a.empty());
}

TEST(StableBufferTestSuite, AssignCheck1Ext) {
  CCircuitalBufferExt<int> a = {1, 2, 3};
  CCircuitalBufferExt<int> b = {3, 4, 5};
  CCircuitalBufferExt<int> c = {3, 4};

  a.assign(b.begin(), b.end() - 1);
  ASSERT_TRUE(a == c);

  CCircuitalBufferExt<int> d = {3, 4, 6, 7};

  a.assign(d.begin(), d.end());
  ASSERT_EQ(a.size(), 4);
}

TEST(StableBufferTestSuite, AssignCheck2Ext) {
  CCircuitalBufferExt<int> a = {1, 2, 3};
  CCircuitalBufferExt<int> b = {2, 7, 21};
  a.assign({2, 7, 21});
  ASSERT_TRUE(a == b);

  a.assign({3, 4, 6, 7});
  ASSERT_EQ(a.max_size(), 4);
}

TEST(StableBufferTestSuite, AssignCheck3Ext) {
  CCircuitalBufferExt<int> a = {1, 2, 3, 4};
  CCircuitalBufferExt<int> b = {2, 2, 2};
  a.assign(3, 2);
  ASSERT_TRUE(a == b);

  a.assign(5, 7);

  ASSERT_EQ(a.max_size(), 8);
}

TEST(StableBufferTestSuite, SortCheck1Ext) {
  CCircuitalBufferExt<int> a = {1, 6, 2, 7, -1, 99, 3, -2, 4};
  a.push_back(2);
  CCircuitalBufferExt<int> b = {-2, -1, 1, 2, 2, 3, 4, 6, 7, 99};
  std::sort(a.begin(), a.end());
  ASSERT_TRUE(a == b);
}

TEST(StableBufferTestSuite, SortCheck2Ext) {
  CCircuitalBufferExt<int> a = {6, 4, 1, -10, 7, 22, 4, 0};
  a.push_back(8);
  CCircuitalBufferExt<int> b = {22, 8, 7, 6, 4, 4, 1, 0, -10};
  std::sort(a.begin(), a.end(), std::greater<>());
  ASSERT_TRUE(a == b);
}

TEST(StableBufferTestSuite, FindCheck1Ext) {
  CCircuitalBufferExt<int> a = {1, 6, 2, 7, -1, 99, 3, -2, 4};
  a.push_front(99);
  int ind = std::distance(a.begin(), std::find(a.begin(), a.end(), 99));
  ASSERT_EQ(ind, 0);
}

TEST(StableBufferTestSuite, FindCheck2Ext) {
  CCircuitalBufferExt<int> a = {6, 4, 1, -10, 7, 22, 4, 0};
  a.push_front(-2);
  int ind = std::distance(a.begin(), std::find(a.begin(), a.end(), 6));
  ASSERT_EQ(ind, 1);
}

TEST(StableBufferTestSuite, RotateCheck1Ext) {
  CCircuitalBufferExt<int> a = {6, 4, 1, -10, 7, 22, 4, 0};
  a.push_back(77);
  CCircuitalBufferExt<int> b = {1, -10, 7, 22, 4, 0, 77, 6, 4};
  std::rotate(a.begin(), a.begin() + 2, a.end());
  ASSERT_TRUE(a == b);
}

TEST(StableBufferTestSuite, RotateCheck2Ext) {
  CCircuitalBufferExt<int> a = {6, 4, 1, -10, 7, 22, 4, 0};
  a.push_back(77);
  CCircuitalBufferExt<int> b = {6, 4, 1, -10, 7, 22, 4, 0, 77};
  std::rotate(a.begin(), a.end(), a.end());
  ASSERT_TRUE(a == b);
}
