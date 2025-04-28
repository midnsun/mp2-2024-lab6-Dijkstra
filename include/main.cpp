#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <string>
#include <sstream>

using namespace std;

template<typename T>
class myHeap {
    std::vector<T> data;
    int size;
    void slideDown(int ind) {
        int tmpi;
        for (int i = ind; i < size;) {
            //            tmpi = i;
            if (2 * i + 2 < size) {
                if ((data[i] < data[2 * i + 1]) && (data[i] < data[2 * i + 2])) return;
                if (data[2 * i + 1] < data[2 * i + 2]) {
                    std::swap(data[2 * i + 1], data[i]);
                    i = 2 * i + 1;
                }
                else if (data[2 * i + 1] >= data[2 * i + 2]) {
                    std::swap(data[2 * i + 2], data[i]);
                    i = 2 * i + 2;
                }
            }
            else if (2 * i + 1 < size) {
                if (data[i] < data[2 * i + 1]) return;
                std::swap(data[2 * i + 1], data[i]);
                i = 2 * i + 1;
            }
            else return;
        }
    }
    void slideUp(int ind) {
        for (int i = ind; i >= 0;) {
            if (((i - 1) / 2) >= 0) {
                if (data[(i - 1) / 2] > data[i]) {
                    std::swap(data[(i - 1) / 2], data[i]);
                }
                else return;
            }
            i = (i - 1) / 2;
        }
    }
public:
    myHeap() :size(0) {}
    int extractMin() {
        if (size == 0) return 0;
        int res = data[0];
        std::swap(data[0], data[--size]);
        slideDown(0);
        return res;
    }
    void add(const T& val) {
        if (size < data.size()) data[size] = val;
        else data.push_back(val);
        ++size;
        slideUp(size - 1);
    }
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
};

template <typename T>
void printvec(const std::vector<T>& vec) {
    for (size_t i = 0; i < vec.size(); ++i) std::cout << vec[i] << " ";
    std::cout << std::endl;
}

template<typename TYPE>
void _swap_p(TYPE** a, TYPE** b) {
    TYPE* tmp = *a;
    *a = *b;
    *b = tmp;
}

int _min(int v1, int v2) { return  v1 < v2 ? v1 : v2; }
int _max(int v1, int v2) { return  v1 > v2 ? v1 : v2; }

template<typename TYPE>
void _copy(TYPE* src, TYPE* dst, size_t first, size_t last) {
    size_t i;
    for (i = first; i < last; i++) dst[i] = src[i];
}

template<typename TYPE>
void _merge(TYPE* a, TYPE* b, TYPE* data, size_t an, size_t bn) {
    size_t ai = 0;
    size_t bi = 0;
    size_t di = 0;

    while (ai < an && bi < bn) {
        if (a[ai] < b[bi]) data[di++] = a[ai++];
        else data[di++] = b[bi++];
    }
    for (; ai < an; ai++) data[di++] = a[ai];
    for (; bi < bn; bi++) data[di++] = b[bi];
}

template<typename TYPE>
void _mergesort(TYPE* m, int size) {
    size_t counter = 0;
    int step, i;
    TYPE* tmpdata = (TYPE*)malloc(size * sizeof(TYPE));
    for (step = 1; step < size; step *= 2) {
        for (i = 0; i < size; i += 2 * step) {
            _merge(m + i, m + i + step, tmpdata + i, _max(0, _min(step, size - i)), _max(0, _min(step, size - step - i)));
        }
        _swap_p(&m, &tmpdata);
        counter++;
    }
    if ((counter % 2) != 0) {
        _swap_p(&m, &tmpdata);
        _copy(tmpdata, m, 0, size);
    }
    free(tmpdata);
}

template <typename T>
class binomialHeap {
    struct Node {
        int degree;
        Node* child;
        Node* sibling;
        Node* parent;
        T data;
        Node(int _degree, Node* _child, Node* _sibling, Node* _parent, const T& _data) : degree(_degree), child(_child), sibling(_sibling), parent(_parent), data(_data) {}
    };

    Node* head;
public:
    binomialHeap() : head(nullptr) {}

    const T& searchMin() const {
        Node* tmp = head;
        T minkey;
        if (head == nullptr) return T();
        minkey = head->data;
        while (tmp != nullptr) {
            minkey = (tmp->data < minkey) ? tmp->data : minkey;
            tmp = tmp->sibling;
        }
        return minkey;
    }

    bool isCorrect() {
        if (head == nullptr || head->sibling == nullptr) return true;
        Node* tmp = head;
        while (tmp->sibling != nullptr) {
            if (tmp->degree <= tmp->sibling->degree) return false;
            tmp = tmp->sibling;
        }
        return true;
    }

    Node* mergeBinomialTrees(Node* left, Node* right) {
        Node* res = nullptr;
        if (right->data < left->data) {
            left->sibling = right->child;
            right->child = left;
            left->parent = right;
            res = right;
        }
        else {
            right->sibling = left->child;
            left->child = right;
            right->parent = left;
            res = left;
        }
        res->degree++;
        return res;
    }

    void mergeHeapOld(binomialHeap& heap) {
        if (head == nullptr) {
            head = heap.head;
            heap.head = nullptr;
            return;
        }
        Node* lroot, * rroot, *tmproot1, *tmproot2;
        lroot = head;
        rroot = heap.head;
        while (rroot != nullptr) {
            if (rroot->degree > lroot->degree) {
                if (lroot->sibling == nullptr || lroot->sibling->degree > rroot->degree) {
                    tmproot1 = lroot->sibling;
                    lroot->sibling = rroot;
                    tmproot2 = rroot->sibling;
                    rroot->sibling = tmproot1->sibling;
                    rroot = tmproot2;
                }
                lroot = lroot->sibling;
                continue;
            }
            else if (rroot->degree == lroot->degree) {
                lroot = mergeBinomialTrees(rroot, lroot);
//                lroot = lroot->sibling;
                rroot = rroot->sibling;
            }
            else {
                std::cout << "Merge Heap error" << std::endl;
                return;
            }
        }
        heap.head = nullptr;
        bool flag = true;
        Node* tmpdel, *tmproot;
        while (flag) {
            flag = false;
            tmproot = head;
            while (tmproot != nullptr && tmproot->sibling != nullptr) {
                if (tmproot->degree == tmproot->sibling->degree) {
                    tmpdel = tmproot->sibling->sibling;
                    tmproot->sibling = mergeBinomialTrees(tmproot, tmproot->sibling);
                    tmproot->sibling = tmpdel;
                    flag = true;
                }
                else if (tmproot->degree < tmproot->sibling->degree) {
                    std::cout << "Error in heapMerge 2" << std::endl; //
                    return;
                }
                tmproot = tmproot->sibling;
            }
        }
        if (!isCorrect()) std::cout << "Bad merge" << std::endl; //
    }

    void mergeHeap(binomialHeap& heap) {
        bool coutflag = false;
        if (heap.head == nullptr) return;
        if (head == nullptr) {
            head = heap.head;
            heap.head = nullptr;
            return;
        }
        Node* lhead, * rhead, * tmphead, * tmphead2;
        if (heap.head->degree > head->degree) {
            tmphead = heap.head;
            heap.head = head;
            head = tmphead;
        }

        if (coutflag) std::cout << std::endl << "Merge started\n";
        if (coutflag) print();
        if (coutflag) heap.print();

        rhead = heap.head;
        if (head->degree == heap.head->degree) {
            rhead = rhead->sibling;
            tmphead = head->sibling;
            head = mergeBinomialTrees(head, heap.head);
            head->sibling = tmphead;
            heap.head = rhead;
        }
        lhead = head;
        while (rhead != nullptr) {
            if (lhead->degree > rhead->degree) {
                if (lhead->sibling == nullptr || lhead->sibling->degree < rhead->degree) {
                    tmphead = rhead->sibling;
                    rhead->sibling = lhead->sibling;
                    lhead->sibling = rhead;
                    rhead = tmphead;
                    lhead = lhead->sibling;
                }
                else if (lhead->sibling->degree == rhead->degree) {

                    if (coutflag) std::cout << "here. Before merging: " << std::endl;
                    if (coutflag) print();
                    if (coutflag) heap.print();

                    tmphead = lhead->sibling->sibling;
                    tmphead2 = rhead->sibling;
                    lhead->sibling = mergeBinomialTrees(lhead->sibling, rhead);
                    lhead->sibling->sibling = tmphead;
                    rhead = tmphead2;

                    if (coutflag) std::cout << "here. After merging: " << std::endl;
                    if (coutflag) print();
                    if (coutflag) heap.print();
                }
                else {
                    lhead = lhead->sibling;
                }
            }
            else if (lhead->degree == rhead->degree) {
                std::cout << "ERROR!!! mergeHeap 1" << std::endl;
                return;
                lhead = mergeBinomialTrees(lhead, rhead);
                rhead = rhead->sibling;
            }
            else {
                std::cout << "ERROR!!! megreHeap 2" << std::endl;
                return;
            }
        }
        heap.head = nullptr; // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        if (coutflag) std::cout << "Print after half of merging: " << std::endl;
        if (coutflag) print();

        bool flag = true;
        while (flag) {
            flag = false;
            if (head->sibling == nullptr) break;
            if (head->degree == head->sibling->degree) {
                tmphead = head->sibling->sibling;
                head = mergeBinomialTrees(head, head->sibling);
                head->sibling = tmphead;
                flag = true;
            }
            lhead = head;
            while (lhead->sibling != nullptr && lhead->sibling->sibling != nullptr) {
                if (lhead->sibling->degree == lhead->sibling->sibling->degree) {
                    tmphead = lhead->sibling->sibling->sibling;
                    lhead->sibling = mergeBinomialTrees(lhead->sibling, lhead->sibling->sibling);
                    lhead->sibling->sibling = tmphead;
                    flag = true;
                }
                else 
                    lhead = lhead->sibling;
            }
        }

        if (!isCorrect()) std::cout << "Bad merge" << std::endl; //
        if (coutflag)std::cout << "merge ended\n";
        if (coutflag)print();
    }

    void insert(const T& _data) {
        binomialHeap _heap;
        _heap.head = new Node{ 0, nullptr, nullptr, nullptr, _data };
        mergeHeap(_heap);
    }

    T extractMin() { // Dont work
        bool coutflag = false;
        if (coutflag) std::cout << "extract min started. " << std::endl;
        if (coutflag) print();
        if (head == nullptr) return T();
        T retdata;
        Node* minnode = head;
        Node* tmphead = head;
        while (tmphead != nullptr) {
            if (tmphead->data < minnode->data) minnode = tmphead;
            tmphead = tmphead->sibling;
        }
        retdata = minnode->data;

        if (minnode == head) head = head->sibling;
        else {
            tmphead = head;
            while (tmphead->sibling != nullptr) {
                if (tmphead->sibling == minnode) {
                    tmphead->sibling = tmphead->sibling->sibling;
                    break;
                }
                tmphead = tmphead->sibling;
            }
        }

        if (coutflag) std::cout << "Minimal node extracted. " << std::endl;
        if (coutflag) print();

        binomialHeap _heap;
        _heap.head = minnode->child;
        tmphead = _heap.head;
        while (tmphead != nullptr) {
            tmphead->parent = nullptr;
            tmphead = tmphead->sibling;
        }

        if (coutflag) std::cout << "tmp heap created. Given heap: " << std::endl;
        if (coutflag) print();
        if (coutflag) std::cout << "tmp heap created. Tmp heap: " << std::endl;
        if (coutflag) _heap.print();

        mergeHeap(_heap);
        delete minnode;

        if (coutflag) std::cout << "extract min ended. " << std::endl;
        if (coutflag) print();

        return retdata;
    }

    void print() {
        std::cout << "printing tree:" << std::endl;
        Node* tmp = head;
        while (tmp != nullptr) {
            std::cout << "   deg:" << tmp->degree << " ";
            printBinomialTree(tmp);
            tmp = tmp->sibling;
        }
        std::cout << std::endl;
    }

    void printBinomialTree(Node* root) {
        if (root == nullptr) return;
        std::cout << root->data << ":" << root->degree << " ";
        Node* tmp = root->child;
        while (tmp != nullptr) {
            printBinomialTree(tmp);
            tmp = tmp->sibling;
        }
    }

    ~binomialHeap() {
        while (head != nullptr)
            extractMin();
    }
};

template <typename T>
bool isVectorSorted(std::vector<T>& v) {
    if (v.size() <= 1) return true;
    for (size_t i = 0; i < v.size() - 1; ++i) {
        if (v[i] > v[i + 1]) return false;
    }
    return true;
}

void testBinomialHeap() {
    int s = 10000000;
    int elem;
    std::random_device r;
    std::default_random_engine e(r());
    std::uniform_int_distribution<int> gen(-1000, 1000);
    std::vector<int> v;

    binomialHeap<int> bh;

    for (size_t i = 0; i < s; ++i) {
        elem = gen(e);
        //        std::cout << "new element: " << elem << std::endl;
        bh.insert(elem);
        //        bh.print();
        //        std::cout << std::endl;
    }

    std::cout << "insertion ended" << std::endl;
//    bh.print();

    std::cout << std::endl << "Extracting min: " << std::endl << std::endl;

    for (size_t i = 0; i < s; ++i) {
        elem = bh.extractMin();
        v.push_back(elem);
//        std::cout << "Min:" << elem << std::endl << std::endl;
    }
    std::cout << isVectorSorted(v) << std::endl;
}

void testBinaryHeap() {
    int s = 10000000;
    myHeap<int> h;
    int elem;
    std::random_device r;
    std::default_random_engine e(r());
    std::uniform_int_distribution<int> gen(-1000, 1000);
    std::vector<int> v;


    for (size_t i = 0; i < s; ++i) {
        elem = gen(e);
        h.push_back(elem);
        v.push_back(elem);
    }

    std::chrono::steady_clock::time_point start, finish;
    uint64_t time;

    start = std::chrono::steady_clock::now();
    h.sort();
    finish = std::chrono::steady_clock::now();
    time = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
    std::cout << "time on heapsort: " << time << std::endl;

    start = std::chrono::steady_clock::now();
    _mergesort<int>(v.data(), v.size());
    finish = std::chrono::steady_clock::now();
    time = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
    std::cout << "time on mergesort: " << time << std::endl;
}

int main() {

    testBinaryHeap();
    testBinomialHeap();

    return 0;
    std::string s("123.32ee1");

        char junk;
        double d;
        stringstream ss(s);
        if (ss >> d && !(ss >> junk)) {
            std::cout << d << std::endl;
        }
        else {
            std::cout << "bad input" << std::endl;
        }

    return 0;
}