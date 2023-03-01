#include<iostream>
#include<ctime>
#include"BST.h"
#include"RBTree.h"
#include"AVLTree.h"

int main()
{
	std::srand(time(NULL));
	RBTree test;
	for (int i = 0; i < 10; i++)
	{
		test.insert(i);
		test.preOrder(true);
		std::cout << std::endl;
	}



	return 0;
}