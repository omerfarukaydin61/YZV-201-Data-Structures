// YZV_201.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <string>
#include <iostream>
#include "stack.h"
using namespace std;

StackNode::StackNode() {
	data_ = 0;
	next_ = nullptr;
}
StackNode::StackNode(int data) {
	data_ = data;
	next_ = nullptr;
}

void Stack::Push(int data) {	// Pushes the data to the top of the stack
	if (Is_Empty())
	{
		StackNode* newNode = new StackNode();
		newNode->data_ = data;
		this->top = newNode;
		return;
	}
	StackNode* newNode = new StackNode();
	newNode->data_ = data;
	newNode->next_ = this->top;
	this->top = newNode;
	return;
}
void Stack::Pop() {		// Pops the top of the stack
	if (!Is_Empty())
	{
		StackNode* newNode = new StackNode();
		newNode = this->top->next_;
		delete this->top;
		this->top = newNode;
	}
}
StackNode* Stack::Peek() {		// Returns the top of the stack
	return this->top;
}
int Stack::Size()		// Returns the size of the stack
{
	int size = 0;
	StackNode* temp = this->top;
	while (temp != nullptr)
	{
		size++;
		temp = temp->next_;
	}
	return size;
}
void Stack::print_all() {		// Prints all the elements of the stack
	if (!Is_Empty())
	{
		StackNode* temp = this->top;
		while (temp != NULL && temp != nullptr)
		{
			PrintToConsole(temp->data_);
			temp = temp->next_;
		}
	}
	return;
}
template <typename T>		// Template function to print any type of data to the console
void Stack::PrintToConsole(T item) {		// Prints the given item to the console
	std::cout << item << std::endl;
}
bool Stack::Is_Descending() {		// Checks if the stack is descending
	bool result = true;
	if (!Is_Empty())
	{
		StackNode* temp = this->top;
		while (temp != nullptr && temp->next_ != nullptr)
		{
			if (temp->data_ <= temp->next_->data_)
			{
				temp = temp->next_;
			}
			else
			{
				result = false;
				return result;
			}
		}
	}
	return result;
}
void Stack::Sequentilized() {		// Sequentilizes the stack
	if (!Is_Empty())
	{
		StackNode* first = this->top;
		StackNode* second = this->top->next_;

		while (first->next_ != nullptr && second->next_ != nullptr && first->data_ - second->data_ == -1)
		{
			first = second;
			second = second->next_;
		}

		first->next_ = nullptr;

		while (second != nullptr)
		{
			first = second;
			second = second->next_;
			delete first;
		}
	}
}
void Stack::Merge_Basket(Stack* stack) {		// Merges the given stack to the current stack
	if (!stack->Is_Empty())
	{
		StackNode* temp = stack->top;
		while (temp != nullptr)
		{
			StackNode* newNode = new StackNode();
			newNode->data_ = temp->data_;
			newNode->next_ = nullptr;
			if (this->top == nullptr || this->top->data_ >= newNode->data_)
			{
				newNode->next_ = this->top;
				this->top = newNode;
			}
			else
			{
				StackNode* current = this->top;
				while (current->next_ != NULL && current->next_->data_ < newNode->data_)
				{
					current = current->next_;
				}
				newNode->next_ = current->next_;
				current->next_ = newNode;
			}
			temp = temp->next_;
		}
		stack->emptyAllNodes();
	}
}
bool Stack::Is_Empty() {		// Checks if the stack is empty
	if (this->top == nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void Stack::emptyAllNodes()		// Empties all the nodes of the stack
{
	StackNode* temp = top;
	StackNode* tempNext = NULL;
	while (temp != NULL) {
		tempNext = temp->next_;
		delete temp;
		temp = tempNext;
	}
	top = NULL;
	delete temp;
	delete tempNext;
}
Stack::Stack() {		// Constructor
	this->top = nullptr;
}
Stack::~Stack() {		// Destructor
	this->emptyAllNodes();
}
