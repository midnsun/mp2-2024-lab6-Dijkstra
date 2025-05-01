#include <gtest.h>
#include "myGraph.h"
#include "binomialHeap.h"
#include "binaryHeap.h"
#include <fstream>
#include <vector>

typedef Dijkstra<double, binaryHeap> D1;
typedef Dijkstra<double, binomialHeap> D2;

TEST(dijkstra, can_binary_heap_dijkstra)
{
	myGraph<double> G(10);
	G.generate(15);

	ASSERT_NO_THROW(D1 D(G, 0));
}

TEST(dijkstra, can_binomial_heap_dijkstra)
{
	myGraph<double> G(10);
	G.generate(15);

	ASSERT_NO_THROW(D2 D(G, 0));
}

TEST(dijkstra, correct_binary_heap_calculating_dijkstra)
{
	myGraph<double> G(15);
	std::string s = "2 5 20 1 15 3 0 15 6 0 2 25 3 1 25 3 10 7 70 2 2 10 8 50 1 9 10 2 0 20 10 30 3 1 0 7 40 10 10 4 6 40 2 70 8 30 12 60 4 7 30 12 5 13 70 3 50 2 4 10 14 25 3 5 30 6 10 11 10 2 10 10 12 35 4 11 35 7 60 8 5 13 70 2 12 70 8 70 1 9 25 7";
	std::istringstream s1;
	s1.str(s);
	G.scan(s1);
	std::vector<double> example = { 55, 40, 65, 75, std::numeric_limits<double>::max(), 75, 40, 0, 30, std::numeric_limits<double>::max(), 50, 60, 35, 100, std::numeric_limits<double>::max() };

	Dijkstra<double, binaryHeap> D(G, 7);
	EXPECT_EQ(D.dist.size(), example.size());
	for (size_t i = 0; i < D.dist.size(); ++i) {
		EXPECT_EQ(D.dist[i], example[i]);
	}
}

TEST(dijkstra, correct_binomial_heap_calculating_dijkstra)
{
	myGraph<double> G(15);
	std::string s = "2 5 20 1 15 3 0 15 6 0 2 25 3 1 25 3 10 7 70 2 2 10 8 50 1 9 10 2 0 20 10 30 3 1 0 7 40 10 10 4 6 40 2 70 8 30 12 60 4 7 30 12 5 13 70 3 50 2 4 10 14 25 3 5 30 6 10 11 10 2 10 10 12 35 4 11 35 7 60 8 5 13 70 2 12 70 8 70 1 9 25 7";
	std::istringstream s1;
	s1.str(s);
	G.scan(s1);
	std::vector<double> example = { 55, 40, 65, 75, std::numeric_limits<double>::max(), 75, 40, 0, 30, std::numeric_limits<double>::max(), 50, 60, 35, 100, std::numeric_limits<double>::max() };

	Dijkstra<double, binomialHeap> D(G, 7);
	EXPECT_EQ(D.dist.size(), example.size());
	for (size_t i = 0; i < D.dist.size(); ++i) {
		EXPECT_EQ(D.dist[i], example[i]);
	}
}

TEST(dijkstra, incorrect_binomial_heap_calculating_dijkstra)
{
	myGraph<double> G(15);
	std::string s = "2 5 20 1 15 3 0 15 6 0 2 25 3 1 25 3 10 7 70 2 2 10 8 50 1 9 10 2 0 20 10 30 3 1 0 7 40 10 10 4 6 40 2 70 8 30 12 60 4 7 30 12 5 13 70 3 50 2 4 10 14 25 3 5 30 6 10 11 10 2 10 10 12 35 4 11 35 7 60 8 5 13 70 2 12 70 8 70 1 9 25 7";
	std::istringstream s1;
	s1.str(s);
	G.scan(s1);
	std::vector<double> example = { 55, 40, 65, 75, std::numeric_limits<double>::max(), 75, 40, 0, 30, std::numeric_limits<double>::max(), 50, 60, 35, 100, std::numeric_limits<double>::max() };

	ASSERT_ANY_THROW(D2 D(G, 15));
}

TEST(dijkstra, can_get_distance)
{
	myGraph<double> G(15);
	std::string s = "2 5 20 1 15 3 0 15 6 0 2 25 3 1 25 3 10 7 70 2 2 10 8 50 1 9 10 2 0 20 10 30 3 1 0 7 40 10 10 4 6 40 2 70 8 30 12 60 4 7 30 12 5 13 70 3 50 2 4 10 14 25 3 5 30 6 10 11 10 2 10 10 12 35 4 11 35 7 60 8 5 13 70 2 12 70 8 70 1 9 25 7";
	std::istringstream s1;
	s1.str(s);
	G.scan(s1);
	std::vector<double> example = { 55, 40, 65, 75, std::numeric_limits<double>::max(), 75, 40, 0, 30, std::numeric_limits<double>::max(), 50, 60, 35, 100, std::numeric_limits<double>::max() };

	Dijkstra<double, binomialHeap> D(G, 7);
	ASSERT_NO_THROW(D.getDistance(0));
}

TEST(dijkstra, cannot_get_distance)
{
	myGraph<double> G(15);
	std::string s = "2 5 20 1 15 3 0 15 6 0 2 25 3 1 25 3 10 7 70 2 2 10 8 50 1 9 10 2 0 20 10 30 3 1 0 7 40 10 10 4 6 40 2 70 8 30 12 60 4 7 30 12 5 13 70 3 50 2 4 10 14 25 3 5 30 6 10 11 10 2 10 10 12 35 4 11 35 7 60 8 5 13 70 2 12 70 8 70 1 9 25 7";
	std::istringstream s1;
	s1.str(s);
	G.scan(s1);
	std::vector<double> example = { 55, 40, 65, 75, std::numeric_limits<double>::max(), 75, 40, 0, 30, std::numeric_limits<double>::max(), 50, 60, 35, 100, std::numeric_limits<double>::max() };

	Dijkstra<double, binomialHeap> D(G, 7);
	ASSERT_ANY_THROW(D.getDistance(15));
}

TEST(dijkstra, get_distance_is_correct)
{
	myGraph<double> G(15);
	std::string s = "2 5 20 1 15 3 0 15 6 0 2 25 3 1 25 3 10 7 70 2 2 10 8 50 1 9 10 2 0 20 10 30 3 1 0 7 40 10 10 4 6 40 2 70 8 30 12 60 4 7 30 12 5 13 70 3 50 2 4 10 14 25 3 5 30 6 10 11 10 2 10 10 12 35 4 11 35 7 60 8 5 13 70 2 12 70 8 70 1 9 25 7";
	std::istringstream s1;
	s1.str(s);
	G.scan(s1);
	std::vector<double> example = { 55, 40, 65, 75, std::numeric_limits<double>::max(), 75, 40, 0, 30, std::numeric_limits<double>::max(), 50, 60, 35, 100, std::numeric_limits<double>::max() };

	Dijkstra<double, binomialHeap> D(G, 7);
	for (size_t i = 0; i < D.dist.size(); ++i) {
		EXPECT_EQ(D.getDistance(i), example[i]);
	}
}

TEST(dijkstra, can_is_connected)
{
	myGraph<double> G(15);
	std::string s = "2 5 20 1 15 3 0 15 6 0 2 25 3 1 25 3 10 7 70 2 2 10 8 50 1 9 10 2 0 20 10 30 3 1 0 7 40 10 10 4 6 40 2 70 8 30 12 60 4 7 30 12 5 13 70 3 50 2 4 10 14 25 3 5 30 6 10 11 10 2 10 10 12 35 4 11 35 7 60 8 5 13 70 2 12 70 8 70 1 9 25 7";
	std::istringstream s1;
	s1.str(s);
	G.scan(s1);
	std::vector<double> example = { 55, 40, 65, 75, std::numeric_limits<double>::max(), 75, 40, 0, 30, std::numeric_limits<double>::max(), 50, 60, 35, 100, std::numeric_limits<double>::max() };

	Dijkstra<double, binomialHeap> D(G, 7);
	ASSERT_NO_THROW(D.isConnected());
}

TEST(dijkstra, can_is_connected_is_correct_1)
{
	myGraph<double> G(15);
	std::string s = "2 5 20 1 15 3 0 15 6 0 2 25 3 1 25 3 10 7 70 2 2 10 8 50 1 9 10 2 0 20 10 30 3 1 0 7 40 10 10 4 6 40 2 70 8 30 12 60 4 7 30 12 5 13 70 3 50 2 4 10 14 25 3 5 30 6 10 11 10 2 10 10 12 35 4 11 35 7 60 8 5 13 70 2 12 70 8 70 1 9 25 7";
	std::istringstream s1;
	s1.str(s);
	G.scan(s1);
	std::vector<double> example = { 55, 40, 65, 75, std::numeric_limits<double>::max(), 75, 40, 0, 30, std::numeric_limits<double>::max(), 50, 60, 35, 100, std::numeric_limits<double>::max() };

	Dijkstra<double, binomialHeap> D(G, 7);
	EXPECT_EQ(D.isConnected(), false);
}

TEST(dijkstra, can_is_connected_is_correct_2)
{
	myGraph<double> G(15);
	std::string s = "3 5 20 1 15 9 10 3 0 15 6 0 2 25 3 1 25 3 10 7 70 2 2 10 8 50 1 9 10 2 0 20 10 30 3 1 0 7 40 10 10 4 6 40 2 70 8 30 12 60 4 7 30 12 5 13 70 3 50 2 4 10 14 25 3 5 30 6 10 11 10 2 10 10 12 35 4 11 35 7 60 8 5 13 70 2 12 70 8 70 1 9 25 7";
	std::istringstream s1;
	s1.str(s);
	G.scan(s1);
	std::vector<double> example = { 55, 40, 65, 75, std::numeric_limits<double>::max(), 75, 40, 0, 30, std::numeric_limits<double>::max(), 50, 60, 35, 100, std::numeric_limits<double>::max() };

	Dijkstra<double, binomialHeap> D(G, 7);
	EXPECT_EQ(D.isConnected(), true);
}