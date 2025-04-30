#pragma once
#include "myVector.h"

template <typename T>
class myMatrix {
	myVector<T> mem;
	size_t sz;
public:
	myMatrix(size_t _sz = 0, const T& elem = T()) : sz(_sz), mem(_sz * _sz, elem) {

	}
	myMatrix(const myMatrix& mat) : sz(mat.sz), mem(mat.mem) {

	}
	myMatrix& operator=(const myMatrix& mat) {
		mem = mat.mem;
		sz = mat.sz;
	}
	size_t size() const noexcept {
		return sz;
	}
	T& operator()(size_t i, size_t j) noexcept {
		return mem[j * sz + i];
	}
	const T& operator()(size_t i, size_t j) const noexcept {
		return mem[j * sz + i];
	}
};