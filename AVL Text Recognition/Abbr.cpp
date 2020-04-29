/*
 * Abbr.cpp
 *
 *  Created on: Apr 19, 2020
 *      Author: 13027
 */

#include "Abbr.hpp"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
using namespace std;

Abbr::Abbr(string name) {
	fn = name;
	readFile();
}
string Abbr::strip(string s) {
	const char* WhiteSpace = " \t\v\r\n";
	size_t start = s.find_first_not_of(WhiteSpace);
	size_t end = s.find_last_not_of(WhiteSpace);
	return start == end ? string() : s.substr(start, end - start + 1);

}

void Abbr::Interface() {
	char c = 'a';
	while (c != 'q') {
		cout <<endl<<"****************************************************"<<endl;
		cout <<"Choose Option:\n  a\tGet phrase\n  b\tadd a phrase\n  c\tdelete a phrase\n  d\tprint tree\n  q\tquit"<< endl;
		cin >> c;
		switch (c) {
		case 'a': {
			cout << "Enter Abbreviation: "<<endl;
			string s;
			cin >> s;
			TNode *t = tree->find(s);
			if (t == NULL) {
				char k;
				cout << s <<" not found in database.  Do you wish to enter it? (y or n)" << endl;
				cin >> k;
				if (k ==  'y') {
					string phr;
					cout << "Enter Phrase: "<<endl;
					cin.ignore();
					getline(cin, phr);
					tree->insert(s,phr);
					cout << endl <<s << "\t" << phr << " inserted successfully "<<endl;
				}
			}
			else {
				cout <<s << ", "<< t->data->longphrase << endl;
			}
			break;
		}
		case 'b':{
			string phr;
			cout << "Enter Phrase: "<<endl;
			cin.ignore();
			getline(cin, phr);
			cout << endl << "Enter Abbrev: ";
			string abbr;
			cin >> abbr;
			if (tree->insert(abbr,phr)) {
				cout << endl <<abbr << "\t" << phr << " inserted successfully "<<endl;
			}
			else {
				TNode *t = tree->find(abbr);
				cout << endl <<abbr << " already in tree with " << t->data->longphrase << endl;
			}
			break;
		}
		case 'c': {
			cout << "Enter Abbrev to be deleted:\t";
			string s;
			cin >> s;
			TNode *t = tree->remove(s);
			if (t == NULL) {
				cout << endl << s << " not in tree " << endl;
			}
			else {
				cout << endl<< s<<","<<t->data->longphrase<< " has been removed. "<<endl;
			}
			break;
		}
		case 'd': {
			cout << "Choose a for pre, b for in, or c for post-order\t";
			char k;
			cin >> k;
			cout << endl;
			cout << "************************************************"<<endl;
			if (k == 'a') {
			cout << "*********** Printing Tree Pre Order ************"<<endl;
			cout << "************************************************"<<endl;
			tree->printTreePre();
			}
			else if (k == 'b') {
			cout << "*********** Printing Tree In Order *************"<<endl;
			cout << "************************************************"<<endl;
			tree->printTreeIO();
			}
			if (k == 'c') {
			cout << "*********** Printing Tree Post Order ***********"<<endl;
			cout << "************************************************"<<endl;
			tree->printTreePost();
			}

			break;
		}
		}
	}
}
void Abbr::readFile() {
	tree = new BST();
	ifstream file(fn.c_str());
	string word;
	string phrase;
	while (!file.eof()) {
		file >> word;
		getline(file,phrase);
		phrase = strip(phrase);
		if (!file.eof()) {
			cout << word << ", "<<phrase<<endl;
			tree->insert(word,phrase);
		}
	}
	tree->printTreeIO();
	return;
}

//	BST *tree;
//	string fn;
//public:
//	Abbr(string filename);

//	AddPhrases();
//	DeletePhrases();
//	PrintPhrases();
//};





