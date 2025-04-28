#pragma once
#include "myVector.h"

template <typename T>
class myMatrix {
	myVector<T> mem;
public:
	myMatrix(size_t sz = 1) : mem(sz * sz) {

	}
};