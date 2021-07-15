#ifndef PARTICIPANT_H
#define PARTICIPANT_H
#include <iostream>
#include <string>
using namespace std;

//Linked list for Participants' details
class Participant {
private:
	struct PartNode {
		string name;
		int score, group;
		PartNode* next = nullptr;
		PartNode* prev = nullptr;
	};
	PartNode* head;
	PartNode* end;
public:
	Participant();
	~Participant();
	void appendNode(string, int, int);	//To append the participants
	void insertNode(string, int, int);	//To insert new participants into the list
	void deleteNode(string);		//To delete the participants
	void changeScore(string, int);	//To add/subtract the score of participants
	void setScore(string, int);	//To reset the score of the participants
	void displayList()const;		//To display the list
	void displayList_rev()const;	//To display the list in reverse
	bool isEmpty()const;					//To check if the list is empty
	void returnNode(string&, int&, int&, int)const;
	void returnNode_rev(string&, int&, int&, int)const;
	void calcTotalScore(int&, int&)const;
	void clear();
};
#endif