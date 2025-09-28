#include <iostream>
#include "AVL.h"
#include <sstream>

using namespace std;

bool validUFID(int& id) {

}

bool validName(string& name) {

}

int main(){
	//AVL tree;
	string number;
	getline(cin, number);

	istringstream inputStream(number);

	int number2 = 0;
	//received a hint on how to make this if statement through the edugator AI model.
	if (!(inputStream >> number2)) {
		cout << "unsuccessful" << endl;
		return 1;
	}

	int counter = 0;
	while(counter < number2) {

		//first word from the line - command
		string command;
		inputStream >> command;

		if (command == "insert") {
			string space;
			getline(inputStream, space, '"');

			string name;
			getline(inputStream, name, '"');

			string space2;
			getline(inputStream, space2, ' ');

			string number;
			getline(inputStream, number);

			//check to make sure number is 8 digits
			int id = 0;

			if (!(inputStream >> id)) {
				cout << "unsuccessful" << endl;
				break;
			}







		}
		else if (command == "remove") {

		}
		else if (command == "search") {

		}
		else if (command == "printInorder") {

		}
		else if (command == "printPreorder") {

		}
		else if (command == "printPostorder") {

		}
		else if (command == "printLevelCount") {

		}
		else if (command == "removeInorder") {

		}
		else {
			cout << "unsuccessful" << endl;
		}



		counter++;
	}


	return 0;
}
