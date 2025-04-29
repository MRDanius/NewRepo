#pragma once

#include "Point.h"

class SimpleStack {
private:
    struct Node {
        Point data;
        Node* next;
        Node(Point p);
    };
    Node* topNode;

public:
    SimpleStack();
    ~SimpleStack();
    void push(Point p);
    void pop();
    Point top() const;
    bool isEmpty() const;
};