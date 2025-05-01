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

TEST(binomialHeap, can_create)
{
	ASSERT_NO_THROW(Q q);
}

TEST(binomialHeap, can_add)
{
	Q q;
	ASSERT_NO_THROW(q.add(0.0));
}

TEST(binomialHeap, add_is_correct_1)
{
	Q q;
	q.add(0.0);
	EXPECT_NE(q.head, nullptr);
	EXPECT_EQ(q.head->data, 0.0);
}

TEST(binomialHeap, can_is_empty)
{
	Q q;
	q.add(0.0);
	ASSERT_NO_THROW(q.isEmpty());
}

TEST(binomialHeap, is_empty_is_correct_1)
{
	Q q;
	q.add(0.0);
	EXPECT_EQ(q.isEmpty(), false);
}

TEST(binomialHeap, is_empty_is_correct_2)
{
	Q q;
	//	q.add(0.0);
	EXPECT_EQ(q.isEmpty(), true);
}

TEST(binomialHeap, can_extract_min)
{
	Q q;
	q.add(0.0);
	ASSERT_NO_THROW(q.extractMin());
}

TEST(binomialHeap, extract_min_is_correct_1)
{
	Q q;
	q.add(0.0);
	q.add(1.0);
	EXPECT_EQ(q.extractMin(), 0.0);
}

TEST(binomialHeap, extract_min_is_correct_2)
{
	Q q;
	q.add(1.0);
	q.add(0.0);
	EXPECT_EQ(q.extractMin(), 0.0);
}

TEST(binomialHeap, extract_min_changes_min)
{
	Q q;
	q.add(1.0);
	q.add(0.0);
	q.extractMin();
	EXPECT_EQ(q.searchMin(), 1.0);
}

TEST(binomialHeap, extract_min_empty_returns_default)
{
	Q q;
	EXPECT_EQ(q.extractMin(), double());
}

TEST(binomialHeap, search_min_empty_returns_default)
{
	Q q;
	EXPECT_EQ(q.searchMin(), double());
}

TEST(binomialHeap, is_empty_is_correct_3)
{
	Q q;
	q.add(0.0);
	q.extractMin();
	EXPECT_EQ(q.isEmpty(), true);
}

TEST(binomialHeap, can_search_min)
{
	Q q;
	q.add(0.0);
	ASSERT_NO_THROW(q.searchMin());
}

TEST(binomialHeap, search_min_is_correct_1)
{
	Q q;
	q.add(0.0);
	q.add(1.0);
	EXPECT_EQ(q.searchMin(), 0.0);
}

TEST(binomialHeap, search_min_is_correct_2)
{
	Q q;
	q.add(1.0);
	q.add(0.0);
	EXPECT_EQ(q.searchMin(), 0.0);
}

TEST(binomialHeap, multiple_add_and_extract_is_correct)
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

TEST(binomialHeap, can_merge_binomial_trees) {
	Q q;
	Q::Node* h1, *h2, *h = nullptr;
	h1 = new Q::Node{2, nullptr, nullptr, nullptr, 0.0};
	h1->child = new Q::Node{ 1, nullptr, nullptr, h1, 0.5 };
	h1->child->sibling = new Q::Node{ 0, nullptr, nullptr, h1, 2.0 };
	h1->child->child = new Q::Node{ 0, nullptr, nullptr, h1->child, 1.0 };

	h2 = new Q::Node{2, nullptr, nullptr, nullptr, 1.0};
	h2->child = new Q::Node{ 1, nullptr, nullptr, h2, 1.5 };
	h2->child->sibling = new Q::Node{ 0, nullptr, nullptr, h2, 1.0 };
	h2->child->child = new Q::Node{ 0, nullptr, nullptr, h2->child, 2.0 };

	ASSERT_NO_THROW(h = q.mergeBinomialTrees(h1, h2));
	q.head = h;
}

TEST(binomialHeap, merge_binomial_trees_is_correct) {
	Q q;
	Q::Node* h1, * h2, * h;
	h1 = new Q::Node{ 2, nullptr, nullptr, nullptr, 0.0 };
	h1->child = new Q::Node{ 1, nullptr, nullptr, h1, 0.5 };
	h1->child->sibling = new Q::Node{ 0, nullptr, nullptr, h1, 2.0 };
	h1->child->child = new Q::Node{ 0, nullptr, nullptr, h1->child, 1.0 };

	h2 = new Q::Node{ 2, nullptr, nullptr, nullptr, 1.0 };
	h2->child = new Q::Node{ 1, nullptr, nullptr, h2, 1.5 };
	h2->child->sibling = new Q::Node{ 0, nullptr, nullptr, h2, 1.0 };
	h2->child->child = new Q::Node{ 0, nullptr, nullptr, h2->child, 2.0 };

	h = q.mergeBinomialTrees(h1, h2);
	q.head = h;

	EXPECT_EQ(q.extractMin(), 0.0);
	EXPECT_EQ(q.extractMin(), 0.5);
	EXPECT_EQ(q.extractMin(), 1.0);
	EXPECT_EQ(q.extractMin(), 1.0);
	EXPECT_EQ(q.extractMin(), 1.0);
	EXPECT_EQ(q.extractMin(), 1.5);
	EXPECT_EQ(q.extractMin(), 2.0);
	EXPECT_EQ(q.extractMin(), 2.0);
	EXPECT_EQ(q.isEmpty(), true);
}

TEST(binomialHeap, can_merge_binomial_heaps) {
	Q q, qt;
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
	qt.add(2.0);
	qt.add(3.0);
	qt.add(4.0);
	qt.add(-3.0);
	qt.add(2.0);
	qt.add(1.0);
	qt.add(0.0);
	qt.add(-2.0);
	qt.add(10.0);
	qt.add(5.0);
	
	ASSERT_NO_THROW(q.mergeHeap(qt));
}

TEST(binomialHeap, can_merge_binomial_heaps_is_correct) {
	Q q, qt;
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
	qt.add(2.0);
	qt.add(3.0);
	qt.add(4.0);
	qt.add(-3.0);
	qt.add(2.0);
	qt.add(1.0);
	qt.add(0.0);
	qt.add(-2.0);
	qt.add(10.0);
	qt.add(5.0);

	q.mergeHeap(qt);
	EXPECT_EQ(qt.isEmpty(), true);
	EXPECT_EQ(q.extractMin(), -3.0);
	EXPECT_EQ(q.extractMin(), -2.0);
	EXPECT_EQ(q.extractMin(), -2.0);
	EXPECT_EQ(q.extractMin(), -1.0);
	EXPECT_EQ(q.extractMin(), 0.0);
	EXPECT_EQ(q.extractMin(), 0.0);
	EXPECT_EQ(q.extractMin(), 1.0);
	EXPECT_EQ(q.extractMin(), 1.0);
	EXPECT_EQ(q.extractMin(), 2.0);
	EXPECT_EQ(q.extractMin(), 2.0);
	EXPECT_EQ(q.extractMin(), 2.0);
	EXPECT_EQ(q.extractMin(), 3.0);
	EXPECT_EQ(q.extractMin(), 3.0);
	EXPECT_EQ(q.extractMin(), 3.0);
	EXPECT_EQ(q.extractMin(), 4.0);
	EXPECT_EQ(q.extractMin(), 4.0);
	EXPECT_EQ(q.extractMin(), 5.0);
	EXPECT_EQ(q.extractMin(), 5.0);
	EXPECT_EQ(q.extractMin(), 10.0);
	EXPECT_EQ(q.extractMin(), 10.0);
	EXPECT_EQ(q.isEmpty(), true);
}