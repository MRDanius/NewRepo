#include "SimpleStack.h"


SimpleStack::Node::Node(Point p) : data(p), next(nullptr) {}

SimpleStack::SimpleStack() : topNode(nullptr) {}

SimpleStack::~SimpleStack() {
    while (!isEmpty()) pop();
}

void SimpleStack::push(Point p) {
    Node* newNode = new Node(p);
    newNode->next = topNode;
    topNode = newNode;
}

void SimpleStack::pop() {
    if (isEmpty()) return;
    Node* temp = topNode;
    topNode = topNode->next;
    delete temp;
}

Point SimpleStack::top() const {
    if (isEmpty()) return Point();
    return topNode->data;
}

bool SimpleStack::isEmpty() const {
    return topNode == nullptr;
}