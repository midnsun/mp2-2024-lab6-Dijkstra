#include <iostream>
#include <random>
#include <string>
#include "graphviz/gvc.h"
#include "graphviz/cgraph.h"
#include "myGraph.h"
#include "binomialHeap.h"
#include "binaryHeap.h"
#include <limits>
#include <chrono>
#include <fstream>

int main() {
//    freopen("../theGraph.txt", "r", stdin);

    std::cout << "Welcome to Dijkstra algorithm!\nPlease, enter a size for graph: " << std::endl;
    size_t sz;
    std::cin >> sz;
    myGraph<double> G(sz);
    std::chrono::steady_clock::time_point start, finish;
    uint64_t time;
    try {
        char c = 0;
        while (c != 'q') {
            std::cout << "Type g for generate graph, m for enter it manually, q to quit" << std::endl;
            std::cin >> c;
            switch (c) {
            case 'g':
                std::cout << "Enter count of edges: " << std::endl;
                size_t edgesCount;
                std::cin >> edgesCount;
                G.generate(edgesCount);
                break;
            case 'm':
                G.scan(std::cin);                                      
                break;
            case 'q':
                std::cout << "Quitting" << std::endl;
                return 0;
                break;
            default:
                std::cout << "Unknown input. Qutting" << std::endl;
                return 0;
                break;
            }

            std::cout << "Your graph is: " << std::endl;
            G.print();
            size_t n;
            std::cout << "Enter a number of a vertex for what you want to know all the distances for other vertices: " << std::endl;
            std::cin >> n;

            start = std::chrono::steady_clock::now();
            Dijkstra<double, binaryHeap> D1(G, n);
            finish = std::chrono::steady_clock::now();
            time = std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();
            std::cout << "Time for binary heap priority queue is: " << time << " microseconds" << std::endl;

            start = std::chrono::steady_clock::now();
            Dijkstra<double, binomialHeap> D2(G, n);
            finish = std::chrono::steady_clock::now();
            time = std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();
            std::cout << "Time for binomial heap priority queue is: " << time << " microseconds" << std::endl;

            while (n != std::numeric_limits<size_t>::max()) {
                std::cout << "Enter a number of a vertex in graph for which you want to know its distance. For quit enter any number bigger than a size of the graph: " << std::endl;
                std::cin >> n;
                if (n >= G.size()) break;
                std::cout << "For binary heap dijkstra: " << D1.getDistance(n) << "; For binomial heap dijkstra: " << D2.getDistance(n) << std::endl;
            }
        }
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    
    std::cout << "Ended" << std::endl;
	return 0;
}