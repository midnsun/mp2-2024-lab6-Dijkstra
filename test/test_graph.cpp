#include <gtest.h>
#include "myGraph.h"
#include <fstream>

TEST(myGraph, can_create_myGraph)
{
	ASSERT_NO_THROW(myGraph<double> g);
}

TEST(myGraph, can_create_myGraph_is_correct)
{
	myGraph<double> g;
	EXPECT_EQ(g.data.size(), 0);
}


TEST(myGraph, can_create_myGraph_with_operands)
{
	ASSERT_NO_THROW(myGraph<double> g(5));
}

TEST(myGraph, can_create_myGraph_with_operands_is_correct_1)
{
	myGraph<double> g(5);
	EXPECT_EQ(g.data.size(), 5);
}

TEST(myGraph, can_create_myGraph_with_operands_is_correct_2)
{
	myGraph<double> g(6);
	EXPECT_NE(g.data.size(), 5);
}

TEST(myGraph, can_size)
{
	myGraph<double> g(6);
	ASSERT_NO_THROW(g.size());
}

TEST(myGraph, size_is_correct)
{
	myGraph<double> g(6);
	EXPECT_EQ(g.size(), 6);
}

TEST(myGraph, can_generate) {
	myGraph<double> g(6);
	ASSERT_NO_THROW(g.generate(5));
}

TEST(myGraph, can_print) {
	myGraph<double> g(6);
	g.generate(5);
	ASSERT_NO_THROW(g.print());
}

TEST(myGraph, can_scan) {
	myGraph<double> g(15);
	std::string s = "2 5 20 1 15 3 0 15 6 0 2 25 3 1 25 3 10 7 70 2 2 10 8 50 1 9 10 2 0 20 10 30 3 1 0 7 40 10 10 4 6 40 2 70 8 30 12 60 4 7 30 12 5 13 70 3 50 2 4 10 14 25 3 5 30 6 10 11 10 2 10 10 12 35 4 11 35 7 60 8 5 13 70 2 12 70 8 70 1 9 25 7";
	std::istringstream s1;
	s1.str(s);
	
	ASSERT_NO_THROW(g.scan(s1));
}

TEST(myGraph, scan_is_correct) {
	myGraph<double> g(15);
	std::string s = "2 5 20 1 15 3 0 15 6 0 2 25 3 1 25 3 10 7 70 2 2 10 8 50 1 9 10 2 0 20 10 30 3 1 0 7 40 10 10 4 6 40 2 70 8 30 12 60 4 7 30 12 5 13 70 3 50 2 4 10 14 25 3 5 30 6 10 11 10 2 10 10 12 35 4 11 35 7 60 8 5 13 70 2 12 70 8 70 1 9 25 7";
	std::istringstream s1;
	s1.str(s);

	g.scan(s1);
	g.print();

	EXPECT_EQ(g.data[0].size(), 2); EXPECT_EQ(g.data[0][0], std::make_pair(5ull, 20.0)); EXPECT_EQ(g.data[0][1], std::make_pair(1ull, 15.0));
	EXPECT_EQ(g.data[1].size(), 3); EXPECT_EQ(g.data[1][0], std::make_pair(0ull, 15.0)); EXPECT_EQ(g.data[1][1], std::make_pair(6ull, 0.0)); EXPECT_EQ(g.data[1][2], std::make_pair(2ull, 25.0));
	EXPECT_EQ(g.data[2].size(), 3); EXPECT_EQ(g.data[2][0], std::make_pair(1ull, 25.0)); EXPECT_EQ(g.data[2][1], std::make_pair(3ull, 10.0)); EXPECT_EQ(g.data[2][2], std::make_pair(7ull, 70.0));
	EXPECT_EQ(g.data[3].size(), 2); EXPECT_EQ(g.data[3][0], std::make_pair(2ull, 10.0)); EXPECT_EQ(g.data[3][1], std::make_pair(8ull, 50.0));
	EXPECT_EQ(g.data[4].size(), 1); EXPECT_EQ(g.data[4][0], std::make_pair(9ull, 10.0));
	EXPECT_EQ(g.data[5].size(), 2); EXPECT_EQ(g.data[5][0], std::make_pair(0ull, 20.0)); EXPECT_EQ(g.data[5][1], std::make_pair(10ull, 30.0));
	EXPECT_EQ(g.data[6].size(), 3); EXPECT_EQ(g.data[6][0], std::make_pair(1ull, 0.0)); EXPECT_EQ(g.data[6][1], std::make_pair(7ull, 40.0)); EXPECT_EQ(g.data[6][2], std::make_pair(10ull, 10.0));
	EXPECT_EQ(g.data[7].size(), 4); EXPECT_EQ(g.data[7][0], std::make_pair(6ull, 40.0)); EXPECT_EQ(g.data[7][1], std::make_pair(2ull, 70.0)); EXPECT_EQ(g.data[7][2], std::make_pair(8ull, 30.0)); EXPECT_EQ(g.data[7][3], std::make_pair(12ull, 60.0));
	EXPECT_EQ(g.data[8].size(), 4); EXPECT_EQ(g.data[8][0], std::make_pair(7ull, 30.0)); EXPECT_EQ(g.data[8][1], std::make_pair(12ull, 5.0)); EXPECT_EQ(g.data[8][2], std::make_pair(13ull, 70.0)); EXPECT_EQ(g.data[8][3], std::make_pair(3ull, 50.0));
	EXPECT_EQ(g.data[9].size(), 2); EXPECT_EQ(g.data[9][0], std::make_pair(4ull, 10.0)); EXPECT_EQ(g.data[9][1], std::make_pair(14ull, 25.0));
	EXPECT_EQ(g.data[10].size(), 3); EXPECT_EQ(g.data[10][0], std::make_pair(5ull, 30.0)); EXPECT_EQ(g.data[10][1], std::make_pair(6ull, 10.0)); EXPECT_EQ(g.data[10][2], std::make_pair(11ull, 10.0));
	EXPECT_EQ(g.data[11].size(), 2); EXPECT_EQ(g.data[11][0], std::make_pair(10ull, 10.0)); EXPECT_EQ(g.data[11][1], std::make_pair(12ull, 35.0));
	EXPECT_EQ(g.data[12].size(), 4); EXPECT_EQ(g.data[12][0], std::make_pair(11ull, 35.0)); EXPECT_EQ(g.data[12][1], std::make_pair(7ull, 60.0)); EXPECT_EQ(g.data[12][2], std::make_pair(8ull, 5.0)); EXPECT_EQ(g.data[12][3], std::make_pair(13ull, 70.0));
	EXPECT_EQ(g.data[13].size(), 2); EXPECT_EQ(g.data[13][0], std::make_pair(12ull, 70.0)); EXPECT_EQ(g.data[13][1], std::make_pair(8ull, 70.0));
	EXPECT_EQ(g.data[14].size(), 1); EXPECT_EQ(g.data[14][0], std::make_pair(9ull, 25.0));
}

TEST(myGraph, can_print) {
	myGraph<double> g(15);
	g.generate(10);
	ASSERT_NO_THROW(g.print());
}
