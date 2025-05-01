#pragma once

#include "myVector.h"
template<typename T>
class binaryHeap {
    #ifdef TEST_MODE
	public:
	#endif
    myVector<T> data;
    int size;
public:
    void slideDown(int ind) {
        T tmp;
        for (int i = ind; i < size;) {
            if (2 * i + 2 < size) {
                if ((data[i] < data[2 * i + 1]) && (data[i] < data[2 * i + 2])) return;
                if (data[2 * i + 1] < data[2 * i + 2]) {
                    tmp = data[2 * i + 1];
                    data[2 * i + 1] = data[i];
                    data[i] = tmp;
//                    std::swap(data[2 * i + 1], data[i]);
                    i = 2 * i + 1;
                }
                else if (data[2 * i + 1] >= data[2 * i + 2]) {
                    tmp = data[2 * i + 2];
                    data[2 * i + 2] = data[i];
                    data[i] = tmp;
//                    std::swap(data[2 * i + 2], data[i]);
                    i = 2 * i + 2;
                }
            }
            else if (2 * i + 1 < size) {
                if (data[i] < data[2 * i + 1]) return;
                tmp = data[2 * i + 1];
                data[2 * i + 1] = data[i];
                data[i] = tmp;
//                std::swap(data[2 * i + 1], data[i]);
                i = 2 * i + 1;
            }
            else return;
        }
    }
    void slideUp(int ind) {
        T tmp;
        for (int i = ind; i >= 0;) {
            if (((i - 1) / 2) >= 0) {
                if (data[(i - 1) / 2] > data[i]) {
                    tmp = data[(i - 1) / 2];
                    data[(i - 1) / 2] = data[i];
                    data[i] = tmp;
//                    std::swap(data[(i - 1) / 2], data[i]);
                }
                else return;
            }
            i = (i - 1) / 2;
        }
    }
    binaryHeap() :size(0) {}
    T extractMin() {
        if (size == 0) return T();
        T res = data[0];
        data[0] = data[--size];
        data[size] = res;
//        std::swap(data[0], data[--size]);
        slideDown(0);
        return res;
    }
    T searchMin() const {
        return data[0];
    }
    bool isEmpty() const {
        return size == 0;
    }
    void add(const T& val) {
        if (size < data.size()) data[size] = val;
        else data.push_back(val);
        ++size;
        slideUp(size - 1);
    }
    /*
    void push_back(const T& val) {
        if (size < data.size()) data[size] = val;
        else data.push_back(val);
        ++size;
    }
    void heapify() {
        for (int i = size / 2; i >= 0; --i) {
            slideDown(i);
        }
    }
    void print() {
        int i;
        for (i = 0; i < size; ++i) std::cout << data[i] << " ";
        std::cout << std::endl;
        return; //
        for (; i < data.size(); ++i) std::cout << data[i] << " ";
        std::cout << std::endl;
    }
    void sort() {
        heapify();
        int tmpsize = size;
        while (size > 0) extractMin();
        size = tmpsize;
    }
    bool isSorted() {
        for (int i = 0; i < size - 1; ++i) {
            if (data[i] < data[i + 1]) return false;
        }
        return true;
    }
    */
};