#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct NODE {
    int key;
    NODE* p_next;
};

struct Queue {
    NODE* front;
    NODE* rear;
};

void printQueue(Queue& q, ofstream& output) {
    NODE* temp = q.front;
    if (temp == nullptr) {
        output << "EMPTY" << endl;
    }
    else {
        while (temp != nullptr) {
            output << temp->key << " ";
            temp = temp->p_next;
        }
        output << endl;
    }
}

void enqueue(Queue& q, int key, ofstream& output) {
    NODE* newNode = new NODE;
    newNode->key = key;
    newNode->p_next = nullptr;

    if (q.rear == nullptr) {
        q.front = q.rear = newNode;
    }
    else {
        q.rear->p_next = newNode;
        q.rear = newNode;
    }
    printQueue(q, output);
}

int dequeue(Queue& q, ofstream& output) {
    if (q.front == nullptr) {
        output << "EMPTY" << endl;
        return -1;
    }
    NODE* temp = q.front;
    int removedKey = temp->key;
    q.front = q.front->p_next;
    if (q.front == nullptr) {
        q.rear = nullptr;
    }
    delete temp;
    printQueue(q, output);
    return removedKey;
}

int size(Queue& q) {
    NODE* temp = q.front;
    int count = 0;
    while (temp != nullptr) {
        count++;
        temp = temp->p_next;
    }
    return count;
}

bool isEmpty(Queue& q) {
    return q.front == nullptr;
}

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");

    if (!input) {
        cerr << "Cannot open input file!" << endl;
        return 1;
    }
    if (!output) {
        cerr << "Cannot open output file!" << endl;
        return 1;
    }

    Queue queue;
    queue.front = queue.rear = nullptr;

    int key;
    string command;

    while (input >> command) {
        if (command == "init") {
            if (isEmpty(queue)) {
                output << "EMPTY" << endl;
            }
            else {
                printQueue(queue, output);
            }
        }
        else if (command == "enqueue") {
            input >> key;
            enqueue(queue, key, output);
        }
        else if (command == "dequeue") {
            dequeue(queue, output);
        }
        else if (command == "size") {
            output << size(queue) << endl;
        }
        else if (command == "empty") {
            if (isEmpty(queue)) {
                output << "EMPTY" << endl;
            }
            else {
                output << "1" << endl;
            }
        }
        else {
            output << "Unknown command: " << command << endl;
            break;
        }
    }

    while (!isEmpty(queue)) {
        dequeue(queue, output);
    }

    input.close();
    output.close();

    return 0;
}
