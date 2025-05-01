#include <gtest.h>
#include "binomialHeap.h"
#include <vector>

template <typename T>
bool isVectorSorted(std::vector<T>& v) {
	if (v.size() <= 1) return true;
	for (size_t i = 0; i < v.size() - 1; ++i) {
		if (v[i] > v[i + 1]) return false;
	}
	return true;
}

typedef binomialHeap<double> Q;

TEST(binomiaHeap, can_create)
{
	ASSERT_NO_THROW(Q q);
}

TEST(binomiaHeap, can_add)
{
	Q q;
	ASSERT_NO_THROW(q.add(0.0));
}

TEST(binomiaHeap, add_is_correct_1)
{
	Q q;
	q.add(0.0);
	EXPECT_NE(q.head, nullptr);
	EXPECT_EQ(q.head->data, 0.0);
}

TEST(binomiaHeap, can_is_empty)
{
	Q q;
	q.add(0.0);
	ASSERT_NO_THROW(q.isEmpty());
}

TEST(binomiaHeap, is_empty_is_correct_1)
{
	Q q;
	q.add(0.0);
	EXPECT_EQ(q.isEmpty(), false);
}

TEST(binomiaHeap, is_empty_is_correct_2)
{
	Q q;
	//	q.add(0.0);
	EXPECT_EQ(q.isEmpty(), true);
}

TEST(binomiaHeap, can_extract_min)
{
	Q q;
	q.add(0.0);
	ASSERT_NO_THROW(q.extractMin());
}

TEST(binomiaHeap, extract_min_is_correct_1)
{
	Q q;
	q.add(0.0);
	q.add(1.0);
	EXPECT_EQ(std::abs(q.extractMin()) <= std::numeric_limits<double>::min(), true);
}

TEST(binomiaHeap, extract_min_is_correct_2)
{
	Q q;
	q.add(1.0);
	q.add(0.0);
	EXPECT_EQ(std::abs(q.extractMin()) <= std::numeric_limits<double>::min(), true);
}

TEST(binomiaHeap, is_empty_is_correct_3)
{
	Q q;
	q.add(0.0);
	q.extractMin();
	EXPECT_EQ(q.isEmpty(), true);
}

TEST(binomiaHeap, can_search_min)
{
	Q q;
	q.add(0.0);
	ASSERT_NO_THROW(q.searchMin());
}

TEST(binomiaHeap, search_min_is_correct_1)
{
	Q q;
	q.add(0.0);
	q.add(1.0);
	EXPECT_EQ(std::abs(q.searchMin()) <= std::numeric_limits<double>::min(), true);
}

TEST(binomiaHeap, search_min_is_correct_2)
{
	Q q;
	q.add(1.0);
	q.add(0.0);
	EXPECT_EQ(std::abs(q.searchMin()) <= std::numeric_limits<double>::min(), true);
}

TEST(binomiaHeap, multiple_add_and_extract_is_correct)
{
	Q q;
	q.add(1.0);
	q.add(0.0);
	q.add(2.0);
	q.add(-1.0);
	q.add(3.0);
	q.add(3.0);
	q.add(4.0);
	q.add(-2.0);
	q.add(10.0);
	q.add(5.0);
	std::vector<double> v;
	while (!q.isEmpty()) {
		v.push_back(q.extractMin());
	}
	EXPECT_EQ(true, isVectorSorted(v));
}