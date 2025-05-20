#include <iostream>

using namespace std;

struct NODE {
	int key;
	NODE* p_left;
	NODE* p_right;
};

NODE* createNode(int data) {
    NODE* newNode = new NODE;
    newNode->key = data;
    newNode->p_left = nullptr;
    newNode->p_right = nullptr;
    return newNode;
}

NODE* Search(NODE* pRoot, int x) {
    if (!pRoot || pRoot->key == x) return pRoot;
    if (x < pRoot->key) return Search(pRoot->p_left, x);
    return Search(pRoot->p_right, x);
}

void Insert(NODE*& pRoot, int x) {
    if (!pRoot) pRoot = createNode(x);
    else if (x < pRoot->key) Insert(pRoot->p_left, x);
    else if (x > pRoot->key) Insert(pRoot->p_right, x);
}

void Remove(NODE*& pRoot, int x) {
    if (!pRoot) return;
    if (x < pRoot->key) Remove(pRoot->p_left, x);
    else if (x > pRoot->key) Remove(pRoot->p_right, x);
    else {
        if (!pRoot->p_left || !pRoot->p_right) {
            NODE* temp = pRoot->p_left ? pRoot->p_left : pRoot->p_right;
            delete pRoot;
            pRoot = temp;
        }
        else {
            NODE* temp = pRoot;
            while (temp && temp->p_left) temp = temp->p_left;
            pRoot->key = temp->key;
            Remove(pRoot->p_right, temp->key);
        }
    }
}

NODE* createTree(int a[], int n) {
    NODE* pRoot = nullptr;
    int i = 0;
    while (i < n) {
        Insert(pRoot, a[i]);
        ++i;
    }
    return pRoot;
}

void removeTree(NODE*& pRoot) {
    if (!pRoot) return;
    removeTree(pRoot->p_left);
    removeTree(pRoot->p_right);
    delete pRoot;
    pRoot = nullptr;
}

int Height(NODE* pRoot) {
    if (!pRoot) return -1;
    int left = Height(pRoot->p_left);
    int right = Height(pRoot->p_right);
    return 1 + max(left, right);
}

int countLess(NODE* pRoot, int x) {
    if (!pRoot) return 0;
    if (pRoot->key < x) return 1 + countLess(pRoot->p_left, x) + countLess(pRoot->p_right, x);
    else countLess(pRoot->p_left, x);
}

int countGreater(NODE* pRoot, int x) {
    if (!pRoot) return 0;
    if (pRoot->key > x) return 1 + countGreater(pRoot->p_left, x) + countGreater(pRoot->p_right, x);
    else countGreater(pRoot->p_right, x);
}

bool isBSTUtil(NODE* pRoot, NODE* minNode, NODE* maxNode) {
    if (!pRoot) return true;
    if ((minNode && pRoot->key <= minNode->key) || (maxNode && pRoot->key >= maxNode->key)) return false;
    return isBSTUtil(pRoot->p_left, minNode, pRoot) && isBSTUtil(pRoot->p_right, pRoot, maxNode);
}

bool isBST(NODE* pRoot) {
    return isBSTUtil(pRoot, nullptr, nullptr);
}

bool isFullBST(NODE* pRoot) {
    if (!pRoot) return true;
    if ((!pRoot->p_left && !pRoot->p_right)) return true;
    if (pRoot->p_left && pRoot->p_right) return isFullBST(pRoot->p_left) && isFullBST(pRoot->p_right);
    return false;
}