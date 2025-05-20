#include <iostream>
#include <vector>
#include <queue>

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

vector<int> NLR(NODE* pRoot) {
	vector<int> result;
	if (pRoot) {
		result.push_back(pRoot->key);
		vector<int> left = NLR(pRoot->p_left);
		vector<int> right = NLR(pRoot->p_right);
		result.insert(result.end(), left.begin(), left.end());
		result.insert(result.end(), right.begin(), right.end());
	}
	return result;
}

vector<int> LNR(NODE* pRoot) {
	vector<int> result;
	if (pRoot) {
		vector<int> left = LNR(pRoot->p_left);
		result.insert(result.end(), left.begin(), left.end());
		result.push_back(pRoot->key);
		vector<int> right = LNR(pRoot->p_right);
		result.insert(result.end(), right.begin(), right.end());
	}
	return result;
}

vector<int> LRN(NODE* pRoot) {
	vector<int> result;
	if (pRoot) {
		vector<int> left = LNR(pRoot->p_left);
		result.insert(result.end(), left.begin(), left.end());
		vector<int> right = LNR(pRoot->p_right);
		result.insert(result.end(), right.begin(), right.end());
		result.push_back(pRoot->key);
	}
	return result;
}

vector<vector<int>> LevelOrder(NODE* pRoot) {
	vector<vector<int>> result;
	if (!pRoot) return result;
	queue<NODE*> q;
	q.push(pRoot);
	while (!q.empty()) {
		vector<int> level;
		for (int i = 0; i < q.size(); ++i) {
			NODE* node = q.front();
			q.pop();
			level.push_back(node->key);
			if (node->p_left) q.push(node->p_left);
			if (node->p_right) q.push(node->p_right);
		}
		result.push_back(level);
	}
	return result;
}

int countNode(NODE* pRoot) {
	if (!pRoot) return 0;
	return 1 + countNode(pRoot->p_left) + countNode(pRoot->p_right);
}

int sumNode(NODE* pRoot) {
	if (!pRoot) return 0;
	return pRoot->key + sumNode(pRoot->p_left) + sumNode(pRoot->p_right);
}

int heightNodeEx(NODE* pRoot, int value, int currentHeight) {
	if (!pRoot) return -1;
	if (pRoot->key == value) return currentHeight;

	int left = heightNodeEx(pRoot->p_left, value, currentHeight + 1);
	if (left != -1) return left;

	return heightNodeEx(pRoot->p_right, value, currentHeight + 1);
}

int heightNode(NODE* pRoot, int value) {
	return heightNodeEx(pRoot, value, 0);
}

int Level(NODE* pRoot, NODE* p, int level = 0) {
	if (!pRoot) return -1;
	if (pRoot == p) return level;
	int left = Level(pRoot->p_left, p, level + 1);
	if (left != -1) return left;
	return Level(pRoot->p_right, p, level + 1);
}

int countLeaf(NODE* pRoot) {
	if (!pRoot) return 0;
	if (!pRoot->p_left && !pRoot->p_right) return 1;
	return countLeaf(pRoot->p_left) + countLeaf(pRoot->p_right);
}