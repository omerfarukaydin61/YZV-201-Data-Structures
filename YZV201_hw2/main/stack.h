#include <iostream>
#include <cstdlib>
#include <limits>
#include <string>
using namespace std;

class StackNode {
public:
    int data_;
    StackNode* next_;

    StackNode();
    StackNode(int data);
};
class Stack {
public:
    StackNode* top;

    void Push(int data);
    void Pop();
    StackNode* Peek();
    int Size();
    void print_all();
    template <typename T>
    void PrintToConsole(T item);
    bool Is_Descending();
    void Sequentilized();
    void Merge_Basket(Stack* stack);
    bool Is_Empty();
    void emptyAllNodes();
    Stack();
    ~Stack();
};