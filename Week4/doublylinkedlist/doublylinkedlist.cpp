#include <iostream>
#include <cassert>
using namespace std;

struct NODE {
    int key;
    NODE* p_next;
    NODE* p_prev;
};

struct List {
    NODE* p_head;
    NODE* p_tail;
    List(NODE* head = nullptr, NODE* tail = nullptr) : p_head(head), p_tail(tail) {}
};

// --- Function prototypes ---
NODE* createNode(int data);
List* createList(NODE* p_node);
bool addHead(List*& L, int data);
bool addTail(List*& L, int data);
bool removeHead(List*& L);
void removeTail(List*& L);
void removeAll(List*& L);
void removeBefore(List*& L, int val);
void removeAfter(List*& L, int val);
bool addPos(List*& L, int data, int pos);
void removePos(List*& L, int data, int pos);
bool addBefore(List*& L, int data, int val);
bool addAfter(List*& L, int data, int val);
void printList(List* L);
int countElements(List* L);
List* reverseList(List* L);
void removeDuplicate(List*& L);
bool removeElement(List*& L, int key);

// function to create a list from an array
List* createListFromArray(int arr[], int n)
{
    List* newList = new List();
    newList->p_head = nullptr;
    newList->p_tail = nullptr;
    for (int i = 0; i < n; ++i)
    {
        addTail(newList, arr[i]);
    }
    return newList;
}

// function to compare two lists
bool areListsEqual(List* list1, List* list2)
{
    NODE* current1 = list1 ? list1->p_head : nullptr;
    NODE* current2 = list2 ? list2->p_head : nullptr;
    while (current1 && current2)
    {
        if (current1->key != current2->key)
        {
            return false;
        }
        current1 = current1->p_next;
        current2 = current2->p_next;
    }
    return (current1 == nullptr && current2 == nullptr);
}

// function to free the memory of a list
void freeList(List* L)
{
    NODE* current = L->p_head;
    while (current)
    {
        NODE* next = current->p_next;
        delete current;
        current = next;
    }
    delete L;
}

NODE* createNode(int data) {
    NODE* newNode = new NODE();
    newNode->key = data;
    newNode->p_next = nullptr;
    newNode->p_prev = nullptr;
    return newNode;
}

List* createList(NODE* p_node) {
    List* newList = new List(p_node, p_node);
    return newList;
}

bool addHead(List*& L, int data) {
    NODE* newNode = createNode(data);
    if (L == nullptr) {
        L = new List();
    }

    if (L->p_head == nullptr) {
        L->p_head = newNode;
        L->p_tail = newNode;
    }
    else {
        newNode->p_next = L->p_head;
        L->p_head->p_prev = newNode;
        L->p_head = newNode;
    }
    return true;
}

bool addTail(List*& L, int data) {
    NODE* newNode = createNode(data);
    if (L->p_head == nullptr) {
        L->p_head = newNode;
        L->p_tail = newNode;
    }
    else {
        newNode->p_prev = L->p_tail;
        L->p_tail->p_next = newNode;
        L->p_tail = newNode;
    }
    return true;
}

bool removeHead(List*& L) {
    if (L->p_head == nullptr) return false;

    NODE* temp = L->p_head;
    L->p_head = L->p_head->p_next;

    if (L->p_head != nullptr) L->p_head->p_prev = nullptr;
    else L->p_tail = nullptr;

    delete temp;
    return true;
}

void removeTail(List*& L) {
    if (L->p_head == nullptr) return;

    if (L->p_head == L->p_tail) {
        delete L->p_head;
        L->p_head = nullptr;
        L->p_tail = nullptr;
        return;
    }

    NODE* temp = L->p_tail;
    L->p_tail = L->p_tail->p_prev;
    L->p_tail->p_next = nullptr;
    delete temp;
}

void removeAll(List*& L) {
    if (L == nullptr || L->p_head == nullptr) return;

    NODE* current = L->p_head;
    while (current != nullptr) {
        NODE* next = current->p_next;
        delete current;
        current = next;
    }

    L->p_head = nullptr;
    L->p_tail = nullptr;
}

void removeBefore(List*& L, int val) {
    if (L == nullptr || L->p_head == nullptr || L->p_head->key == val) return;

    if (L->p_head->p_next != nullptr && L->p_head->p_next->key == val) {
        NODE* temp = L->p_head;
        L->p_head = L->p_head->p_next;
        L->p_head->p_prev = nullptr;
        delete temp;
        if (L->p_head == nullptr) L->p_tail = nullptr;
        return;
    }

    NODE* current = L->p_head;
    while (current != nullptr && current->key != val) {
        current = current->p_next;
    }

    if (current != nullptr && current->p_prev != nullptr && current->p_prev->p_prev != nullptr) {
        NODE* toDelete = current->p_prev;
        NODE* prevNode = toDelete->p_prev;

        prevNode->p_next = current;
        current->p_prev = prevNode;

        delete toDelete;
    }
}

void removeAfter(List*& L, int val) {
    if (L == nullptr || L->p_head == nullptr) return;

    NODE* current = L->p_head;
    while (current != nullptr && current->key != val) {
        current = current->p_next;
    }
    
    if (current != nullptr && current->p_next != nullptr) {
        NODE* temp = current->p_next;
        current->p_next = temp->p_next;
        if (temp == L->p_tail) {
            L->p_tail = current;
        }
        delete temp;
    }
}

bool addPos(List*& L, int data, int pos) {
    if (pos < 0) return false;

    if (pos == 0) return addHead(L, data);

    NODE* current = L->p_head;
    int index = 0;

    while (current != nullptr && index < pos - 1) {
        current = current->p_next;
        index++;
    }

    if (current == nullptr) return false;

    NODE* newNode = createNode(data);
    newNode->p_next = current->p_next;
    newNode->p_prev = current;

    if (current->p_next != nullptr) {
        current->p_next->p_prev = newNode;
    }
    else {
        L->p_tail = newNode;
    }

    current->p_next = newNode;

    return true;
}

void removePos(List*& L, int data, int pos) {
    if (pos < 0 || L == nullptr || L->p_head == nullptr) return;

    if (pos == 0) {
        removeHead(L);
        return;
    }

    NODE* current = L->p_head;
    int index = 0;

    while (current != nullptr && index < pos) {
        current = current->p_next;
        index++;
    }

    if (current == nullptr) return;

    if (current->p_prev != nullptr) {
        current->p_prev->p_next = current->p_next;
    }

    if (current->p_next != nullptr) {
        current->p_next->p_prev = current->p_prev;
    }
    else {
        L->p_tail = current->p_prev;
    }

    delete current;
}

bool addBefore(List*& L, int data, int val) {
    if (L == nullptr || L->p_head == nullptr) return false;

    if (L->p_head->key == val) {
        return addHead(L, data);
    }

    NODE* current = L->p_head;
    while (current != nullptr && current->key != val) {
        current = current->p_next;
    }

    if (current == nullptr) return false;

    NODE* newNode = createNode(data);
    newNode->p_next = current;
    newNode->p_prev = current->p_prev;

    if (current->p_prev != nullptr) {
        current->p_prev->p_next = newNode;
    }

    current->p_prev = newNode;

    if (newNode->p_prev == nullptr) {
        L->p_head = newNode;
    }

    return true;
}

bool addAfter(List*& L, int data, int val) {
    NODE* current = L->p_head;
    while (current != nullptr && current->key != val) {
        current = current->p_next;
    }

    if (current == nullptr) return false;

    NODE* newNode = createNode(data);
    newNode->p_next = current->p_next;
    newNode->p_prev = current;

    if (current->p_next != nullptr) {
        current->p_next->p_prev = newNode;
    }
    else {
        L->p_tail = newNode;
    }

    current->p_next = newNode;

    return true;
}

void printList(List* L) {
    NODE* current = L->p_head;
    while (current != nullptr) {
        cout << current->key << " ";
        current = current->p_next;
    }
    cout << endl;
}

int countElements(List* L) {
    int count = 0;
    NODE* current = L->p_head;
    while (current != nullptr) {
        count++;
        current = current->p_next;
    }
    return count;
}

List* reverseList(List* L) {
    if (L == nullptr || L->p_head == nullptr) return new List();

    List* newList = new List();
    NODE* current = L->p_head;

    while (current != nullptr) {
        addHead(newList, current->key);
        current = current->p_next;
    }

    return newList;
}

void removeDuplicate(List*& L) {
    if (L == nullptr || L->p_head == nullptr) return;

    NODE* current = L->p_head;
    while (current != nullptr) {
        NODE* runner = current->p_next;
        while (runner != nullptr) {
            if (runner->key == current->key) {
                NODE* temp = runner;
                if (runner->p_prev != nullptr) {
                    runner->p_prev->p_next = runner->p_next;
                }
                if (runner->p_next != nullptr) {
                    runner->p_next->p_prev = runner->p_prev;
                }
                else {
                    L->p_tail = runner->p_prev;
                }
                runner = runner->p_next;
                delete temp;
            }
            else {
                runner = runner->p_next;
            }
        }
        current = current->p_next;
    }
}

bool removeElement(List*& L, int key) {
    if (L == nullptr || L->p_head == nullptr) return false;

    if (L->p_head->key == key) {
        return removeHead(L);
    }

    NODE* current = L->p_head;
    while (current != nullptr && current->key != key) {
        current = current->p_next;
    }

    if (current == nullptr) return false;

    if (current->p_prev != nullptr) {
        current->p_prev->p_next = current->p_next;
    }

    if (current->p_next != nullptr) {
        current->p_next->p_prev = current->p_prev;
    }
    else {
        L->p_tail = current->p_prev;
    }

    delete current;
    return true;
}

int main() {
	List* list = nullptr;
	addHead(list, 10);
	addTail(list, 20);
	addTail(list, 30);
	printList(list);
	removeHead(list);
	printList(list);
	removeTail(list);
	printList(list);
	addBefore(list, 15, 20);
	printList(list);
	addAfter(list, 25, 20);
	printList(list);
	removeBefore(list, 20);
	printList(list);
	removeAfter(list, 20);
	printList(list);
	removeAll(list);
	printList(list);
	freeList(list);
	return 0;
}