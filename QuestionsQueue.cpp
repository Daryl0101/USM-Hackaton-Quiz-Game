#include <iostream>
#include <string>
#include "QuestionsQueue.h"
using namespace std;

QuestionsQueue::QuestionsQueue() {
	rear = front = nullptr;
}

QuestionsQueue::~QuestionsQueue() {
	clear();
}

void QuestionsQueue::enqueue(int n, string q, string a1, string a2, string a3, string a4, char corr) {
	QuesNode* newNode = new QuesNode(n, q, a1, a2, a3, a4, corr);
	QuesNode* nodePtr = nullptr;
	//If the queue is empty
	if (isEmpty()) {
		front = newNode;
		rear = newNode;
	}
	//If the queue is not empty
	else {
		rear->next = newNode;
		rear = newNode;
	}
	count++;
}

void QuestionsQueue::dequeue(int& n, string& q, string& a1, string& a2, string& a3, string& a4, char& corr) {
	//If the queue is empty
	if (isEmpty()) {
		cout << "There are no questions!\n";
	}
	//If the queue is not empty
	else {
		n = front->num; q = front->ques; a1 = front->ans1; a2 = front->ans2; a3 = front->ans3; a4 = front->ans4; corr = front->correct;
		QuesNode* nodePtr = nullptr;
		nodePtr = front;
		front = front->next;
		delete nodePtr;
		count--;
	}
}

void QuestionsQueue::displayNode(int n) {
	QuesNode* nodePtr = front;
	for (int i = 0; i < n; i++) {
		nodePtr = nodePtr->next;
	}
	cout << nodePtr->num << "\t" << nodePtr->ques << endl;
	cout << "a. " << nodePtr->ans1 << endl
		<< "b. " << nodePtr->ans2 << endl
		<< "c. " << nodePtr->ans3 << endl
		<< "d. " << nodePtr->ans4 << endl;
}

bool QuestionsQueue::isEmpty() {
	bool status;
	if (count > 0)
		status = false;
	else
		status = true;
	return status;
}

void QuestionsQueue::clear() {
	int n; string q; string a1; string a2; string a3; string a4; char corr;

	while (!isEmpty()) {
		dequeue(n, q, a1, a2, a3, a4, corr);
	}
}