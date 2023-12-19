#pragma once

#include <iostream>
using namespace std;

struct Node {
	char data;
	Node* next;
	Node* prev;
};

typedef Node* NodePtr;

class MyStackLinkedList {
private:
	NodePtr tail;
public:
	MyStackLinkedList() {
		tail = nullptr;
	}

	void push(char item) {
		NodePtr node = new Node;
		node->data = item;
		node->next = nullptr;
		node->prev = nullptr;

		if (tail == nullptr) {
			tail = node;
		}
		else {
			tail->next = node;
			node->prev = tail;
			tail = node;
		}
	}

	char pop() {
		if (tail == nullptr) {
			cout << "stack is empty" << endl;
			return ' ';
		}

		char item = tail->data;
		NodePtr prev = tail->prev;
		if (prev != nullptr) {
			prev->next = nullptr;
		}
		tail->prev = nullptr;
		delete tail;
		tail = prev;
		return item;
	}

	char peek() {
		if (tail == nullptr) {
			cout << "stack is empty" << endl;
			return ' ';
		}

		return tail->data;
	}

	bool isEmpty() {
		return tail == nullptr;
	}

	void printStack() {
		NodePtr current = tail;
		while (current != nullptr) {
			cout << current->data << " ";
			current = current->prev;
		}
		cout << endl;
	}

};