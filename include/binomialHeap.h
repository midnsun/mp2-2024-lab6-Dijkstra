#pragma once

#include "myMatrix.h"
template <typename T>
class binomialHeap {
    #ifdef TEST_MODE
	public:
	#endif
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
    bool isEmpty() const {
        return head == nullptr;
    }
    T searchMin() const {
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

    void mergeHeap(binomialHeap& heap) {
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
                    tmphead = lhead->sibling->sibling;
                    tmphead2 = rhead->sibling;
                    lhead->sibling = mergeBinomialTrees(lhead->sibling, rhead);
                    lhead->sibling->sibling = tmphead;
                    rhead = tmphead2;
                }
                else {
                    lhead = lhead->sibling;
                }
            }
            else if (lhead->degree == rhead->degree) {
                return;
            }
            else {
                return;
            }
        }
        heap.head = nullptr;

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
    }

    void add(const T& _data) {
        binomialHeap _heap;
        _heap.head = new Node{ 0, nullptr, nullptr, nullptr, _data };
        mergeHeap(_heap);
    }

    T extractMin() {
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

        binomialHeap _heap;
        _heap.head = minnode->child;
        tmphead = _heap.head;
        while (tmphead != nullptr) {
            tmphead->parent = nullptr;
            tmphead = tmphead->sibling;
        }

        mergeHeap(_heap);
        delete minnode;

        return retdata;
    }

    ~binomialHeap() {
        while (head != nullptr)
            extractMin();
    }
};