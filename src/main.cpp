#include <iostream>
#include "AVL.h"
#include <sstream>
#include <cctype>

using namespace std;

//helper methods
bool validUFID(int& id) {
	if (id >= 10000000 && id <= 99999999) {
		return true;
	}
	return false;
}

//helper methods
bool validName(string& name) {
	if (name.empty()) {
		return false;
	}

	//credits to this link for how to identify the word as just letters: https://cplusplus.com/forum/beginner/186225/
	for (std::string::size_type i = 0; i < name.size(); i++)
	{
		char ch = name[i];
		if (ch == ' ') {
			continue;
		}


		int uppercaseChar = toupper(name[i]); //Convert character to upper case version of character
		if (uppercaseChar < 'A' || uppercaseChar > 'Z') //If character is not A-Z
		{
			return false;
		}

	}
	return true;

}

// exactly 8 digits as typed (allows leading zeros)
bool validUFIDToken(const string& s) {
	if (s.size() != 8) return false;
	for (char c : s) if (!isdigit(static_cast<unsigned char>(c))) return false;
	return true;
}


int main(){
	AVL tree;
	string number;
	getline(cin, number);

	istringstream inputStream2(number);

	int number2 = 0;
	//received a hint on how to make this if statement through the edugator AI model.
	if (!(inputStream2 >> number2)) {
		cout << "unsuccessful" << endl;
		return 1;
	}


	//START THE LOOP
	int counter = 0;
	while(counter < number2) {

		//first word from the line - command
		string line;
		if (!getline(cin, line)) { //get the next line
			break;
		}
		istringstream inputStream(line);
		string command;
		inputStream >> command;


		//commands
		if (command == "insert") {
			string skipToQuote;
			getline(inputStream, skipToQuote, '"'); // skip up to first quote

			string name;
			getline(inputStream, name, '"');        // read the quoted name

			string idtok;
			if (!(inputStream >> idtok) || !validUFIDToken(idtok) || !validName(name)) {
				cout << "unsuccessful" << endl;
				continue;
			}
			int id = stoi(idtok);
			tree.insert(name, id);
		}
		else if (command == "remove") {
			string idtok;
			if (!(inputStream >> idtok) || !validUFIDToken(idtok)) {
				cout << "unsuccessful" << endl;
				continue;
			}
			int id = stoi(idtok);
			tree.remove(id);
		}
		else if (command == "search") {
			inputStream >> ws;

			// name search
			if (inputStream.peek() == '"') {
				inputStream.get();
				std::string name;
				if (!std::getline(inputStream, name, '"')) {
					std::cout << "unsuccessful" << std::endl;
					continue;
				}

				if (!validName(name)) {            // validate NAME
					std::cout << "unsuccessful" << std::endl;
					continue;
				}

				tree.search(name);                 // call
			}
			// ID search
			else {
				string idtok;
				if (!(inputStream >> idtok) || !validUFIDToken(idtok)) {
					cout << "unsuccessful" << endl;
					continue;
				}
				int id = stoi(idtok);
				tree.search(id);
			}

		}
		else if (command == "printInorder") {
			tree.inOrder();
		}
		else if (command == "printPreorder") {
			tree.preOrder();
		}
		else if (command == "printPostorder") {
			tree.postOrder();
		}
		else if (command == "printLevelCount") {
			tree.printLevelCount();
		}
		else if (command == "removeInorder") {
			int n = 0;
			if (!(inputStream >> n)) {              // n is not an integer
				std::cout << "unsuccessful" << std::endl;
				continue;
			}
			if (n < 0) {                            // N must be >= 0
				std::cout << "unsuccessful" << std::endl;
				continue;
			}

			tree.removeInorder(n);
		}
		else {
			cout << "unsuccessful" << endl;
		}

		counter++;
	}


	return 0;
}
