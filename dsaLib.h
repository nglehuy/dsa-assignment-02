/*
 * =========================================================================================
 * Name        : dsaLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - Bach Khoa University
 * Description : library for Assignment 2 - Data structures and Algorithms - Fall 2017
 * =========================================================================================
 */
#ifndef A02_DSALIB_H
#define A02_DSALIB_H
#include <math.h>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class DSAException {
    int    _error;
    string _text;
   public:
    DSAException() : _error(0), _text("Success") {}
    DSAException(int err) : _error(err), _text("Unknown Error") {}
    DSAException(int err, const char *text) : _error(err), _text(text) {}
    int     getError() { return _error; }
    string &getErrorText() { return _text; }
};
template <class T>
struct L1Item {
    T          data;
    L1Item<T> *pNext;
    L1Item() : pNext(NULL) {}
    L1Item(T &a) : data(a), pNext(NULL) {}
};
template <class T>
class L1List {
    L1Item<T> *_pHead;  // The head pointer of linked list
    L1Item<T> *_pLast;  // The last pointer of linked list
    size_t     _size;   // number of elements in this list
   public:
    L1List() : _pHead(NULL), _pLast(NULL), _size(0) {}
    L1List(T &a) : _pHead(a), _pLast(a), _size(1) {}
    ~L1List() {
        destroy();
        _size = 0;
    }
    void   destroy();
    bool   isEmpty() { return _pHead == NULL; }
    size_t getSize() { return _size; }
    T &at(int i);
    T &operator[](int i);
    bool find(T &a, int &idx);
    int insert(int i, T &a);
    int insertTail(T &a);
    int remove(int i);
    int push_back(T &a);
    int insertHead(T &a);
    int         removeHead();
    int         removeLast();
    void        reverse();
    T &         getLast();
    L1Item<T> *&pointerHead() { return _pHead; }
    L1Item<T> *&pointerLast() { return _pLast; }
    bool traverse(bool (*op)(T, T, T, T), T n4) {
        L1Item<T> *p = _pHead;
        while (p->pNext != NULL) {
            if (op(p->data, p->pNext->data, _pLast->data, n4)) return true;
            p = p->pNext;
        }
        return false;
    }
    // void traverse (std::function<void(void *&, T &)> op, void *&pGData) {
    //     L1Item<T> *p = _pHead;
    //     while (p) {
    //         op (pGData, p->data);
    //         p = p->pNext;
    //     }
    // }
    void traverse(void (*op)(void *&, T &), void *&pGData) {
        L1Item<T> *p = _pHead;
        while (p) {
            op(pGData, p->data);
            p = p->pNext;
        }
    }
    bool traverse(bool (*op)(T &, T &), T &id) {
        L1Item<T> *p = _pHead;
        while (p != NULL) {
            if (op(p->data, id)) return true;
            p = p->pNext;
        }
        return false;
    }
    void traverseGreater(bool (*op)(T &, T &), T &n) {
        L1Item<T> *p = _pHead;
        while (p != NULL) {
            if (op(p->data, n)) { n = p->data; }
            p = p->pNext;
        }
    }
    void traverse(void (*op)(T &)) {
        L1Item<T> *p = _pHead;
        while (p) {
            op(p->data);
            p = p->pNext;
        }
    }
    void traverse(void (*op)(T &, T &), T &a) {
        L1Item<T> *p = _pHead;
        while (p) {
            op(p->data, a);
            p = p->pNext;
        }
    }
    void traverse(void (*op)(T &, void *), void *pParam) {
        L1Item<T> *p = _pHead;
        while (p) {
            op(p->data, pParam);
            p = p->pNext;
        }
    }
    void removeAll(T &a) {
        L1Item<T> *pre = _pHead;
        L1Item<T> *cur = _pHead->pNext;
        while (cur) {
            if (cur->data == a) {
                L1Item<T> *del = cur;
                pre->pNext     = cur->pNext;
                delete del;
                cur = pre->pNext;
                _size--;
                continue;
            }
            pre = cur;
            cur = cur->pNext;
        }
        _pLast = pre;
        if (_pHead->data == a) { removeHead(); }
    }
};
/// Insert item to the end of the list
/// Return 0 if success
template <class T>
int L1List<T>::push_back(T &a) {
    if (_pHead == NULL) { _pHead = new L1Item<T>(a); }
    else {
        L1Item<T> *p       = _pHead;
        while (p->pNext) p = p->pNext;
        p->pNext           = new L1Item<T>(a);
    }
    _size++;
    return 0;
}
/// Insert item to the front of the list
/// Return 0 if success
template <class T>
int L1List<T>::insertHead(T &a) {
    L1Item<T> *p = new L1Item<T>(a);
    p->pNext     = _pHead;
    _pHead       = p;
    _size++;
    return 0;
}
/// Remove the first item of the list
/// Return 0 if success
template <class T>
int L1List<T>::removeHead() {
    if (_pHead) {
        L1Item<T> *p = _pHead;
        _pHead       = p->pNext;
        delete p;
        _size--;
        if (_size == 0) _pLast = _pHead;
        return 0;
    }
    return -1;
}
/// Remove the last item of the list
/// Return 0 if success
template <class T>
int L1List<T>::removeLast() {
    if (_pHead) {
        if (_pHead->pNext) {
            L1Item<T> *prev = _pHead;
            L1Item<T> *pcur = prev->pNext;
            while (pcur->pNext) {
                prev = pcur;
                pcur = pcur->pNext;
            }
            delete pcur;
            prev->pNext = NULL;
            _pLast      = prev;
        }
        else {
            delete _pHead;
            _pHead = NULL;
        }
        _size--;
        return 0;
    }
    return -1;
}
///////////////======================Self-define======================////////////////
/// Reverse the list
template <class T>
void L1List<T>::reverse() {
    L1Item<T> *temp  = new L1Item<T>();
    bool       first = false;
    while (_pHead != NULL) {
        temp->data   = _pHead->data;
        L1Item<T> *t = new L1Item<T>();
        t->pNext     = temp;
        if (!first) {
            _pLast = temp;
            first  = true;
        }
        temp   = t;
        _pHead = _pHead->pNext;
    }
    _pHead = temp->pNext;
    delete temp;
}
/// Remove the ith item of the list
/// Return 0 if success, else return -1
template <class T>
int L1List<T>::remove(int i) {
    if (i == 0) {
        removeHead();
        return 0;
    }
    else if (i == _size - 1) {
        removeLast();
        return 0;
    }
    else if (i > 0 && i < _size - 1) {
        L1Item<T> *pre  = _pHead;
        L1Item<T> *curr = _pHead;
        while (i != 0) {
            pre  = curr;
            curr = curr->pNext;
            i--;
        }
        pre->pNext = curr->pNext;
        delete curr;
        return 0;
    }
    else {
        return -1;
    }
}
/// Insert an item into the list
/// Return 0 if success
template <class T>
int L1List<T>::insert(int i, T &a) {
    if (i == 0) {
        insertHead(a);
        return 0;
    }
    if (i > 0 && i < _size) {  // from 1 to size - 1
        L1Item<T> *pre  = _pHead;
        L1Item<T> *curr = _pHead;
        while (i != 0) {
            pre  = curr;
            curr = curr->pNext;
            i--;
        }
        pre->pNext        = new L1Item<T>(a);
        pre->pNext->pNext = curr;
        _size++;
        return 0;
    }
    else if (i == _size) {
        insertTail(a);
        return 0;
    }
    else {
        return -1;
    }
}
/// Insert an item into the tail of linked list
/// Return 0 if success
template <class T>
int L1List<T>::insertTail(T &a) {
    if (_pLast == NULL) {
        insertHead(a);
        _pLast = _pHead;
        return 0;
    }
    _pLast->pNext = new L1Item<T>(a);
    _pLast        = _pLast->pNext;
    _size++;
    return 0;
}
/// Find the item a
/// Get the index if found
template <class T>
bool L1List<T>::find(T &a, int &idx) {
    L1Item<T> *temp = _pHead;
    idx             = 0;
    while (temp != NULL) {
        if (a == temp->data) { return true; }
        temp = temp->pNext;
        idx++;
    }
    return false;
}
/// Operator[]
template <class T>
T &L1List<T>::operator[](int i) {
    if (i <= _size - 1 && i >= 0) {
        L1Item<T> *temp = _pHead;
        while (i != 0) {
            temp = temp->pNext;
            i--;
        }
        T &ans = temp->data;
        return ans;
    }
}
/// At
/// if out-of-range then throw the exception
template <class T>
T &L1List<T>::at(int i) {
    if (i <= _size - 1 && i >= 0) { operator[](i); }
    else
        throw out_of_range("Out-of-range");
}
/// Destroy the list
template <class T>
void L1List<T>::destroy() {
    if (_pHead == NULL) return;
    while (_pHead != NULL) {
        L1Item<T> *del = _pHead;
        _pHead         = _pHead->pNext;
        delete del;
    }
    _pLast = _pHead;
}
/// Get the last node
template <class T>
T &L1List<T>::getLast() {
    T &ans = _pLast->data;
    return ans;
}
/************************************************************************
 * This section is for AVL tree
 ************************************************************************/
template <class T>
struct AVLNode {
    T           _data;
    AVLNode<T> *_pLeft, *_pRight;
#ifdef AVL_USE_HEIGHT
    int _height;
    AVLNode(T &a) : _data(a), _pLeft(NULL), _pRight(NULL), _height(1) {}
#else
    int _bFactor;
    AVLNode(T &a) : _data(a), _pLeft(NULL), _pRight(NULL), _bFactor(0) {}
#endif
};
template <class T>
class AVLTree {
    AVLNode<T> *_pRoot;
   public:
    AVLTree() : _pRoot(NULL) {}
    AVLTree(T &a) { _pRoot = new AVLNode<T>(a); }
    ~AVLTree() { destroy(_pRoot); }
    T &  getRootData() { return _pRoot->_data; }
    bool find(T &key, T *&ret) { return find(_pRoot, key, ret); }
    bool searchWithCondition(std::function<bool(T &)> op, T &min, T &max) {
        return searchWithCondition(_pRoot, op, min, max);
    }
    void traverseWithCondition(std::function<void(T &)> op, T &min, T &max) {
        traverseWithCondition(_pRoot, op, min, max);
    }
    void traverseWithConditionRNL(std::function<void(T &)> op, T &min, T &max) {
        traverseWithConditionRNL(_pRoot, op, min, max);
    }
    void traverseWithConditionNLR(std::function<void(T &)> op, T &min, T &max) {
        traverseWithConditionNLR(_pRoot, op, min, max);
    }
    bool insert(T &key) { return insert(_pRoot, key); }
    bool remove(T &key) { return remove(_pRoot, key); }
    void           traverseNLR(void (*op)(T &)) { traverseNLR(_pRoot, op); }
    void traverseNLR(void (*op)(void *&, T &), void *&pGD) { traverseNLR(_pRoot, op, pGD); }
    void traverseLNR(void (*op)(T &)) { traverseLNR(_pRoot, op); }
    bool traverseLNR(std::function<bool(double, T &)> op, double _lo) {
        if (_pRoot == NULL)
            return false;
        else
            return traverseLNR(_pRoot, op, _lo);
    }
    bool traverseLNR(std::function<bool(double, double, double, T &)> op, double _la, double _lo,
                     double _r) {
        if (_pRoot == NULL)
            return false;
        else
            return traverseLNR(_pRoot, op, _la, _lo, _r);
    }
    void traverseLNR(std::function<void(T &, T &)> op, T &startIn) {
        traverseLNR(_pRoot, op, startIn);
    }
    void traverseLNR(std::function<void(T &)> op) { traverseLNR(_pRoot, op); }
    void traverseLRN(void (*op)(T &)) { traverseLRN(_pRoot, op); }
    void printNLR() {
        _printNLR(_pRoot);
        cout << endl;
    }
    void destroy() { destroy(_pRoot); }
   protected:
    bool searchWithCondition(AVLNode<T> *&pR, std::function<bool(T &)> op, T &min, T &max) {
        if (pR == NULL)
            return false;
        else if (pR->_data >= min && pR->_data <= max) {  // meat the range
            if (op(pR->_data))
                return true;
            else if (searchWithCondition(pR->_pLeft, op, min, max))
                return true;
            else if (searchWithCondition(pR->_pRight, op, min, max))
                return true;
            else
                return false;
        }
        else if (pR->_data < min) {  // smaller than the min, search the right (the right always
                                     // greater then the root)
            return searchWithCondition(pR->_pRight, op, min, max);
        }
        else  // greater than the max, search the left (the left always smaller then the root)
            return searchWithCondition(pR->_pLeft, op, min, max);
    }
    void traverseWithCondition(AVLNode<T> *&pR, std::function<void(T &)> op, T &min, T &max) {
        if (pR == NULL)
            return;
        else if (pR->_data >= min && pR->_data <= max) {
            traverseWithCondition(pR->_pLeft, op, min, max);
            op(pR->_data);
            traverseWithCondition(pR->_pRight, op, min, max);
        }
        else if (pR->_data < min)
            traverseWithCondition(pR->_pRight, op, min, max);
        else
            traverseWithCondition(pR->_pLeft, op, min, max);
    }
    void traverseWithConditionRNL(AVLNode<T> *&pR, std::function<void(T &)> op, T &min, T &max) {
        if (pR == NULL)
            return;
        else if (pR->_data >= min && pR->_data <= max) {
            traverseWithConditionRNL(pR->_pRight, op, min, max);
            op(pR->_data);
            traverseWithConditionRNL(pR->_pLeft, op, min, max);
        }
        else if (pR->_data < min)
            traverseWithConditionRNL(pR->_pRight, op, min, max);
        else
            traverseWithConditionRNL(pR->_pLeft, op, min, max);
    }
    void traverseWithConditionNLR(AVLNode<T> *&pR, std::function<void(T &)> op, T &min, T &max) {
        if (pR == NULL)
            return;
        else if (pR->_data >= min && pR->_data <= max) {
            op(pR->_data);
            traverseWithConditionNLR(pR->_pLeft, op, min, max);
            traverseWithConditionNLR(pR->_pRight, op, min, max);
        }
        else if (pR->_data < min)
            traverseWithConditionNLR(pR->_pRight, op, min, max);
        else
            traverseWithConditionNLR(pR->_pLeft, op, min, max);
    }
    void _printNLR(AVLNode<T> *&_pR) {
        if (_pR == NULL) return;
        cout << _pR->_data << " ";
        _printNLR(_pR->_pLeft);
        _printNLR(_pR->_pRight);
    }
    void destroy(AVLNode<T> *&pR) {
        if (pR == NULL) return;
        destroy(pR->_pLeft);
        destroy(pR->_pRight);
        pR = NULL;
    }
    bool find(AVLNode<T> *pR, T &key, T *&ret) {
        if (pR == NULL)
            return false;
        else if (pR->_data == key) {
            ret = &(pR->_data);
            return true;
        }
        else if (pR->_data > key) {
            return find(pR->_pLeft, key, ret);
        }
        else
            return find(pR->_pRight, key, ret);
    }
    bool insert(AVLNode<T> *&pR, T &a) {
#ifdef AVL_USE_HEIGHT
        if (pR == NULL) {
            pR = new AVLNode<T>(a);
            return true;
        }
        else if (pR->_data > a)
            insert(pR->_pLeft, a);
        else
            insert(pR->_pRight, a);
        reBalance(pR);
        return true;
#else
        if (pR == NULL) {
            pR = new AVLNode<T>(a);
            return true;
        }
        else if (pR->_data > a) {
            if (insert(pR->_pLeft, a)) {  // left higher after insertion
                pR->_bFactor++;           // update bFactor of pR
                if (pR->_bFactor == 1) return true;
                if (pR->_bFactor == 0) return false;
                return balanceLeft(pR);  // true if not destroy the balance but increase the height
            }
            return false;
        }
        else {
            if (insert(pR->_pRight, a)) {  // right higher after insertion
                pR->_bFactor--;
                if (pR->_bFactor == -1) return true;
                if (pR->_bFactor == 0) return false;
                return balanceRight(pR);
            }
            return false;
        }
#endif
    }
    bool remove(AVLNode<T> *&pR, T &a) {
#ifdef AVL_USE_HEIGHT
        if (pR == NULL) return false;
        if (a < pR->_data) { remove(pR->_pLeft, a); }
        else if (a > pR->_data) {
            remove(pR->_pRight, a);
        }
        else {
            if (pR->_pRight == NULL && pR->_pLeft == NULL) {
                AVLNode<T> *p = pR;
                pR            = NULL;
                delete p;
                return true;
            }
            else if (pR->_pRight == NULL) {
                AVLNode<T> *t = pR;
                pR            = pR->_pLeft;
                delete t;
                return true;
            }
            else {
                AVLNode<T> *t       = pR->_pRight;
                while (t->_pLeft) t = t->_pLeft;
                pR->_data           = t->_data;
                remove(pR->_pRight, t->_data);
            }
        }
        reBalance(pR);
        return true;
#else
        if (pR == NULL) return false;
        if (a < pR->_data) {
            if (remove(pR->_pLeft, a))  // left shorter , right higher
            {
                pR->_bFactor--;
                if (pR->_bFactor == -1) return false;
                if (pR->_bFactor == 0) return true;
                return !balanceRight(pR);
            }
            return false;
        }
        else if (a > pR->_data) {
            if (remove(pR->_pRight, a))  // right shorter , left higher
            {
                pR->_bFactor++;
                if (pR->_bFactor == 1) return false;
                if (pR->_bFactor == 0) return true;
                return !balanceLeft(pR);
            }
            return false;
        }
        else {
            if (pR->_pRight == NULL && pR->_pLeft == NULL) {
                AVLNode<T> *p = pR;
                pR            = NULL;
                delete p;
                return true;
            }
            else if (pR->_pRight == NULL) {
                AVLNode<T> *t = pR;
                pR            = pR->_pLeft;
                delete t;
                return true;
            }
            else {
                AVLNode<T> *t       = pR->_pRight;
                while (t->_pLeft) t = t->_pLeft;
                pR->_data           = t->_data;
                if (remove(pR->_pRight, t->_data)) {
                    pR->_bFactor++;
                    if (pR->_bFactor == 1) return false;
                    if (pR->_bFactor == 0) return true;
                    return !balanceLeft(pR);
                }
                return false;
            }
        }
#endif
    }
    void traverseNLR(AVLNode<T> *pR, void (*op)(T &)) {
        if (pR == NULL) return;
        op(pR->_data);
        traverseNLR(pR->_pLeft, op);
        traverseNLR(pR->_pRight, op);
    }
    void traverseNLR(AVLNode<T> *pR, void (*op)(void *&, T &), void *&pGD) {
        if (pR == NULL) return;
        op(pGD, pR->_data);
        traverseNLR(pR->_pLeft, op);
        traverseNLR(pR->_pRight, op);
    }
    void traverseLNR(AVLNode<T> *pR, void (*op)(T &)) {
        if (pR == NULL) return;
        traverseLNR(pR->_pLeft, op);
        op(pR->_data);
        traverseLNR(pR->_pRight, op);
    }
    void traverseLNR(AVLNode<T> *pR, std::function<void(T &, T &)> op, T &startIn) {
        if (pR == NULL) return;
        traverseLNR(pR->_pLeft, op);
        op(pR->_data, startIn);
        traverseLNR(pR->_pRight, op);
    }
    void traverseLNR(AVLNode<T> *pR, std::function<void(T &)> op) {
        if (pR == NULL) return;
        traverseLNR(pR->_pLeft, op);
        op(pR->_data);
        traverseLNR(pR->_pRight, op);
    }
    bool traverseLNR(AVLNode<T> *pR, std::function<bool(double, T &)> op, double _lo) {
        if (pR == NULL) return true;
        // traverse left
        if (!traverseLNR(pR->_pLeft, op, _lo)) return false;
        // visit the root
        else if (!op(_lo, pR->_data))
            return false;
        // traverse right
        else if (!traverseLNR(pR->_pRight, op, _lo))
            return false;
        else
            return true;
    }
    bool traverseLNR(AVLNode<T> *pR, std::function<bool(double, double, double, T &)> op,
                     double _la, double _lo, double _r) {
        if (pR == NULL) return true;
        // traverse left
        if (traverseLNR(pR->_pLeft, op, _la, _lo, _r)) return true;
        // visit the root
        else if (op(_la, _lo, _r, pR->_data))
            return true;
        // traverse right
        else if (traverseLNR(pR->_pRight, op, _la, _lo, _r))
            return true;
        else
            return false;
    }
    void traverseLRN(AVLNode<T> *pR, void (*op)(T &)) {
        if (pR == NULL) return;
        traverseLRN(pR->_pLeft, op);
        traverseLRN(pR->_pRight, op);
        op(pR->_data);
    }
#ifdef AVL_USE_HEIGHT
    int max(int a, int b) { return (a > b) ? a : b; }
    int GetHeight(AVLNode<T> *&pR) {
        if (pR == NULL) return 0;
        return pR->_height;
    }
    void updateHeight(AVLNode<T> *&pR) {
        if (pR == NULL) return;
        pR->_height = max(GetHeight(pR->_pLeft), GetHeight(pR->_pRight)) + 1;
    }
    int GetBalanceFactor(AVLNode<T> *&pR) {
        if (pR == NULL) return 0;
        return GetHeight(pR->_pLeft) - GetHeight(pR->_pRight);
    }
    void reBalance(AVLNode<T> *&pR) {
        updateHeight(pR);
        int b  = GetBalanceFactor(pR);
        int bL = GetBalanceFactor(pR->_pLeft);
        int bR = GetBalanceFactor(pR->_pRight);
        if (b > 1 && bL >= 0) { rotRight(pR); }
        else if (b > 1 && bL < 0) {
            rotLR(pR);
        }
        else if (b < -1 && bR <= 0) {
            rotLeft(pR);
        }
        else if (b < -1 && bR > 0) {
            rotRL(pR);
        }
    }
#endif
    void rotLeft(AVLNode<T> *&pR) {
        AVLNode<T> *x = pR->_pRight;
        AVLNode<T> *y = x->_pLeft;
        x->_pLeft     = pR;
        pR->_pRight   = y;
        pR            = x;
#ifdef AVL_USE_HEIGHT
        // update height
        updateHeight(pR->_pLeft);
        updateHeight(pR);
#else
        // recalculate bFactor
        pR->_bFactor++;
        pR->_pLeft->_bFactor += (pR->_bFactor + 2);
#endif
    }
    void rotRight(AVLNode<T> *&pR) {
        AVLNode<T> *x = pR->_pLeft;
        AVLNode<T> *y = x->_pRight;
        x->_pRight    = pR;
        pR->_pLeft    = y;
        pR            = x;
#ifdef AVL_USE_HEIGHT
        // update height
        updateHeight(pR->_pRight);
        updateHeight(pR);
#else
        // recalculate bFactor
        pR->_bFactor--;
        pR->_pRight->_bFactor -= (pR->_bFactor + 2);
#endif
    }
    void rotLR(AVLNode<T> *&pR) {
        rotLeft(pR->_pLeft);
        rotRight(pR);
    }
    void rotRL(AVLNode<T> *&pR) {
        rotRight(pR->_pRight);
        rotLeft(pR);
    }
    bool balanceLeft(AVLNode<T> *&pR) {
        // > 1 means the height of the left is greater then the right 2 units
        // return false if it's rebalanced (means that the height doesnt increase)
        if (pR->_bFactor > 1 && pR->_pLeft->_bFactor >= 0) {
            /*           9                        7
             *         /   \                   /     \
             *        7     10               5         9
             *      /   \        ==>       /   \      /  \
             *     5     8                4     6    8    10
             *   /   \
             *  4     6
             */
            rotRight(pR);
        }
        else if (pR->_bFactor > 1 && pR->_pLeft->_bFactor < 0) {
            /*              11                      11                      9
             *            /   \                    /  \                   /    \
             *           7     12                 9    12                7     11
             *         /   \            ==>      /  \           ==>     / \   /   \
             *        5     9                   7   10                 5   8 10   12
             *             /  \                / \
             *            8    10             5   8
             */
            rotLR(pR);
        }
        return !(pR->_bFactor == 0);  // balance for insertion, false to finish
    }
    bool balanceRight(AVLNode<T> *&pR) {
        //< -1 means the height of the right is greater then the left 2 units
        // return false if the height doesnt increase
        if (pR->_bFactor < -1 && pR->_pRight->_bFactor <= 0) {
            /*             5                           7
             *           /   \                      /     \
             *          4     7                   5        9
             *               /  \        ==>     / \      /  \
             *              6    9              4   6    8   10
             *                  /  \
             *                 8    10
             */
            rotLeft(pR);
        }
        else if (pR->_bFactor < -1 && pR->_pRight->_bFactor > 0) {
            /*              7                           7                           9
             *             / \                         /  \                       /    \
             *            5   11                      5    9                    7       11
             *               /  \       ==>               /  \          ==>    / \     /   \
             *              9   12                       8    11              5   8   10   12
             *             / \                               /  \
             *            8   10                            10  12
             */
            rotRL(pR);
        }
        return !(pR->_bFactor == 0);
    }
};
#endif  // A02_DSALIB_H
