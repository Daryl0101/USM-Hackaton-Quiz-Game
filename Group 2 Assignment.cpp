#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "Participant.h"
#include "QuestionsQueue.h"
using namespace std;

void welcome_interface();
void game_tutorial();
void importFile(QuestionsQueue&, ifstream&, string, int&);
void validation(int&, int);
void validate_char(char&, char, char, char, char);
void validate_char2(char&, char, char, char, char, char, char);
void showRanking(Participant[], Participant&, int, int, int);

int main() {
	char main_menu_choice;
	bool goback = true;
	//Temporary variables to hold questions' details
	string ques, a1, a2, a3, a4;
	char ans;
	int num;
	//Total counters
	int num_of_ques = 0, num_of_groups = 0, num_of_players = 0;
	//Temporary variables to hold the players' details
	string tempName;
	int tempScore, tempGroup;
	QuestionsQueue QuestionSet;	//Queue holds all questions and their choices with answers

	while (goback) {

		//Interface: Name of Game, Welcoming note
		welcome_interface();
		//Main Menu
		cout << "Main Menu\n"
			<< "-----------------------------------------------------------\n"
			<< "A. New Game\n"
			<< "B. How To Play\n"
			<< "C. Exit Program\n"
			<< "-----------------------------------------------------------\n";
		cin >> main_menu_choice;
		validate_char2(main_menu_choice, 'A', 'B', 'C', 'a', 'b', 'c');
		system("cls");

		if (main_menu_choice == 'a' || main_menu_choice == 'A') {
			//Open file
			ifstream file;
			string fileToOpen = "Hackathon2_Questions&Ans.txt";
			//Import questions into QuestionSet
			importFile(QuestionSet, file, fileToOpen, num_of_ques);

			//User insert how many groups and how many players per group
			cout << "Number of Groups:\t\t";
			cin >> num_of_groups;
			validation(num_of_groups, 0);	//Input validation
			cout << "Number of Players per Group:\t";
			cin >> num_of_players;
			validation(num_of_players, 0);	//Input validation

			Participant* Groups = new Participant[num_of_groups];	//Each linked list holds a group
			//Input the names for all players from each group into linked list
			cin.ignore();
			for (int i = 0; i < num_of_groups; i++) {
				cout << "---Group " << i + 1 << "---\n";
				for (int j = 0; j < num_of_players; j++) {
					cout << "Name of Player " << j + 1 << ": ";
					getline(cin, tempName);
					Groups[i].appendNode(tempName, 0, i + 1);
				}
				//Reset the temporary variables
				tempName.clear();
				tempScore = 0, tempGroup = 0;
			}
			system("cls");

			//To arrange the players into their turns (G1P1,G2P1,G1P2,G2P2...)
			Participant PlayerTurns;
			for (int j = 0; j < num_of_players; j++) {
				for (int k = num_of_groups; k > 0; k--) {
					Groups[k - 1].returnNode(tempName, tempScore, tempGroup, j);
					PlayerTurns.appendNode(tempName, tempScore, tempGroup);
				}
			}

			/************************************************************************************
			* Game starts:																		*
			* 1) Every player will have one chance of answering each question					*
			* 2) If the player gave the correct answer, they will gain 2 marks					*
			* 3) If the player gave the wrong answer, they will lose 1 mark						*
			* 4) The player with the highest marks wins the MVP Award							*
			* 5) The group with the highest marks wins the Best Team Award						*
			************************************************************************************/
			int total_players = num_of_groups * num_of_players;
			char player_ans;
			for (int i = 0; i < num_of_ques; i++) {
				QuestionSet.dequeue(num, ques, a1, a2, a3, a4, ans);
				for (int j = 0; j < total_players; j++) {
					cout << "-------------------------------------------------------------------------------------------\n"
						<< "| " << num << ") " << ques << endl
						<< "| " << "A. " << a1 << endl
						<< "| " << "B. " << a2 << endl
						<< "| " << "C. " << a3 << endl
						<< "| " << "D. " << a4 << endl
						<< "-------------------------------------------------------------------------------------------\n";
					PlayerTurns.returnNode(tempName, tempScore, tempGroup, j);	//To get the particulars of the player
					cout << tempName << "'s turn\t\t\t\t\tScore: " << tempScore << "/" << num_of_ques * 2 << endl
						<< "Answer(a/b/c/d): ";
					cin >> player_ans;
					validate_char(player_ans, 'a', 'b', 'c', 'd');	//Input validation
					if (ans == player_ans) {
						cout << "Your answer is correct!\n";
						PlayerTurns.changeScore(tempName, 2);
						system("pause");
					}
					else if (ans != player_ans) {
						cout << "Your answer is wrong!\nThe correct answer is '" << ans << "' " << endl;
						PlayerTurns.changeScore(tempName, -1);
						system("pause");
					}
					//Clear screen
					system("cls");
				}
				//Reset the temporary variables
				tempName.clear();
				tempScore = 0, tempGroup = 0;
			}

			//To rank all the players
			Participant Ranking;
			for (int i = 0; i < total_players; i++) {
				PlayerTurns.returnNode(tempName, tempScore, tempGroup, i);
				Ranking.insertNode(tempName, tempScore, tempGroup);
			}
			//Reset the temporary variables
			tempName.clear();
			tempScore = 0, tempGroup = 0;
			//To set the scores of each player in their respective groups
			for (int i = 0; i < num_of_groups; i++) {
				for (int j = 0; j < total_players; j++) {
					PlayerTurns.returnNode(tempName, tempScore, tempGroup, j);
					Groups[i].setScore(tempName, tempScore);
				}
			}
			//Reset the temporary variables
			tempName.clear();
			tempScore = 0, tempGroup = 0;
			Participant* Groups_temp = new Participant[num_of_groups];	//Temporary linked list for Groups[]
			//To rank the players in their respective groups
			for (int i = 0; i < num_of_groups; i++) {
				for (int j = 0; j < num_of_players; j++) {
					Groups[i].returnNode(tempName, tempScore, tempGroup, j);
					Groups_temp[i].appendNode(tempName, tempScore, tempGroup);
				}
				Groups[i].clear();
				//Reset the temporary variables
				tempName.clear();
				tempScore = 0, tempGroup = 0;
				for (int k = 0; k < num_of_players; k++) {
					Groups_temp[i].returnNode(tempName, tempScore, tempGroup, k);
					Groups[i].insertNode(tempName, tempScore, tempGroup);
				}
			}
			delete[] Groups_temp;
			//Reset the temporary variables
			tempName.clear();
			tempScore = 0, tempGroup = 0;

			showRanking(Groups, Ranking, num_of_groups, num_of_players, total_players);
			goback = false;
		}
		else if (main_menu_choice == 'B' || main_menu_choice == 'b') {
			game_tutorial();
		}
		else {

			goback = false;
		}
	}
	cout << "Thanks for playing!\n";
	return 0;
}

void welcome_interface() {
	int x = 0;	//Horizontal axis
	int y = 5;	//Vertical axis
	//Control the y axis
	for (int i = 0; i < y; i++) {
		cout << endl;
	}
	//Quizzy
	for (int i = 0; i < 2; i++) {
		cout << setw(15 + x) << "@@@@@@@@" << endl;
	}
	for (int i = 0; i < 6; i++) {
		cout << setw(7 + x) << "@@" << setw(10) << "@@" << endl;
	}
	cout << setw(7 + x) << "@@" << setw(10) << "@@" << setw(6) << "@@@" << setw(5) << "@@@" << setw(5) << "@@@" << setw(8) << "@@@@@@" << setw(8) << "@@@@@@" << setw(5) << "@@@" << setw(6) << "@@@" << endl;
	cout << setw(7 + x) << "@@" << setw(10) << "@@" << setw(5) << "@" << setw(5) << "@" << setw(5) << "@" << setw(4) << "@" << setw(5) << "@" << setw(3) << "@" << setw(5) << "@" << setw(4) << "@" << setw(6) << "@" << endl;
	cout << setw(7 + x) << "@@" << setw(10) << "@@" << setw(5) << "@" << setw(5) << "@" << setw(5) << "@" << setw(8) << "@" << setw(8) << "@" << setw(6) << "@" << setw(4) << "@" << endl;
	cout << setw(7 + x) << "@@" << setw(10) << "@@" << setw(5) << "@" << setw(5) << "@" << setw(5) << "@" << setw(7) << "@" << setw(8) << "@" << setw(8) << "@" << setw(2) << "@" << endl;
	cout << setw(7 + x) << "@@" << setw(8) << "@@" << setw(7) << "@" << setw(5) << "@" << setw(5) << "@" << setw(6) << "@" << setw(8) << "@" << setw(10) << "@" << setw(41) << "@@@@@@" << endl;
	cout << setw(7 + x) << "@@" << setw(8) << "@@" << setw(7) << "@" << setw(5) << "@" << setw(5) << "@" << setw(5) << "@" << setw(8) << "@" << setw(11) << "@" << setw(41) << "@@@@@@" << endl;
	cout << setw(13 + x) << "@@@@@@" << setw(6) << "@@@@" << setw(3) << "@" << setw(5) << "@" << setw(5) << "@" << setw(4) << "@" << setw(5) << "@" << setw(3) << "@" << setw(5) << "@" << setw(7) << "@" << setw(35) << "@@" << setw(8) << "@@" << endl;
	cout << setw(13 + x) << "@@@@@@" << setw(6) << "@@@@" << setw(7) << "@@@@" << setw(7) << "@@@" << setw(8) << "@@@@@@" << setw(8) << "@@@@@@" << setw(8) << "@@@" << setw(34) << "@@" << setw(8) << "@@" << endl;
	//Empty lines between Quizzy and Peazy
	for (int i = 0; i < 2; i++) {
		cout << setw(99 + x) << "@@" << endl;
	}
	//Peazy
	for (int i = 0; i < 2; i++) {
		cout << setw(47 + x) << "@@@@@@@@@@" << setw(50) << "@@" << endl;
	}
	for (int i = 0; i < 2; i++) {
		cout << setw(41 + x) << "@@" << setw(8) << "@@" << setw(46) << "@@" << endl;
	}
	for (int i = 0; i < 2; i++) {
		cout << setw(41 + x) << "@@" << setw(8) << "@@" << endl;
	}
	for (int i = 0; i < 2; i++) {
		cout << setw(41 + x) << "@@" << setw(8) << "@@" << setw(46) << "@@" << endl;
	}
	cout << setw(47 + x) << "@@@@@@@@" << setw(9) << "@@@@@@" << setw(7) << "@@" << setw(11) << "@@@@@@" << setw(5) << "@@@" << setw(6) << "@@@" << endl;
	cout << setw(47 + x) << "@@@@@@@@" << setw(5) << "@" << setw(4) << "@" << setw(5) << "@" << setw(3) << "@" << setw(5) << "@" << setw(5) << "@" << setw(4) << "@" << setw(6) << "@" << endl;
	cout << setw(41 + x) << "@@" << setw(11) << "@" << setw(8) << "@" << setw(5) << "@" << setw(8) << "@" << setw(6) << "@" << setw(4) << "@" << endl;
	cout << setw(41 + x) << "@@" << setw(14) << "@@@@" << setw(5) << "@" << setw(5) << "@" << setw(7) << "@" << setw(8) << "@" << setw(2) << "@" << endl;
	cout << setw(41 + x) << "@@" << setw(11) << "@" << setw(13) << "@@@@@@" << setw(6) << "@" << setw(10) << "@" << endl;
	cout << setw(41 + x) << "@@" << setw(11) << "@" << setw(8) << "@" << setw(5) << "@" << setw(5) << "@" << setw(11) << "@" << endl;
	cout << setw(42 + x) << "@@@@" << setw(10) << "@" << setw(4) << "@" << setw(4) << "@" << setw(5) << "@" << setw(4) << "@" << setw(5) << "@" << setw(7) << "@" << endl;
	cout << setw(42 + x) << "@@@@" << setw(14) << "@@@@@@" << setw(5) << "@@@" << setw(5) << "@@@" << setw(8) << "@@@@@@" << setw(8) << "@@@" << endl;
	cout << endl << endl << setw(80 + x) << "~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ WELCOME ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~" << endl;
}

//Import data from txt file and store into linked list, calculates the total number of questions
void importFile(QuestionsQueue& fullSet, ifstream& file, string f, int& counter) {
	file.open(f);
	if (!file) {
		cout << "cannot open file\n";
		return;
	}
	//Temporary variables to get data from txt file
	string ques, a1, a2, a3, a4;
	char ans;
	int num;
	//Insert data from txt file into linked list
	while (file >> num) {
		getline(file, ques, ';');
		getline(file, a1, ';');
		getline(file, a2, ';');
		getline(file, a3, ';');
		getline(file, a4, ';');
		file >> ans;
		//For checking
	/*	cout << num << " " << a1 << " " << a2 << " " << a3 << " " << a4 << " " << ans << " " << endl;*/
		fullSet.enqueue(num, ques, a1, a2, a3, a4, ans);
		counter++;
	}
	file.close();
	return;
}

void game_tutorial() {
	system("cls");
	cout << "----------- How to Play? -----------\n"
		<< "Step 1:\nEnter the number of Groups and number of Players in each group:\n"
		<< "Number of Groups:\t\t2\n"
		<< "Number of Players per Group:\t5\n\n"
		<< "NEXT->\t";
	system("pause");
	system("cls");

	cout << "Step 2:\nThe game starts! The first player from Group 1 will get to answer first:\n"
		<< "-------------------------------------------------------------------------------------------\n"
		<< "| " << "1) Who invented the light bulb?" << endl
		<< "| " << "A. Francis Light" << endl
		<< "| " << "B. Elon Musk" << endl
		<< "| " << "C. Nikola Tesla" << endl
		<< "| " << "D. Thomas Edison" << endl
		<< "-------------------------------------------------------------------------------------------\n"
		<< "Daryl's turn\t\t\t\t\tScore: 0/100\n"
		<< "Answer(a/b/c/d): \n\n"
		<< "NEXT->\t";
	system("pause");
	system("cls");

	cout << "Step 3:\nThe first player from Group 2 will get to answer next:\n"
		<< "-------------------------------------------------------------------------------------------\n"
		<< "| " << "1) Who invented the light bulb?" << endl
		<< "| " << "A. Francis Light" << endl
		<< "| " << "B. Elon Musk" << endl
		<< "| " << "C. Nikola Tesla" << endl
		<< "| " << "D. Thomas Edison" << endl
		<< "-------------------------------------------------------------------------------------------\n"
		<< "Kavee's turn\t\t\t\t\tScore: 0/100\n"
		<< "Answer(a/b/c/d): \n\n";
	system("pause");
	cout << "Each member from each Group will answer the questions consequently:\n"
		<< "Group 1\tPlayer 1\n"
		<< "Group 2\tPlayer 1\n"
		<< "Group 1\tPlayer 2\n"
		<< "Group 2\tPlayer 2\n"
		<< " . \n"
		<< " . \n"
		<< " . \n\n"
		<< "NEXT->\t";
	system("pause");
	system("cls");

	cout << "Step 4:\nIf the player answers correctly, he/she will gain 2 marks:\n"
		<< "-------------------------------------------------------------------------------------------\n"
		<< "| " << "1) Who invented the light bulb?" << endl
		<< "| " << "A. Francis Light" << endl
		<< "| " << "B. Elon Musk" << endl
		<< "| " << "C. Nikola Tesla" << endl
		<< "| " << "D. Thomas Edison" << endl
		<< "-------------------------------------------------------------------------------------------\n"
		<< "Daryl's turn\t\t\t\t\tScore: 2/100\n"
		<< "Answer(a/b/c/d): D\n"
		<< "Your answer is correct!\n\n";
	cout << "If the player answers wrongly, he/she will lose 1 mark:\n"
		<< "-------------------------------------------------------------------------------------------\n"
		<< "| " << "1) Who invented the light bulb?" << endl
		<< "| " << "A. Francis Light" << endl
		<< "| " << "B. Elon Musk" << endl
		<< "| " << "C. Nikola Tesla" << endl
		<< "| " << "D. Thomas Edison" << endl
		<< "-------------------------------------------------------------------------------------------\n"
		<< "Daryl's turn\t\t\t\t\tScore: -1/100\n"
		<< "Answer(a/b/c/d): B\n"
		<< "Your answer is wrong!\nThe correct answer is 'd'\n\n"
		<< "Yes! It is possible to get negative marks, so answer the questions carefully!\n\n"
		<< "NEXT->\t";
	system("pause");
	system("cls");

	cout << "Step 5:\nAll players will be ranked from highest score to lowest score:\n"
		<< "------------------Ranking------------------\n"
		<< "Name\t\tGroup\t\tScore\n"
		<< "-------------------------------------------\n"
		<< "Kavee\t\t2\t\t80\n"
		<< "Daryl\t\t1\t\t70\n"
		<< "Afiq\t\t1\t\t65\n"
		<< "Hui Wen\t\t2\t\t64\n"
		<< "-------------------------------------------\n"
		<< "Players will also be ranked in their respective groups from highest score to lowest score:\n"
		//Example of ranking
		<< "~ ~ ~ ~ ~ ~ ~ ~ Group Results ~ ~ ~ ~ ~ ~ ~ ~\n"
		<< "Group 1 ------------------------------------\n"
		<< "Name\t\tGroup\t\tScore\n"
		<< "Daryl\t\t1\t\t70\n"
		<< "Afiq\t\t1\t\t65\n"
		<< "-------------------------------------------\n"
		<< "Total Scores:\t\t\t135\n\n"
		<< "NEXT->\t";
	system("pause");
	system("cls");

	cout << "Step 6:\nThe player with the highest score wins the <MVP Award>:\n"
		<< "\n<MVP Award> Winner:\t\tKavee\n\n"
		<< "The group with the highest score wins the <Best Team Award>:\n"
		<< "\n<Best Team Award> Winner:\tGroup 1\n\n"
		<< "BACK TO MAIN MENU->\t";
	system("pause");
	system("cls");
	return;
}

//Validate numeric data
void validation(int& num, int lowLim) {
	while (num < lowLim) {
		cout << "Please enter a value greater than " << lowLim << ": ";
		cin >> num;
	}
	return;
}

//Validate character data
void validate_char(char& input, char a, char b, char c, char d) {
	while (!(input == a || input == b || input == c || input == d)) {
		cout << "Please enter (" << a << "/" << b << "/" << c << "/" << d << ")  only: ";
		cin >> input;
	}
}

//Validate character data with different number of characters
void validate_char2(char& input, char a, char b, char c, char d, char e, char f) {
	while (!(input == a || input == b || input == c || input == d || input == e || input == f)) {
		cout << "Please enter (" << a << "/" << b << "/" << c << ")  only: ";
		cin >> input;
	}
}

void showRanking(Participant Groups[], Participant& Ranking, int num_of_groups, int num_of_players, int total_players) {
	int scores, team, totalScores, bestTeam;
	string mvp;
	//Display ranking of all players and MVP Award Winner
	cout << "------------------Ranking------------------\n"
		<< "Name\t\tGroup\t\tScore\n"
		<< "-------------------------------------------\n";
	Ranking.displayList();
	cout << "-------------------------------------------\n";
	//Dummy variables
	int a, b;
	Ranking.returnNode(mvp, a, b, 0);
	cout << "<MVP Award> Winner:\t\t" << mvp << endl << endl;

	Groups[0].calcTotalScore(scores, team);
	totalScores = scores; bestTeam = team;
	//Display ranking of players in respective group and Best Team Award Winner
	cout << "~ ~ ~ ~ ~ ~ ~ ~ Group Results ~ ~ ~ ~ ~ ~ ~ ~\n";
	for (int i = 0, team = i; i < num_of_groups; i++) {
		cout << "Group " << i + 1 << " ------------------------------------\n"
			<< "Name\t\tGroup\t\tScore\n";
		cout << "-------------------------------------------\n";
		Groups[i].displayList();
		Groups[i].calcTotalScore(scores, team);
		cout << "-------------------------------------------\n";
		cout << "Total Scores:\t\t\t" << scores << endl;
		cout << "-------------------------------------------\n\n\n";
		if (scores > totalScores) {
			totalScores = scores; bestTeam = team;
		}
	}
	cout << "<Best Team Award> Winner:\tGroup " << bestTeam << endl;
	system("pause");
	return;
}