/*
 * Phrase.cpp
 *
 *  Created on: Apr 10, 2020
 *      Author: 13027
 */
#include <iostream>
#include <string>
#include "Phrase.hpp"
using namespace std;

Phrase::Phrase(string s, string l) {
	phrase = s;
	longphrase = l;
}

Phrase::Phrase() {
	phrase = "";
	longphrase = "";
}


