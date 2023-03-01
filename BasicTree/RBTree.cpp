#include"RBTree.h"
#include<iostream>


void RBTree::insert(const int value)
{
	if (_root == nullptr)
	{
		_root = new RBNode(nullptr, nullptr, nullptr, value, BLACK);
		return;
	}

	RBNode* parent = _root->_parent;
	RBNode* current = _root;
	while (true)
	{
		if (current->_value > value)
		{
			if (current->_left == nullptr)
			{
				current->_left = new RBNode(current,nullptr,nullptr, value, RED);
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
				current->_right = new RBNode(current, nullptr, nullptr, value, RED);
				current = current->_right;
				break;
			}

			parent = current;
			current = current->_right;
		}
	}

	if (current->_parent->_color == RED)
		fixInsertion(current);
}


void RBTree::deleteNode(RBNode* node)
{
	if (node == nullptr) return;
	RBNode* toSwap = findMin(node->_right);
	RBNode* toHandle = nullptr;
	RBNode* toDelete = nullptr;
	RBNode* sibling;
	int deletedColor = node->_color;

	if (toSwap == nullptr)
	{
		setNewCh(node->_parent, node, node->_left, sibling);
		if (node->_left)
		{
			deletedColor = node->_left->_color;
			node->_left->_color = node->_color;
			toHandle = node->_left;
		}
		else
		{
			toHandle = node->_parent;
		}
		if (node == _root) {
			deleteRoot();
			return;
		}

		delete node;
		fixDeletion(toHandle, sibling, deletedColor);
		return;
	}

	node->_value = toSwap->_value;
	toDelete = toSwap;
	toHandle = toSwap->_parent;
	if (toSwap->_right)
	{
		deletedColor = toSwap->_right->_color;
		toSwap->_right->_color = toSwap->_color;
		swapValues(node, toSwap);
	}
	else deletedColor = toSwap->_color;
	setNewCh(toSwap->_parent, toSwap, toSwap->_right, sibling);

	delete toDelete;

	fixDeletion(toHandle, sibling, deletedColor);
}


void RBTree::RBTree::deleteRoot()
{
	RBNode* toDelete = _root;
	if (_root->_left)
	{
		_root = _root->_left;
		_root->_parent = nullptr;
		_root->_color = BLACK;
	}
	else if (_root->_right)
	{
		_root = _root->_right;
		_root->_parent = nullptr;
		_root->_color = BLACK;
	}
	else _root = nullptr;
	delete toDelete;

}


void RBTree::fixInsertion(RBNode* node)
{
	RBNode* parent = nullptr;
	RBNode* uncle = nullptr;

	while (node && node->_parent && node->_parent->_color == RED)
	{
		parent = node->_parent;
		if (parent->_parent->_left == parent)
			uncle = parent->_parent->_right;
		else uncle = parent->_parent->_left;

		if (uncle == nullptr || uncle->_color == BLACK)
		{
			if (parent->_parent->_left == parent)
				fixInsertionL(node, parent);
			else fixInsertionR(node, parent);
		}
		else
		{
			parent->_color = BLACK;
			uncle->_color = BLACK;
			if (parent->_parent != _root)
				parent->_parent->_color = RED;
			node = parent->_parent;
		}
	}
}


void RBTree::fixInsertionL(RBNode* node, RBNode* parent)
{
	if (parent->_right == node)
	{
		leftRotation(parent);
		parent = node;
	}
	parent->_parent->_color = RED;
	parent->_color = BLACK;

	rightRotation(parent->_parent);
}


void RBTree::fixInsertionR(RBNode* node, RBNode* parent)
{
	if (parent->_left == node)
	{
		rightRotation(parent);
		parent = node;
	}

	parent->_parent->_color = RED;
	parent->_color = BLACK;

	leftRotation(parent->_parent);
}


void RBTree::fixDeletion(RBNode* dbParent, RBNode* sibling, const int deletedColor)
{
	if (deletedColor == RED) return;
	RBNode* doubleBlack = nullptr;
	while (true)
	{
		if (sibling->_color == BLACK && dbParent->_color == RED)
		{
			sibling->_color = RED;
			dbParent->_color = BLACK;
			return;
		}

		if (sibling->_color == RED)
		{
			sibling->_color = BLACK;
			dbParent->_color = RED;
			if (dbParent->_left == sibling)
			{
				rightRotation(dbParent);
				dbParent->_color = BLACK;
				dbParent->_left->_color = RED;
			}
			else
			{
				leftRotation(dbParent);
				dbParent->_color = BLACK;
				dbParent->_right->_color = RED;
			}
			return;
		}

		if (dbParent->_left == sibling)
		{
			if (sibling->_left == nullptr && sibling->_right && sibling->_right->_color == RED)
			{
				leftRotation(sibling);
				sibling = sibling->_parent;
			}
			if (sibling->_left && sibling->_left->_color == RED)
			{
				rightRotation(dbParent);
				dbParent->_parent->_left->_color = BLACK;
				return;
			}
		}

		if (dbParent->_right == sibling)
		{
			if (sibling->_right == nullptr && sibling->_left && sibling->_left->_color == RED)
			{
				rightRotation(sibling);
				sibling = sibling->_parent;
			}
			if (sibling->_right && sibling->_right->_color == RED)
			{
				leftRotation(dbParent);
				dbParent->_parent->_right->_color = BLACK;
				return;
			}
		}

		sibling->_color = RED;
		doubleBlack = dbParent;

		if (doubleBlack == _root) return;

		if (dbParent->_color == RED) dbParent->_color = BLACK;
		dbParent = doubleBlack->_parent;
		if (dbParent->_left == doubleBlack)
			sibling = dbParent->_right;
		else sibling = dbParent->_left;
	}

}


void RBTree::printNode(RBNode* node) const
{
	if (node->_color == RED)
		std::cout << " >> RED " << node->_value;
	else std::cout << " >> BLACK " << node->_value;
}


void RBTree::setNewCh(RBNode* parent, RBNode* prevChild, RBNode* newChild, RBNode*& sibling)
{
	if (parent == nullptr) return;
	if (parent->_left == prevChild)
	{
		parent->_left = newChild;
		sibling = parent->_right;
	}
	else
	{
		parent->_right = newChild;
		sibling = parent->_left;
	}
	if (newChild) newChild->_parent = parent;
}