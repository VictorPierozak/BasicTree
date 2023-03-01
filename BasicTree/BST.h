#include"BasicTree.h"
#include<iostream>

class BSTNode : public basic_node<BSTNode, int>
{
public:
	BSTNode():
		basic_node()
	{

	}
	BSTNode( BSTNode* parent, BSTNode* right, BSTNode* left, const int value):
		basic_node(parent, right, left, value)
	{

	}
};

class BST: public basic_tree<BSTNode, int>
{
public:
	~BST()
	{
		clear();
	}

	void insert(const int value) override;
	void deleteNode(BSTNode* node) override;

	void printNode(BSTNode* node) const override;

	using basic_tree::rightRotation;
	using basic_tree::leftRotation;

private:
	void deleteOneCh(BSTNode* node);
};