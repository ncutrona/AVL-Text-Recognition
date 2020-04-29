/*
 * TNode.hpp
 *
 *  Created on: Apr 3, 2020
 *      Author: 13027
 */

#ifndef TNODE_HPP_
#define TNODE_HPP_
#include <iostream>
#include "Phrase.hpp"
using namespace std;

class TNode{
	friend class BST;
	friend class Abbr;
	TNode *left;
	TNode *right;
	TNode *parent;
	Phrase *data;
	int height;
public:
	TNode(string s, string l);
	TNode();
	~TNode();
	void printNode();
};



#endif /* TNODE_HPP_ */
