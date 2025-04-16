#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct NODE {
    int key;
    NODE* p_next;
};

struct Stack {
    NODE* top;
};

void printStack(Stack& s, ofstream& output) {
    NODE* temp = s.top;
    Stack tempStack;
    tempStack.top = nullptr;

    while (temp != nullptr) {
        NODE* newNode = new NODE;
        newNode->key = temp->key;
        newNode->p_next = tempStack.top;
        tempStack.top = newNode;
        temp = temp->p_next;
    }

    temp = tempStack.top;
    if (temp == nullptr) {
        output << "EMPTY" << endl;
    }
    else {
        while (temp != nullptr) {
            output << temp->key << " ";
            NODE* toDelete = temp;
            temp = temp->p_next;
            delete toDelete;
        }
        output << endl;
    }
}


void push(Stack& s, int key, ofstream& output) {
    NODE* newNode = new NODE;
    newNode->key = key;
    newNode->p_next = s.top;
    s.top = newNode;
    printStack(s, output);
}

int pop(Stack& s, ofstream& output) {
    if (s.top == nullptr) {
        output << "EMPTY" << endl;
        return -1;
    }
    NODE* temp = s.top;
    s.top = s.top->p_next;
    delete temp;
    printStack(s, output);
}

int size(Stack& s) {
    NODE* temp = s.top;
    int count = 0;
    while (temp != nullptr) {
        count++;
        temp = temp->p_next;
    }
    return count;
}

bool isEmpty(Stack& s) {
    return s.top == nullptr;
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

    Stack stack;
    stack.top = nullptr;

    int key;
    string command;

    while (input >> command) {
        if (command == "init") {
            if (isEmpty(stack)) {
                output << "EMPTY" << endl;
            }
            else {
                printStack(stack, output);
            }
        }
        else if (command == "push") {
            input >> key;
            push(stack, key, output);
        }
        else if (command == "pop") {
            pop(stack, output);
        }
        else if (command == "size") {
            output << size(stack) << endl;
        }
        else if (command == "empty") {
            if (isEmpty(stack)) {
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

    while (stack.top != nullptr) {
        pop(stack, output);
    }

    input.close();
    output.close();

    return 0;
}
