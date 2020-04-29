


#include "BST.hpp"


BST::BST() {
	root = NULL;
}

BST::BST(string s, string l) {
	root = new TNode(s,l);
}

void BST::printTreeIO() {
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl<<"Printing In Order:" <<endl;
		printTreeIO(root);
	}
}


void BST::printTreePre() {
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl<<"Printing PreOrder:" <<endl;
		printTreePre(root);
	}
}


void BST::printTreePost() {
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl<<"Printing PostOrder:" <<endl;
		printTreePost(root);
	}
}


void BST::clearTree() {
	if (root == NULL) {
		cout << "Tree already empty" << endl;
	}
	else {
		cout << endl << "Clearing Tree:" << endl;
		clearTree(root);
		root = NULL;
	}
}

void BST::clearTree(TNode *tmp) {
	if (tmp == NULL) {
		return;
	}
	else {
		clearTree(tmp->left);
		clearTree(tmp->right);
		tmp->printNode();
		delete(tmp);
	}
}


//Required Functions:

//This function takes in a string as the node data, and returns a boolean value true if the node is inserted into the BST and false if it is not.
//This method was done iterativley by traversing the tree and inserting the node in the appropriate spot.

bool BST::insert(string s, string l){

	TNode *temp = new TNode(s,l);


	if(root == NULL){
		root = temp;
		setHeight(temp);
		return true;
	}

	TNode *tempRoot = root;
	TNode *tempParent = NULL;

	while(tempRoot != NULL){
		tempParent = tempRoot;
		if(tempRoot->data->phrase < s){
			tempRoot = tempRoot->right;
		}

		else if(tempRoot->data->phrase > s){
			tempRoot = tempRoot->left;
		}

		else{
			return false;
		}
	}

	if(tempParent->data->phrase < s){
		tempParent->right = temp;
		temp->parent = tempParent;
		setHeight(temp);

		return true;
	}

	else{
		tempParent->left = temp;
		temp->parent = tempParent;
		setHeight(temp);

		return true;
	}


	return false;
}



//This function returns a node from the binary tree and takes in a string that will be the data of the node we are trying to find within the tree. This is a relatively simple function. We are
//traversing the tree until we find the data that is being held by the node. If the data/node is not in the tree, we return null.
TNode* BST::find(string s){

	TNode* current = root;
	while(current->data->phrase!=s){

		if(current!=NULL){
			if(current->data->phrase>s){
				current = current->left;
			}

			else{
				current = current->right;
			}

			if(current == NULL){
				return NULL;

			}

		}

	}


	return current;



}

//This function returns nothing and takes in a node from our BST. This function recursively traverses and prints out the data of the tree in order.
void BST::printTreeIO(TNode *n){
	if(n == NULL){
		return;
	}

	else{
		printTreeIO(n->left);
		cout<<n->data->phrase<<", "<<n->data->longphrase<<" "<<n->height<<endl;
		printTreeIO(n->right);
	}
}

//This function returns nothing and takes in a node from our BST. This function recursively traverses and prints out the data of the tree in preorder.
void BST::printTreePre(TNode *n){
	if(n == NULL){
		return;
	}

	else{
		cout<<n->data->phrase<<", "<<n->data->longphrase<<" "<<n->height<<endl;
		printTreePre(n->left);
		printTreePre(n->right);
	}
}

//This function returns nothing and takes in a node from our BST. This function recursively traverses and prints out the data of the tree in postorder.
void BST::printTreePost(TNode *n){
	if(n == NULL){
		return;
	}

	else{
		printTreePost(n->left);
		printTreePost(n->right);
		cout<<n->data->phrase<<", "<<n->data->longphrase<<" "<<n->height<<endl;
	}
}


//COMMENTS FOR THE CODE CAN BE FOUND BELOW  ---- This function returns a node from our BST and takes in a string as the data of the node which we are deleting.
TNode* BST::remove(string s){

	//using the find function to find the node which we want to delete.
	TNode *temp = find(s);

	//These statements check to see if we are removing a node with one kid or no kids. If a node has no kids, the removeNoKids function is called. If not, the removeOneKid function is called
	//depending on which side the child is on.
	if(temp->right == NULL && temp->left == NULL){
		removeNoKids(temp);
	}

	else if(temp->right == NULL && temp->left != NULL){
		removeOneKid(temp, true);
	}

	else if(temp->right != NULL && temp->left == NULL){
		return removeOneKid(temp, false);
	}


//*****************************************************************************************************************************

	//If the node being deleted is not the root we proceed below.
	else if(temp!=root){


		TNode *returnNode = temp;
		TNode *newParent = temp->parent;

		//If the parent to the node we are deleting is the left parent, we proceed with finding the rightmost of the deleted nodes left child.

		if(newParent->left == temp){
			TNode *rightChain = temp->right;
			TNode *leftChild = temp->left;

			while(leftChild->right != NULL){
				leftChild = leftChild->right;
			}

			//INSTEAD OF CALLING REMOVEONEKID OR REMOVENOKIDS I rearranged the pointers. This allowed me to make my code a bit more simple and get the desire output below.
			TNode *tempChild = leftChild;
			temp->parent = NULL;
			newParent->left = tempChild;
			tempChild->parent = newParent;
			tempChild->right = rightChain;

			//Here we are traversing the bottom of the tree and reseting the heights of the tree nodes.
			TNode *findleaf = tempChild->left;
			while(findleaf->right != NULL || findleaf->left != NULL){
				if(findleaf->left == NULL){
					findleaf = findleaf->right;
				}

				else if(findleaf->right == NULL){
					findleaf = findleaf->left;
				}

			}

			setHeight(findleaf);

			return returnNode;
		}


//**********************************************************************************************************************************************************************************************

		else if(newParent->right == temp){


			//If the parent to the node we are deleting is the right parent, we proceed with finding the rightmost of the deleted nodes left child.
			TNode *leftChild = temp->left;
			TNode *rightChain = temp->right;


			while(leftChild->right != NULL){
				leftChild = leftChild->right;
			}


			//INSTEAD OF CALLING REMOVEONEKID OR REMOVENOKIDS I rearranged the pointers. This allowed me to make my code a bit more simple and get the desire output below.
			TNode *tempChild = leftChild;
			temp->parent = NULL;
			newParent->right = tempChild;
			tempChild->parent = newParent;
			tempChild->right = rightChain;


			//Here we are traversing the bottom of the tree and reseting the heights of the tree nodes.
			TNode *findleaf = tempChild->left;
			while(findleaf->right != NULL || findleaf->left != NULL){
				if(findleaf->left == NULL){
					findleaf = findleaf->right;
				}

				else if(findleaf->right == NULL){
					findleaf = findleaf->left;
				}

			}

			setHeight(findleaf);

			return returnNode;
		}

	}
//********************************************************************************************************************************************************************************

    else{

    	//If the node = root
    	TNode *returnNode = temp;


		TNode *leftChild = temp->left;
		TNode *rightChain = temp->right;



		//Here we go left and find the rightmost child of the root.
		while(leftChild->right != NULL){
			leftChild = leftChild->right;
		}

		//Rearranging the pointers instead of calling remove functions.
		TNode *tempChild = leftChild;
		temp->parent = NULL;
		root = tempChild;
		tempChild->right = rightChain;


		//Manually setting the root height before setting all the heights after (See below)
		if(root->right != NULL && root->left != NULL){
			if(root->right->height > root->left->height){
				root->height = root->right->height +1;
			}

			else{
				root->height = root->left->height +1;
			}

		}

		else if(root->right == NULL){
			root->height = root->left->height +1;
		}

		else if(root->left == NULL){
			root->height = root->right->height +1;
		}


		//Traversing to reset the heights.
		TNode *findleaf = tempChild;


		while(findleaf->right != NULL || findleaf->left != NULL){

				if(findleaf->left == NULL){
					findleaf = findleaf->right;
				}

				else if(findleaf->right == NULL){
					findleaf = findleaf->left;
				}

				else if(findleaf->right != NULL && findleaf->left != NULL){
					findleaf = findleaf->right;
					}


			}
			setHeight(findleaf);



			return returnNode;
	}


}



//This function returns a node from our BST and takes in a node from our BST. We are simply removing a node from the tree with no kids and setting the parent of the removed node's left or right to null.
TNode* BST::removeNoKids(TNode *tmp){

	tmp->data->phrase = "STILL HERE";

	TNode *tempParent = tmp->parent;

	TNode *returnedNode = tmp;


	if(tmp == tempParent->left){
		tempParent->left = NULL;
		tmp->parent = NULL; //CEHCK
		setHeight(tempParent);
	}

	else{
		tempParent->right = NULL;
		tmp->parent = NULL; //CHECK
		setHeight(tempParent);
	}

	return returnedNode;

}


//This function removes one child from the BST. It returns a node from the bst which we are removing and takes in a node from our bst as well as a bool (true if left - false if right).

TNode* BST::removeOneKid(TNode *tmp, bool leftFlag){
	/****set flag,set new parent node****/
	TNode* returnedNode = tmp;
	TNode* newParent = tmp->parent;
	if(tmp->right != NULL){
		leftFlag = false;
	}

	else if(tmp->left != NULL){
		leftFlag = true;
	}

	if(leftFlag){
		if(newParent->left == tmp){
			TNode* newLChild = tmp->left;
			tmp->left = NULL;
			tmp->parent = NULL;
			newParent->left=  newLChild;
			newLChild->parent = newParent;

			TNode *findleaf = newLChild;
			while(findleaf->right != NULL || findleaf->left != NULL){
				if(findleaf->left == NULL){
					findleaf = findleaf->right;
				}

				else if(findleaf->right == NULL){
					findleaf = findleaf->left;
				}

			}

			setHeight(findleaf);

		}

		else if(newParent->right == tmp){
			TNode* newLChild = tmp->left;
			tmp->left = NULL;
			tmp->parent = NULL;
			newParent->right=  newLChild;
			newLChild->parent = newParent;

			TNode *findleaf = newLChild;
			while(findleaf->right != NULL || findleaf->left != NULL){
				if(findleaf->left == NULL){
					findleaf = findleaf->right;
				}

				else if(findleaf->right == NULL){
					findleaf = findleaf->left;
				}

			}

			setHeight(findleaf);

		}

	}

	else{
		if(newParent->left == tmp){
			TNode* newRChild = tmp->right;
			tmp->right = NULL;
			tmp->parent = NULL;
			newParent->left = newRChild;
			newRChild->parent = newParent;

			TNode *findleaf = newRChild;
			while(findleaf->right != NULL || findleaf->left != NULL){
				if(findleaf->left == NULL){
					findleaf = findleaf->right;
				}

				else if(findleaf->right == NULL){
					findleaf = findleaf->left;
				}



			setHeight(findleaf);

		}
		}

		else if(newParent->right == tmp){

			TNode* newRChild = tmp->right;
			tmp->right = NULL;
			tmp->parent = NULL;
			newParent->right = newRChild;
			newRChild->parent = newParent;

			TNode *findleaf = newRChild;
			while(findleaf->right != NULL || findleaf->left != NULL){
				if(findleaf->left == NULL){
					findleaf = findleaf->right;
				}

				else if(findleaf->right == NULL){
					findleaf = findleaf->left;
				}

			}

			setHeight(findleaf);

		}

	}

	return returnedNode;



}

//The set height function returns nothing and takes in a node which was inserted or we are starting at. Then, the we traverse backwards to the root setting the height of each node.
//The set height Function has been updated to account for rotations.
void BST::setHeight(TNode *n){


	if(n == root){
		n->height = 1;
		return;
	}

	else if(n->left == NULL && n->right == NULL){
		n->height =1;
		n = n->parent;


		while(n != NULL){

			if(n->left != NULL && n->right != NULL){


				if(n->left->height > n->right->height){
					n->height = n->left->height + 1;
					if(getBalance(n) == 2 && getBalance(n->left)==1){
						rotateRight(n);
					}
					else if(getBalance(n) == 2 && getBalance(n->left)==1){
						cout<<"Left-Right Rotate"<<endl;
						rotateLeft(n->left);
						//rotateRight(n);
					}

					else if(getBalance(n)==2 && getBalance(n->left) == -1){
						rotateLeft(n->left);
					}

					else if(getBalance(n)==2 && getBalance(n->left) ==2){
						rotateRight(n);
					}


				}

				else if(n->left->height < n->right->height){
					n->height = n->right->height + 1;
					if(getBalance(n)==-2 && getBalance(n->right) == -1){

						rotateLeft(n);
					}

					else if(getBalance(n)==-2 && getBalance(n->right) == 1){
						cout<<"Right-Left Rotate"<<endl;
						cout<<"correct rotate"<<endl;
						rotateRight(n->right);
						//rotateLeft(n);
					}

					else if(getBalance(n)==-2 && getBalance(n->right) == -2){
						rotateLeft(n);
					}





				}

				else{
					n->height = n->left->height +1;


				}
			}

			if(n->left == NULL && n->right != NULL){
				n->height = n->right->height +1;

				if(getBalance(n) == -2 && getBalance(n->right) == -1){

					rotateLeft(n);

				}

				else if(getBalance(n)==-2 && getBalance(n->right) == 1){
					cout<<"Right-Left Rotate"<<endl;
					rotateRight(n->right);
					//rotateLeft(n);
				}




				}



			else if(n->right == NULL && n->left != NULL){
				n->height = n->left->height +1;

				if(getBalance(n)==2 && getBalance(n->left)==1){

					rotateRight(n);
				}

				else if(getBalance(n) == 2 && getBalance(n->left)==1){
					cout<<"Left-Right Rotate"<<endl;
					rotateLeft(n->left);
					//rotateRight(n);
				}

				else if(getBalance(n)==2 && getBalance(n->left)==-1){

					rotateLeft(n->left);
				}


			}

			n = n->parent;

	}
	}

}





//ROTATE FUNCTIONS ************************************************************************************************

//The rotateLeft Function rotates the tree to the left depending on the balance of the nodes. There are a few conditions that are show below.
//Depending on the conditions, the tree will rotate in a specific way.
//This function returns the node that is the new root of the subtree and takes in the node it rotates around as an argument.
TNode *BST::rotateLeft(TNode *tmp){



	//No Right Child
	if(tmp->right == NULL){
		return NULL;
	}

	else{
		TNode *rightChild = tmp->right;
		if(tmp == root){

			if(rightChild->left != NULL){

				cout<<"LR case 1"<<endl;

				TNode *rightLeftChild = rightChild->left;

				rightChild->left = tmp;
				rightChild->parent = NULL;
				root = rightChild;
				tmp->parent = rightChild;
				tmp->right = rightLeftChild;
				rightLeftChild->parent = tmp;

				if(rightChild->left!= NULL){
					TNode *findleaf = rightChild->left;
					while(findleaf->right != NULL || findleaf->left != NULL){

							if(findleaf->left == NULL){
								findleaf = findleaf->right;
							}

							else if(findleaf->right == NULL){
								findleaf = findleaf->left;
							}

							else if(findleaf->right != NULL && findleaf->left != NULL){
								findleaf = findleaf->right;
								}


						}
						setHeight(findleaf);
				}


					if(rightChild->right != NULL){
						TNode *findleaf2 = rightChild->right;
						while(findleaf2->right != NULL || findleaf2->left != NULL){

								if(findleaf2->left == NULL){
									findleaf2 = findleaf2->right;
								}

								else if(findleaf2->right == NULL){
									findleaf2 = findleaf2->left;
								}

								else if(findleaf2->right != NULL && findleaf2->left != NULL){
									findleaf2 = findleaf2->right;
									}


							}
							setHeight(findleaf2);
					}
				return rightChild;
			}





			else if(rightChild->left == NULL){
				cout<<"LR case 2"<<endl;

				rightChild->left = tmp;
				rightChild->parent = NULL;
				root = rightChild;
				tmp->parent = rightChild;
				tmp->right = NULL;

				//set heights for each side of the tree.

				if(rightChild->left!= NULL){
					TNode *findleaf = rightChild->left;
					while(findleaf->right != NULL || findleaf->left != NULL){

							if(findleaf->left == NULL){
								findleaf = findleaf->right;
							}

							else if(findleaf->right == NULL){
								findleaf = findleaf->left;
							}

							else if(findleaf->right != NULL && findleaf->left != NULL){
								findleaf = findleaf->right;
								}


						}
						setHeight(findleaf);
				}

					if(rightChild->right != NULL){
						TNode *findleaf2 = rightChild->right;
						while(findleaf2->right != NULL || findleaf2->left != NULL){

								if(findleaf2->left == NULL){
									findleaf2 = findleaf2->right;
								}

								else if(findleaf2->right == NULL){
									findleaf2 = findleaf2->left;
								}

								else if(findleaf2->right != NULL && findleaf2->left != NULL){
									findleaf2 = findleaf2->right;
									}


							}
							setHeight(findleaf2);
					}

				return rightChild;
			}
		}





		else{//tmp is not the root

			if(rightChild->left != NULL){
				cout<<"LR case 3"<<endl;
				TNode *new_right = rightChild->left; //

				if(tmp->parent->right == tmp){
					rightChild->left = tmp;
					rightChild->parent = tmp->parent;
					tmp->parent->right = rightChild;
					tmp->parent = rightChild;
					tmp->right = new_right;
					new_right->parent = tmp;
				}

				else if(tmp->parent->left == tmp){
					rightChild->left = tmp;
					rightChild->parent = tmp->parent;
					tmp->parent->left = rightChild;
					tmp->parent = rightChild;
					tmp->right = new_right;
					new_right->parent = tmp;
				}

				if(rightChild->left != NULL){
					TNode *findleaf = rightChild->left;
					while(findleaf->right != NULL || findleaf->left != NULL){

							if(findleaf->left == NULL){
								findleaf = findleaf->right;
							}

							else if(findleaf->right == NULL){
								findleaf = findleaf->left;
							}

							else if(findleaf->right != NULL && findleaf->left != NULL){
								findleaf = findleaf->right;
								}


						}

						setHeight(findleaf);
				}

					if(rightChild->right != NULL){
						TNode *findleaf2 = rightChild->right;

						while(findleaf2->right != NULL || findleaf2->left != NULL){

								if(findleaf2->left == NULL){
									findleaf2 = findleaf2->right;
								}

								else if(findleaf2->right == NULL){
									findleaf2 = findleaf2->left;
								}

								else if(findleaf2->right != NULL && findleaf2->left != NULL){
									findleaf2 = findleaf2->right;
									}


							}

							setHeight(findleaf2);
					}


				return rightChild;
			}









			else if(rightChild->left == NULL){
				cout<<"LR case 4"<<endl;

				if(tmp->parent->right == tmp){
				rightChild->parent = tmp->parent;
				tmp->parent->right = rightChild;
				tmp->right = NULL;
				tmp->parent = NULL;
				rightChild->left = tmp;
				tmp->parent = rightChild;
				}

				else if(tmp->parent->left == tmp){
					rightChild->parent = tmp->parent;
					tmp->parent->left = rightChild;
					tmp->right = NULL;
					tmp->parent = NULL;
					rightChild->left = tmp;
					tmp->parent = rightChild;
				}


				if(rightChild->left != NULL){
					TNode *findleaf = rightChild->left;
					while(findleaf->right != NULL || findleaf->left != NULL){

							if(findleaf->left == NULL){
								findleaf = findleaf->right;
							}

							else if(findleaf->right == NULL){
								findleaf = findleaf->left;
							}

							else if(findleaf->right != NULL && findleaf->left != NULL){
								findleaf = findleaf->right;
								}


						}


						setHeight(findleaf);
				}

				if(rightChild->right != NULL){
						TNode *findleaf2 = rightChild->right;
						while(findleaf2->right != NULL || findleaf2->left != NULL){

								if(findleaf2->left == NULL){
									findleaf2 = findleaf2->right;
								}

								else if(findleaf2->right == NULL){
									findleaf2 = findleaf2->left;
								}

								else if(findleaf2->right != NULL && findleaf2->left != NULL){
									findleaf2 = findleaf2->right;
									}


							}

							setHeight(findleaf2);
				}

				return rightChild;
			}


		}




	}
}




//The rotateRight Function rotates the tree to the right depending on the balance of the nodes. There are a few conditions that are show below.
//Depending on the conditions, the tree will rotate in a specific way.
//This function returns the node that is the new root of the subtree  and takes in the node it rotates around as an argument.

TNode *BST::rotateRight(TNode *tmp){



	if(tmp->left == NULL){
		return NULL; //no left child
	}

	else{
		TNode *leftChild = tmp -> left;

		if(tmp == root){


			if(leftChild->right != NULL){
				cout<<"RR case 1"<<endl;

				TNode* leftRightChild = leftChild->right;

				leftChild -> right = tmp;
				leftChild -> parent = NULL;

				root = leftChild;
				tmp->parent = leftChild;
				tmp -> left = leftRightChild;
				leftRightChild->parent = tmp;



				if(leftChild->right!=NULL){
				TNode *findleaf = leftChild->right;
					while(findleaf->right != NULL || findleaf->left != NULL){

							if(findleaf->left == NULL){
								findleaf = findleaf->right;
							}

							else if(findleaf->right == NULL){
								findleaf = findleaf->left;
							}

							else if(findleaf->right != NULL && findleaf->left != NULL){
								findleaf = findleaf->right;
								}


						}
						setHeight(findleaf);
				}

				if(leftChild->left != NULL){
							TNode *findleaf2 = leftChild->left;
							while(findleaf2->right != NULL || findleaf2->left != NULL){

									if(findleaf2->left == NULL){
										findleaf2 = findleaf2->right;
									}

									else if(findleaf2->right == NULL){
										findleaf2 = findleaf2->left;
									}

									else if(findleaf2->right != NULL && findleaf2->left != NULL){
										findleaf2 = findleaf2->right;
										}



								setHeight(findleaf2);
					}
					}
				return leftChild;

		}





			else if(leftChild->right == NULL){
				cout<<"RR case 2"<<endl;

				leftChild->right = tmp;

				leftChild -> parent = NULL;

				root = leftChild;

				tmp->parent = leftChild;

				tmp->left = NULL;


				if(leftChild->right != NULL){
					TNode *findleaf = leftChild->right;

					while(findleaf->right != NULL || findleaf->left != NULL){

							if(findleaf->left == NULL){
								findleaf = findleaf->right;
							}


							else if(findleaf->right == NULL){
								findleaf = findleaf->left;
							}

							else if(findleaf->right != NULL && findleaf->left != NULL){
								findleaf = findleaf->right;
								}


						}



						setHeight(findleaf);
				}


				if(leftChild->left!= NULL){
					TNode *findleaf2 = leftChild->left;
					while(findleaf2->right != NULL || findleaf2->left != NULL){

							if(findleaf2->left == NULL){
								findleaf2 = findleaf2->right;
							}

							else if(findleaf2->right == NULL){
								findleaf2 = findleaf2->left;
							}

							else if(findleaf2->right != NULL && findleaf2->left != NULL){
								findleaf2 = findleaf2->right;
								}


						}
						setHeight(findleaf2);
				}



				return leftChild;
			}

	}




		else{

			if(leftChild->right != NULL){
				cout<<"RR case 3"<<endl;
				TNode* newLeft = leftChild->right;

				if(tmp->parent->left == tmp){
					leftChild->right = tmp;
					leftChild->parent = tmp->parent;
					tmp->parent->left = leftChild;
					tmp -> parent = leftChild;
					tmp -> left = newLeft;
					newLeft->parent = tmp;
				}

				else if(tmp->parent->right == tmp){
					leftChild->right = tmp;
					leftChild->parent = tmp->parent;
					tmp->parent->right = leftChild;
					tmp -> parent = leftChild;
					tmp -> left = newLeft;
					newLeft->parent = tmp;
				}



				if(leftChild->right != NULL){
					TNode *findleaf = leftChild->right;
					while(findleaf->right != NULL || findleaf->left != NULL){

							if(findleaf->left == NULL){
								findleaf = findleaf->right;
							}

							else if(findleaf->right == NULL){
								findleaf = findleaf->left;
							}

							else if(findleaf->right != NULL && findleaf->left != NULL){
								findleaf = findleaf->right;
								}


						}


						setHeight(findleaf);
				}

				if(leftChild->left!= NULL){
					TNode *findleaf2 = leftChild->left;

					while(findleaf2->right != NULL || findleaf2->left != NULL){

							if(findleaf2->left == NULL){
								findleaf2 = findleaf2->right;
							}

							else if(findleaf2->right == NULL){
								findleaf2 = findleaf2->left;
							}

							else if(findleaf2->right != NULL && findleaf2->left != NULL){
								findleaf2 = findleaf2->right;
								}


						}

						setHeight(findleaf2);

				}

				return leftChild;
			}





			else if(leftChild->right == NULL){
				cout<<"RR case 4"<<endl;
				if(tmp->parent->left == tmp){

				leftChild->parent = tmp->parent;
				tmp->parent->left = leftChild;

				tmp->left = NULL;
				tmp->parent = NULL;

				leftChild->right = tmp;
				tmp->parent = leftChild;
				}

				else if(tmp->parent->right == tmp){
					leftChild->parent = tmp->parent;
					tmp->parent->right = leftChild;

					tmp->left = NULL;
					tmp->parent = NULL;

					leftChild->right = tmp;
					tmp->parent = leftChild;
				}


				if(leftChild->right != NULL){
					TNode *findleaf = leftChild->right;
					while(findleaf->right != NULL || findleaf->left != NULL){

							if(findleaf->left == NULL){
								findleaf = findleaf->right;
							}

							else if(findleaf->right == NULL){
								findleaf = findleaf->left;
							}

							else if(findleaf->right != NULL && findleaf->left != NULL){
								findleaf = findleaf->right;
								}


						}
						setHeight(findleaf);
				}

					if(leftChild->left!= NULL){
						TNode *findleaf2 = leftChild->left;
						while(findleaf2->right != NULL || findleaf2->left != NULL){

								if(findleaf2->left == NULL){
									findleaf2 = findleaf2->right;
								}

								else if(findleaf2->right == NULL){
									findleaf2 = findleaf2->left;
								}

								else if(findleaf2->right != NULL && findleaf2->left != NULL){
									findleaf2 = findleaf2->right;
									}


							}
							setHeight(findleaf2);
					}


				return leftChild;
			}
		}
}
}










//The get balance function returns the balance of a node. The balance (integer) is returned and the node that the balance is being calculated
//for is used as the function argument.
int BST::getBalance(TNode *tmp){

	if(tmp->right && tmp->left != NULL){
		return tmp->left->height - tmp->right->height;
	}

	else if(tmp->right != NULL and tmp->left == NULL){
		return tmp->right->height * -1;

	}

	else{
		return tmp->left->height;
	}
}










