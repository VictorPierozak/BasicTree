#include"BasicTree.h"

class AVLNode : public basic_node<AVLNode, int>
{
public:
	AVLNode() : basic_node(nullptr, nullptr, nullptr, 0), _height(0), _balance(0)
	{

	}
	AVLNode(AVLNode* parent, AVLNode* right, AVLNode* left, const int value, const int height, const int balance) :
		basic_node(parent, right, left, value), _height(height), _balance(balance)
	{

	}

public:
	int _height;
	int _balance;
};

class AVLTree : public basic_tree<AVLNode, int>
{
public:

	~AVLTree()
	{
		clear();
	}

	virtual void insert(const int value) override;
	virtual void deleteNode(AVLNode* node) override;

	virtual void printNode(AVLNode* node) const override;

private:
	void deleteOneCh(AVLNode* node);
	void balanceSubTree(AVLNode* rootSubTree);
	void calcBalance(AVLNode* node);
};