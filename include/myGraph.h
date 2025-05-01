#pragma once
#include <iostream>
#include <random>
#include <limits>
//#include "../Graphviz/include/graphviz/gvc.h"
#include "myVector.h"

template<typename T>
bool operator <(const std::pair<size_t, T>& v1, const std::pair<size_t, T>& v2) { return v1.second < v2.second; }
template<typename T>
bool operator >(const std::pair<size_t, T>& v1, const std::pair<size_t, T>& v2) { return v1.second > v2.second; }
template<typename T>
bool operator <=(const std::pair<size_t, T>& v1, const std::pair<size_t, T>& v2) { return v1.second <= v2.second; }
template<typename T>
bool operator >=(const std::pair<size_t, T>& v1, const std::pair<size_t, T>& v2) { return v1.second >= v2.second; }
template<typename T>
bool operator ==(const std::pair<size_t, T>& v1, const std::pair<size_t, T>& v2) { return v1.second == v2.second; }
template<typename T>
bool operator !=(const std::pair<size_t, T>& v1, const std::pair<size_t, T>& v2) { return v1.second != v2.second; }

//#include "myMatrix.h"
//#include "binomialHeap.h"
//#include "binaryHeap.h"

/*
template <typename T>
class myGraph {
	myMatrix<T> data;

public:
	friend class Dijkstra;
	myGraph(size_t n = 0) : data(0) {

	}
	size_t size() const {
		return data.size();
	}
	void print() const {
		for (size_t i = 0; i < data.size(); ++i) {
			for (size_t j = 0; j < data.size(); ++i) {
				std::cout << data(i, j) << " ";
			}
			std::cout << std::endl;
		}
	}
	void scan() {
		std::cout << "Enter the Adjacency matrix:\n";
		for (size_t i = 0; i < data.size(); ++i) {
			for (size_t j = 0; j < data.size(); ++i) {
				std::cin >> data(i, j);
			}
			std::cout << std::endl;
		}
	}
	void generate() {
		std::random_device r;
		std::default_random_engine e(r());
		std::uniform_real_distribution<double> gen(0.0, 1000.0);

		for (size_t i = 0; i < data.size(); ++i) {
			for (size_t j = 0; j < data.size(); ++i) {
				data(i, j) = gen(e);
			}
			data(i, i) = 0.0;
		}
	}
};


template <typename T, template<typename> class Q>
class Dijkstra {
	const myGraph<T>& G;
	myVector<T> dist;
public:
	Dijkstra(const myGraph<T>& _G, size_t v) : G(_G), dist(_G.size(), std::numeric_limits<T>::max()) {
		calculate(v);
	}
	T getDistance(size_t n) {
		return dist[n];
	}
	void calculate(size_t v) {
		if (v >= G.size()) throw std::logic_error("Invalid number of vertex to find distances from");
		Q<std::pair<size_t, T>> q;
		dist[v] = 0;
		q.add(std::make_pair(v, dist[v]));
		std::pair<size_T, T> e;
		size_t i;

		while (!q.isEmpty()) {
			e = q.extractMin();
			if (e.second != dist[e.first]) continue;
			for (i = 0; i < G.data.size(); ++i) {
				if (dist[i] > dist[e.first] + )
			}
		}
	}
	bool isConnected() {
		for (const T& d : dist)
			if d == std::numeric_limits<T>::max()
				return false;
		return true;
	}
};
*/



template <typename T>
class myGraph {
	#ifdef TEST_MODE
	public:
	#endif
	myVector<myVector<std::pair<size_t, T>>> data;

public:
	template <typename U, template<typename> class Q>
	friend class Dijkstra;
	myGraph(size_t n = 0) : data(n) {

	}
	size_t size() const {
		return data.size();
	}
	void print() const {
		
		for (size_t i = 0; i < data.size(); ++i) {
			std::cout << i << '\t';
			for (size_t j = 0; j < data[i].size(); ++j) {
				std::cout << data[i][j].first << " " << data[i][j].second << "; ";
			}
			std::cout << std::endl;
		}
		
		
		/*
		GVC_t* gvc;
		Agraph_t* g;
		FILE* fp;
		gvc = gvContext();
		fp = fopen("../example.dot", "r");
//		g = agread(fp, 0); 
		g = agopen(nullptr, Agdesc_t(), 0);
		gvLayout(gvc, g, "dot");
		gvRender(gvc, g, "plain", stdout);
		gvFreeLayout(gvc, g);
		agclose(g);
		gvFreeContext(gvc);
		*/
		
//		Agraph_t* g;
//		Agnode_t* n, * m;
//		Agedge_t* e;
//		Agsym_t* a;
//		GVC_t* gvc;
//		Agdesc_t desc;
//		desc.directed = true;
//		desc.strict = false;
//		/* set up a graphviz context */
//		gvc = gvContext();
//		/* parse command line args - minimally argv[0] sets layout engine */
//		//		gvParseArgs(gvc, argc, argv);
//		/* Create a simple digraph */
//		char* charG = new char[2]; charG[0] = 'g'; charG[1] = '\0';
//		char* charN = new char[2]; charG[0] = 'n'; charG[1] = '\0';
//		char* charM = new char[2]; charG[0] = 'm'; charG[1] = '\0';
//		char* charCOLOR = new char[6]; charCOLOR[0] = 'c'; charCOLOR[1] = 'o'; charCOLOR[2] = 'l'; charCOLOR[3] = 'o'; charCOLOR[4] = 'r'; charCOLOR[5] = '\0';
//		g = agopen(charG, desc, NULL);
//		n = agnode(g, charN, 1);
//		m = agnode(g, charM, 1);
//		e = agedge(g, n, m, 0, 1);
//		/* Set an attribute - in this case one that affects the visible rendering */
//		agsafeset(n, charCOLOR, "red", "");
//		/* Compute a layout using layout engine from command line args */
//		gvLayoutJobs(gvc, g);
//		/* Write the graph according to -T and -o options */
//		gvRenderJobs(gvc, g);
//		/* Free layout data */
//		gvFreeLayout(gvc, g);
//		/* Free graph structures */
//		agclose(g);
//		/* close output file, free context, and return number of errors */
//		gvFreeContext(gvc);
//		delete[] charG;
//		delete[] charN;
//		delete[] charM;
//		delete[] charCOLOR;
//		
	}
	void scan(std::istream& is) {
		size_t e, en;
		T w;
		for (size_t i = 0; i < data.size(); ++i) {
			std::cout << "Enter how many vertices are adjacented with vertex " << i << ". Than enter all adjacent vertices with its number and weights in a row: " << std::endl;
			is >> en;
			for (size_t j = 0; j < en; ++j) {
				is >> e >> w;
				data[i].push_back(std::make_pair(e, w));
			}
			std::cout << std::endl;
		}
	}
	void generate(size_t edgesCount) {

		std::random_device r;
		std::default_random_engine e(r());
		std::uniform_int_distribution<size_t> gen_int(0, data.size() - 1);
		size_t v1, v2, i;
		std::uniform_real_distribution<double> gen_double(0.0, 1000.0);
		double w;
		bool FLAG;

		while (edgesCount > 0) {
			--edgesCount;
			v1 = gen_int(e);
			v2 = gen_int(e);
			if (v1 == v2) {
				++edgesCount;
				continue;
			}
			FLAG = false;
			for (i = 0; i < data[v1].size(); ++i) {
				if (data[v1][i].first == v2) {
					++edgesCount;
					FLAG = true;
					break;
				}
			}
			if (FLAG) continue;
			w = gen_double(e);
			data[v1].push_back(std::make_pair(v2, T(w)));
		}
	}
};


template <typename T, template<typename> class Q>
class Dijkstra {
	#ifdef TEST_MODE
	public:
	#endif
	const myGraph<T>& G;
	myVector<T> dist;
public:
	Dijkstra(const myGraph<T>& _G, size_t v) : G(_G), dist(_G.size(), std::numeric_limits<T>::max()) {
		calculate(v);
	}
	T getDistance(size_t n) {
		if (n >= G.size()) throw std::logic_error("Invalid number of vertex to find distance to");
		return dist[n];
	}
	void calculate(size_t v) {
		if (v >= G.size()) throw std::logic_error("Invalid number of vertex to find distances from");
		Q<std::pair<size_t, T>> q;
		dist[v] = 0;
		q.add(std::make_pair(v, dist[v]));
		std::pair<size_t, T> e, eit;
		size_t i;

		while (!q.isEmpty()) {
			e = q.extractMin();
			if (e.second != dist[e.first]) continue;
			for (i = 0; i < G.data[e.first].size(); ++i) {
				eit = G.data[e.first][i];
				if (dist[eit.first] > dist[e.first] + eit.second) {
					dist[eit.first] = dist[e.first] + eit.second;
					q.add(std::make_pair(eit.first, dist[eit.first]));
				}
			}
		}
	}
	bool isConnected() {
		for (size_t i = 0; i < dist.size(); ++i)
			if (dist[i] == std::numeric_limits<T>::max())
				return false;
		return true;
	}
};

