#include <iostream>
#include <string>
#include <math.h>
using namespace std;

struct Node {
	int data;
	Node *next;
};

struct Stack {
	Node *head;
	Node *iter;
};

void MAKENULL(Stack &stack) {
	stack.head = NULL;
	stack.iter = NULL;
}

bool isEmpty(Stack s) {
	return s.head == NULL;
}

void push(Stack &s, int data) {
	if (isEmpty(s)) {
		s.head = new Node;
		s.iter = s.head;
	}
	else {
		s.iter->next = new Node;
		s.iter = s.iter->next;
	}
	s.iter->next = NULL;
	s.iter->data = data;
}

int pop(Stack &s) {
	if (isEmpty(s)) return -1;
	Node *temp = s.head;
	Node *prev = NULL;
	while (temp->next != NULL) {
		prev = temp;
		temp = temp->next;
	}
	if (prev == NULL)
		MAKENULL(s);
	else {
		s.iter = prev;
		s.iter->next = NULL;
	}
	return temp->data;
}

void printStack(Stack s) {
	Node *temp = s.head;
	int count = -1;
	cout << endl;
	while (temp != NULL) {
		count++;
		cout << count << ": " << temp->data << endl;
		temp = temp->next;
	}
	cout << endl;
}

int getSize(Stack s) {
	Node *temp = s.head;
	int count = 0;
	while (temp != NULL) {
		count++;
		temp = temp->next;
	}
	return count;
}

int getTop(Stack s) {
	return s.iter->data;
}

void main() {
	string exp[50];
	float result = 0;
	int expSize = 0;
	cout << "Enter an expression enter = to stop: ";
	for (int i = 0; i < 50; i++) {
		cin >> exp[i];
		if (!exp[i].compare("=")) break;
		expSize++;
	}
	Stack st;
	MAKENULL(st);
	for (int i = 0; i<expSize; i++) {
		result = 0;
		if (exp[i] != "+" && exp[i] != "-" && exp[i] != "*" && exp[i].compare("/") && exp[i].compare("^")) {
			push(st, stoi(exp[i]));
		}
		else if (!exp[i].compare("+")) {
			printStack(st);
			result = pop(st);
			result += pop(st);
			push(st, result);
		}
		else if (!exp[i].compare("-")) {
			printStack(st);
			result = pop(st);
			result -= pop(st);
			push(st, -result);
		}
		else if (!exp[i].compare("*")) {
			printStack(st);
			result = pop(st);
			result *= pop(st);
			push(st, result);
		}
		else if (!exp[i].compare("/")) {
			int res1 = 0;
			printStack(st);
			res1 = pop(st);
			result = pop(st);
			result = result / res1;
			push(st, result);
		}
		else if (!exp[i].compare("^")) {

			printStack(st);
			int po = pow((double)pop(st), (double)pop(st));
			result += po;
			push(st, result);
		}
		else {
			cout << "expression invalid!";
		}
	}
	cout << endl << endl;
	printStack(st);
	system("pause");
}