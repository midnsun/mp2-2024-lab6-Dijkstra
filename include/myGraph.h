#pragma once
#define GVDLL
#include <iostream>
#include <random>
#include <limits>
#include "../Graphviz/include/graphviz/gvc.h"
#include "myVector.h"
#include <string>
#include <iomanip>
#include <sstream>

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
	#ifndef _CMAKE_
	void print() const {
		std::string dotpath = "../example.dot";
		std::string pngpath = "../../image_file.png";
		std::string svgpath = "../../image_file.svg";
		
//		for (size_t i = 0; i < data.size(); ++i) {
//			std::cout << i << '\t';
//			for (size_t j = 0; j < data[i].size(); ++j) {
//				std::cout << data[i][j].first << " " << data[i][j].second << "; ";
//			}
//			std::cout << std::endl;
//		}
//		
//		GVC_t* gvc = gvContext();
//		Agraph_t* g = agopen(const_cast<char*>("G"), Agdirected, nullptr);
//
//		Agnode_t* n1 = agnode(g, const_cast<char*>("Node1"), true);
//		Agnode_t* n2 = agnode(g, const_cast<char*>("Node2"), true);
//
//		agedge(g, n1, n2, nullptr, true);
//		gvLayout(gvc, g, "dot");  // You can use "dot", "neato", etc.
//		gvRenderFilename(gvc, g, "png", pngpath.c_str());
//
//		gvFreeLayout(gvc, g);
//		agclose(g);
//		gvFreeContext(gvc);
//		std::cout << "See your result in image_file.png" << std::endl;

		GVC_t* gvc = gvContext();
		Agraph_t* g = agopen(const_cast<char*>("G"), Agstrictundirected, nullptr); // strict directed
		agattr(g, AGEDGE, const_cast<char*>("label"), const_cast<char*>(""));
		myVector<Agnode_t*> nodes(data.size());
		std::stringstream weightStr;
		weightStr << std::fixed << std::setprecision(2);

		for (size_t i = 0; i < data.size(); ++i) {
			nodes[i] = agnode(g, const_cast<char*>(std::to_string(i).c_str()), 1);
		}

		for (size_t u = 0; u < data.size(); ++u) {
			for (size_t i = 0; i < data[u].size(); ++i) {
				Agedge_t* e = agedge(g, nodes[u], nodes[data[u][i].first], nullptr, 1);
				weightStr.str("");
				weightStr << data[u][i].second;
				agset(e, const_cast<char*>("label"), _strdup(weightStr.str().c_str()));
			}
		}

		gvLayout(gvc, g, "dot");
		gvRenderFilename(gvc, g, "png", pngpath.c_str());
//		gvRenderFilename(gvc, g, "svg", svgpath.c_str());
		gvFreeLayout(gvc, g);
		agclose(g);
		gvFreeContext(gvc);

	}
	#endif
protected:
	void _scan_test(std::istream& is) {
		size_t e, en;
		T w;
		for (size_t i = 0; i < data.size(); ++i) {
//			std::cout << "Enter how many vertices are adjacented with vertex " << i << ". Than enter all adjacent vertices with its number and weights in a row: " << std::endl;
			is >> en;
			for (size_t j = 0; j < en; ++j) {
				is >> e >> w;
				data[i].push_back(std::make_pair(e, w));
			}
//			std::cout << std::endl;
		}
	}
public:
	void scan(std::istream& is) {
		size_t e, en;
		T w;
		for (size_t i = 0; i < data.size(); ++i) {
			std::cout << "Enter how many vertices are adjacented with vertex " << i << ". Than enter all adjacent vertices with its number and weights in a row: " << std::endl;
			is >> en;
			for (size_t j = 0; j < en; ++j) {
				is >> e >> w;
				std::cout << j << ": " << e << " " << w << std::endl;
				for (size_t k = 0; k < data[i].size(); ++k) if (data[i][k].first == e) throw std::runtime_error("This edge has already exists");
				data[i].push_back(std::make_pair(e, w));
				for (size_t k = 0; k < data[e].size(); ++k) if (data[e][k].first == i) throw std::runtime_error("This edge has already exists");
				data[e].push_back(std::make_pair(i, w));
			}
			std::cout << std::endl;
		}
	}
	void generate(size_t edgesCount) {
		if (edgesCount < data.size() - 1) throw std::runtime_error("egdes count must be higher or equals than size of the graph - 1");
		std::random_device r;
		std::default_random_engine e(r());
		std::uniform_int_distribution<size_t> gen_int(0, data.size() - 1);
		size_t v1, v2, i;
		for (i = 0; i < data.size(); ++i) data[i].resize(0);
		std::uniform_real_distribution<double> gen_double(0.0, 1000.0);
		double w;
		bool FLAG = false;
		edgesCount -= data.size() - 1;
		myVector<size_t> pruferSequence;
		myVector<int> degree(data.size() - 1, 1);
		for (i = 0; i < data.size() - 2; ++i) {
			v1 = gen_int(e);
			pruferSequence.push_back(v1);
			++degree[v1];
		}
		for (i = 0; i < pruferSequence.size(); ++i) {
			for (v1 = 0; v1 < degree.size(); ++v1) {
				if (degree[v1] == 1) {
					v2 = pruferSequence[i];
					--degree[v1];
					--degree[v2];
					w = gen_double(e);
					data[v1].push_back(std::make_pair(v2, T(w)));
					data[v2].push_back(std::make_pair(v1, T(w)));
					break;
				}
			}
		}
		for (i = 0; i < degree.size(); ++i) {
			if (degree[i] == 1) {
				--degree[i];
				v1 = i;
				break;
			}
		}
		w = gen_double(e);
		data[v1].push_back(std::make_pair(data.size() - 1, T(w)));
		data[data.size() - 1].push_back(std::make_pair(v1, T(w)));
//		for (i = 0; i < degree.size(); ++i) {
//			std::cout << degree[i] << std::endl;
//			if (degree[i] != 0) throw std::runtime_error("ERROR!!!");
//		}
		
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
			data[v2].push_back(std::make_pair(v1, T(w)));
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
	myVector<size_t> pathes;
public:
	Dijkstra(const myGraph<T>& _G, size_t v) : G(_G), dist(_G.size(), std::numeric_limits<T>::max()), pathes(_G.size(), std::numeric_limits<size_t>::max()) {
		calculate(v);
	}
	T getDistance(size_t n) {
		if (n >= G.size()) throw std::logic_error("Invalid number of vertex to find distance to");
		return dist[n];
	}
	myVector<size_t> getPath(size_t n) {
		if (n >= G.size()) throw std::logic_error("Invalid number of vertex to find path to");
		myVector<size_t> v;
		size_t tmp;
		for (; n != std::numeric_limits<size_t>::max(); n = pathes[n]) v.push_back(n);
		for (size_t i = 0; i < v.size() / 2; ++i) {
			tmp = v[i];
			v[i] = v[v.size() - 1 - i];
			v[v.size() - 1 - i] = tmp;
		}
		return v;
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
					pathes[eit.first] = e.first;
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

