#include<iostream>
#include"AVLTree.h"

void AVLTree::insert(const int value)
{
	if (_root == nullptr)
	{
		_root = new AVLNode(nullptr, nullptr, nullptr, value, 0,0);
		return;
	}

	AVLNode* parent = _root->_parent;
	AVLNode* current = _root;
	while (true)
	{
		if (current->_value > value)
		{
			if (current->_left == nullptr)
			{
				current->_left = new AVLNode(current, nullptr, nullptr, value, 0, 0);
				current = current->_left;
				break;
			}

			parent = current;
			current = current->_left;
		}
		else
		{
			if (current->_right == nullptr)
			{
				current->_right = new AVLNode(current, nullptr, nullptr, value, 0, 0);
				current = current->_right;
				break;
			}

			parent = current;
			current = current->_right;
		}
	}

	while (current != nullptr)
	{
		calcBalance(current);
		balanceSubTree(current);
		current = current->_parent;
	}
}

void AVLTree::deleteNode(AVLNode* node)
{
	if (node == nullptr) return;
	if (node->_left == nullptr || node->_right == nullptr)
	{
		deleteOneCh(node);
	}
	else
	{
		AVLNode* toSwap = findMin(node->_right);
		AVLNode* parent = toSwap->_parent;
		swapValues(node, toSwap);

		deleteOneCh(toSwap);

		if (parent)
		{
			int prevHeight = parent->_height;
			calcBalance(parent);

			if (prevHeight != parent->_height && parent->_height != 0)
			{
				while (parent != nullptr)
				{
					balanceSubTree(parent);
					parent = parent->_parent;
				}
			}
			else if (parent->_balance == -2)
			{
				leftRotation(parent);
				calcBalance(parent);
				calcBalance(parent->_parent);
			}
		}
	}
}

void AVLTree::deleteOneCh(AVLNode* node)
{
	AVLNode* child = nullptr;
	AVLNode* toDelete = node;

	if (node->_left != nullptr)
		child = node->_left;
	else child = node->_right;

	if (node == _root)
	{
		_root = child;
	}
	else setNewCh(node->_parent, node, child);

	delete toDelete;
}

void AVLTree::printNode(AVLNode* node) const
{
	std::cout << node->_value << ' ';
}


void AVLTree::balanceSubTree(AVLNode* rootSubTree)
{
	calcBalance(rootSubTree);
	switch (rootSubTree->_balance)
	{
	case 2:
		if (rootSubTree->_left->_balance == -1)
		{
			leftRotation(rootSubTree->_left);
			calcBalance(rootSubTree->_left->_left);
			calcBalance(rootSubTree->_left);
		}
		rightRotation(rootSubTree);
		calcBalance(rootSubTree);
		calcBalance(rootSubTree->_parent);
		break;

	case -2:
		if (rootSubTree->_right->_balance == 1)
		{
			rightRotation(rootSubTree->_right);
			calcBalance(rootSubTree->_right->_right);
			calcBalance(rootSubTree->_right);
		}
		leftRotation(rootSubTree);
		calcBalance(rootSubTree);
		calcBalance(rootSubTree->_parent);
		break;

	default:
		break;
	}
}

void AVLTree::calcBalance(AVLNode* node)
{
	node->_balance = 0;
	node->_height = 0;
	if (node == nullptr) return;
	if (node->_right)
	{
		node->_balance -= node->_right->_height;
		node->_height = node->_right->_height + 1;
	}
	else node->_balance += 1;
	if (node->_left)
	{
		node->_balance += node->_left->_height;
		if (node->_left->_height > (node->_height - 1))
			node->_height = node->_left->_height + 1;
	}
	else node->_balance -= 1;
}