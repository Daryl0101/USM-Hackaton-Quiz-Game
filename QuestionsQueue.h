#ifndef QUESTIONSQUEUE_H
#define QUESTIONSQUEUE_H
#include <iostream>
#include <string>
using namespace std;

class QuestionsQueue {
private:
	struct QuesNode {
		string ques;
		string ans1, ans2, ans3, ans4;
		char correct;
		int num;
		QuesNode* next;
		QuesNode(int n, string q, string a1, string a2, string a3, string a4, char corr) {
			num = n; ques = q; ans1 = a1; ans2 = a2; ans3 = a3; ans4 = a4; correct = corr;
		}
	};
	QuesNode* front = nullptr;
	QuesNode* rear = nullptr;
	int count;
public:
	QuestionsQueue();
	~QuestionsQueue();
	void enqueue(int, string, string, string, string, string, char);
	void dequeue(int&, string&, string&, string&, string&, string&, char&);
	bool isEmpty();
	bool isFull();
	void clear();
	void displayNode(int);
};
#endif