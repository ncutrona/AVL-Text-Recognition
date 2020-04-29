/*
 * MainPhrase.cpp
 *
 *  Created on: Apr 19, 2020
 *      Author: 13027
 */

#include <iostream>
#include "Abbr.hpp"
using namespace std;

int main() {
	//Abbr *abbr = new Abbr("PhrasesAndAbbr.txt");
	Abbr *abbr = new Abbr("Testleft.txt");
	cout << "************************************" << endl;
	abbr->tree->clearTree();

	delete abbr;
	cout << "********* Testing right ************" << endl;
	abbr = new Abbr("Testright.txt");
	cout << "************************************" << endl;
	abbr->tree->clearTree();

	delete abbr;
	cout << "********* Testing rightleft ********" << endl;
	abbr = new Abbr("TestRightLeft.txt");
	cout << "************************************" << endl;
	abbr->tree->clearTree();

	delete abbr;
	cout << "********* Testing leftright ********" << endl;
	abbr = new Abbr("TestLeftRight.txt");
	cout << "************************************" << endl;
	abbr->tree->clearTree();

	delete abbr;
	cout << "********* Testing leftright ********" << endl;
	abbr = new Abbr("PhrasesAndAbbr.txt");
	abbr->Interface();
	return 0;
}







