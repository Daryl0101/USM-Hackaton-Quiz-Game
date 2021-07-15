#include <iostream>
#include <string>
#include "Participant.h";
using namespace std;

Participant::Participant() {
	head = nullptr;
	end = nullptr;
}

Participant::~Participant() {
	clear();
}

void Participant::appendNode(string n, int s, int g) {
	PartNode* newNode = new PartNode;
	newNode->name = n;
	newNode->score = s;
	newNode->group = g;
	newNode->next = nullptr;
	newNode->prev = nullptr;
	//If the list is empty
	if (isEmpty()) {
		head = newNode;
		end = newNode;
	}
	else {
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
	}
}

void Participant::insertNode(string n, int s, int g) {
	PartNode* nodePtr = nullptr;
	PartNode* prevNode = nullptr;
	//Allocate a new node and store the details in it
	PartNode* newNode = new PartNode;
	newNode->name = n;
	newNode->score = s;
	newNode->group = g;
	newNode->next = nullptr;
	newNode->prev = nullptr;
	//If there are no nodes in the list
	if (isEmpty()) {
		head = newNode;
		end = newNode;
	}
	else {
		bool found = false;
		nodePtr = head;
		prevNode = nullptr;
		//Traverse through the list to find the suitable place to insert
		while (nodePtr != nullptr && !found) {
			if (nodePtr->score <= s)
				found = true;
			else {
				prevNode = nodePtr;
				nodePtr = nodePtr->next;
			}
		}
		//If the new node is the first in the list
		if (nodePtr == head) {
			head->prev = newNode;
			newNode->next = head;
			head = newNode;
		}
		//If the node is the last in the list
		else if (nodePtr != nullptr) {
			prevNode->next = newNode;
			newNode->prev = prevNode;
			newNode->next = nodePtr;
			nodePtr->prev = newNode;
		}
		//Otherwise, insert the node between prevNode and nodePtr
		else {
			prevNode->next = newNode;
			newNode->prev = prevNode;
			end = newNode;

		}
	}
}

void Participant::deleteNode(string n) {
	PartNode* nodePtr = nullptr;
	PartNode* prevNode = nullptr;
	//If the list is empty
	if (isEmpty()) {
		cout << "There are no participants!\n";
		return;
	}
	//If the list is not empty
	nodePtr = head;
	bool found = false;
	//If the participant is the head
	if (head->name == n) {
		nodePtr = head;
		head = head->next;
		if (head != nullptr) {
			head->prev = nullptr;
		}
		else {
			end = nullptr;
		}
		delete nodePtr;
	}
	while (nodePtr != nullptr && !found) {
		if (nodePtr->name == n)
			found = true;
		else {
			prevNode = nodePtr;
			nodePtr = nodePtr->next;
		}
	}
	//If the participant is not found
	if (nodePtr == nullptr) {
		cout << "The participant cannot be found!\n";
	}
	//If the participant is not the head
	if (nodePtr->name == n) {
		prevNode->next = nodePtr->next;
		if (nodePtr->next != nullptr) {
			nodePtr->next->prev = prevNode;
		}
		if (nodePtr == end) {
			end = prevNode;
		}
		delete nodePtr;
	}
}

void Participant::changeScore(string n, int s) {
	PartNode* nodePtr = nullptr;
	//If the list is empty
	if (isEmpty()) {
		cout << "changeScore empty!\n";
		return;
	}
	//If the list is not empty
	nodePtr = head;
	while (nodePtr != nullptr && nodePtr->name != n) {
		nodePtr = nodePtr->next;
	}
	//If the participant is not found
	if (nodePtr == nullptr) {
		cout << "changeScore not found!\n";
	}
	//If the participant is the head
	else if (head->name == n) {
		head->score += s;
	}
	//If the participant is not the head
	else if (nodePtr->name == n) {
		nodePtr->score += s;
	}
}

void Participant::setScore(string n, int s) {
	PartNode* nodePtr = nullptr;
	//If the list is empty
	if (isEmpty()) {
		cout << "setScore empty!\n";
		return;
	}
	//If the list is not empty
	nodePtr = head;
	while (nodePtr != nullptr && nodePtr->name != n) {
		nodePtr = nodePtr->next;
	}
	//If the participant is not found
	if (nodePtr == nullptr) {

	}
	//If the participant is the head
	else if (head->name == n) {
		head->score = s;
	}
	//If the participant is not the head
	else if (nodePtr->name == n) {
		nodePtr->score = s;
	}
}

void Participant::displayList()const {
	PartNode* nodePtr = nullptr;
	nodePtr = head;
	//If the list is empty
	if (isEmpty()) {
		cout << "There are no participants!\n";
	}
	//If the list is not empty
	else {
		while (nodePtr != nullptr) {
			cout << nodePtr->name << "\t\t" << nodePtr->group << "\t\t" << nodePtr->score << endl;
			nodePtr = nodePtr->next;
		}
	}
}

void Participant::displayList_rev()const {
	PartNode* nodePtr = nullptr;
	nodePtr = end;
	while (nodePtr != nullptr) {
		cout << nodePtr->name << "\t\t" << nodePtr->group << "\t\t" << nodePtr->score << endl;
		nodePtr = nodePtr->prev;
	}
}

bool Participant::isEmpty()const {
	return (head == nullptr);
}

void Participant::returnNode(string& n, int& s, int& g, int whichNode)const {
	PartNode* nodePtr = nullptr;
	nodePtr = head;
	for (int i = 0; i < whichNode; i++) {
		nodePtr = nodePtr->next;
	}
	n = nodePtr->name; s = nodePtr->score; g = nodePtr->group;
}

void Participant::returnNode_rev(string& n, int& s, int& g, int whichNode)const {
	PartNode* nodePtr = nullptr;
	nodePtr = end;
	for (int i = 0; i < whichNode; i++) {
		nodePtr = nodePtr->prev;
	}
	n = nodePtr->name; s = nodePtr->score; g = nodePtr->group;
}

void Participant::calcTotalScore(int& s, int& g)const {
	PartNode* nodePtr = nullptr;
	if (isEmpty()) {
		cout << "calcTotalScore!\n";
	}
	else {
		nodePtr = head;
		g = nodePtr->group; s = nodePtr->score;
		while (nodePtr->next != nullptr) {
			s += nodePtr->score;
			nodePtr = nodePtr->next;
		}
	}
}

void Participant::clear() {
	PartNode* nodePtr = nullptr;
	while (head != nullptr) {
		nodePtr = head;
		head = head->next;
		delete nodePtr;
	}
	end = nullptr;
}