#include <gtest.h>
#include "binaryHeap.h"
#include <vector>

template <typename T>
bool isVectorSorted(std::vector<T>& v) {
	if (v.size() <= 1) return true;
	for (size_t i = 0; i < v.size() - 1; ++i) {
		if (v[i] > v[i + 1]) return false;
	}
	return true;
}

typedef binaryHeap<double> Q;

TEST(binaryHeap, can_create)
{
	ASSERT_NO_THROW(Q q);
}

TEST(binaryHeap, can_add)
{
	Q q;
	ASSERT_NO_THROW(q.add(0.0));
}

TEST(binaryHeap, add_is_correct_1)
{
	Q q;
	q.add(0.0);
	EXPECT_EQ(q.data.size(), 1);
	EXPECT_EQ(q.data[0], 0.0);
}

TEST(binaryHeap, can_is_empty)
{
	Q q;
	q.add(0.0);
	ASSERT_NO_THROW(q.isEmpty());
}

TEST(binaryHeap, is_empty_is_correct_1)
{
	Q q;
	q.add(0.0);
	EXPECT_EQ(q.isEmpty(), false);
}

TEST(binaryHeap, is_empty_is_correct_2)
{
	Q q;
//	q.add(0.0);
	EXPECT_EQ(q.isEmpty(), true);
}

TEST(binaryHeap, can_extract_min)
{
	Q q;
	q.add(0.0);
	ASSERT_NO_THROW(q.extractMin());
}

TEST(binaryHeap, extract_min_is_correct_1)
{
	Q q;
	q.add(0.0);
	q.add(1.0);
	EXPECT_EQ(std::abs(q.extractMin()) <= std::numeric_limits<double>::min(), true);
}

TEST(binaryHeap, extract_min_is_correct_2)
{
	Q q;
	q.add(1.0);
	q.add(0.0);
	EXPECT_EQ(std::abs(q.extractMin()) <= std::numeric_limits<double>::min(), true);
}

TEST(binaryHeap, is_empty_is_correct_3)
{
	Q q;
	q.add(0.0);
	q.extractMin();
	EXPECT_EQ(q.isEmpty(), true);
}

TEST(binaryHeap, can_search_min)
{
	Q q;
	q.add(0.0);
	ASSERT_NO_THROW(q.searchMin());
}

TEST(binaryHeap, search_min_is_correct_1)
{
	Q q;
	q.add(0.0);
	q.add(1.0);
	EXPECT_EQ(std::abs(q.searchMin()) <= std::numeric_limits<double>::min(), true);
}

TEST(binaryHeap, search_min_is_correct_2)
{
	Q q;
	q.add(1.0);
	q.add(0.0);
	EXPECT_EQ(std::abs(q.searchMin()) <= std::numeric_limits<double>::min(), true);
}

TEST(binaryHeap, multiple_add_and_extract_is_correct)
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

TEST(binaryHeap, can_slide_up)
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
	ASSERT_NO_THROW(q.slideUp(5));
}

TEST(binaryHeap, can_slide_down)
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
	ASSERT_NO_THROW(q.slideDown(5));
}

TEST(binaryHeap, slide_up_is_correct)
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
	q.data.push_back(-10.0);
	q.slideUp(10);
	EXPECT_EQ(q.data[0], -10.0);
}

TEST(binaryHeap, slide_down_is_correct)
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
	q.data[0] = 10.0;
	q.slideDown(0);
	EXPECT_EQ(q.data[0], -1.0);
}