#pragma once
#include <iostream>
#include <random>
#include <limits>

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

#include "myMatrix.h"
#include "binomialHeap.h"
#include "binaryHeap.h"

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
			for (size_t j = 0; j < data[i].size(); ++j) {
				std::cout << data[i][j].first << " " << data[i][j].second << "; ";
			}
			std::cout << std::endl;
		}
	}
	void scan() {
		size_t e, en;
		T w;
		for (size_t i = 0; i < data.size(); ++i) {
			std::cout << "Enter how many vertices are adjacented with vertex " << i << ". Than enter all adjacent vertices with its number and weights in a row: " << std::endl;
			std::cin >> en;
			for (size_t j = 0; j < en; ++j) {
				std::cin >> e >> w;
				data[i].push_back(std::make_pair(e, w));
			}
			std::cout << std::endl;
		}
	}
	void generate() {
		std::random_device r;
		std::default_random_engine e(r());
		std::uniform_int_distribution<size_t> gen_int(0, data.size());
		std::uniform_real_distribution<double> gen_double(0.0, 1000.0);

		for (size_t i = 0; i < data.size(); ++i) {
			for (size_t j = 0; j < gen_int(e); ++j) {
//				data[i].pushBack()
			}
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
		for (const T& d : dist)
			if (d == std::numeric_limits<T>::max())
				return false;
		return true;
	}
};

