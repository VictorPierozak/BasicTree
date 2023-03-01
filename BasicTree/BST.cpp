#include"BST.h"

void BST::insert(const int value)
{
	if (_root == nullptr)
		_root = new BSTNode(nullptr, nullptr, nullptr, value);
	else
	{
		BSTNode* current = _root;
		while (true)
		{
			if (current->_value > value)
			{
				if (current->_left == nullptr)
				{
					current->_left = new BSTNode(current, nullptr, nullptr, value);
					break;
				}
				else current = current->_left;
			}
			else if (current->_right == nullptr)
			{
				current->_right = new BSTNode(current, nullptr, nullptr, value);
				break;
			}
			else current = current->_right;
		}
		
	}
}

void BST::deleteOneCh(BSTNode* node)
{
	BSTNode* toSwap = nullptr;
	if (node->_left != nullptr)
		toSwap = node->_left;
	else toSwap = node->_right;
	if (node == _root)
	{
		_root = toSwap;
		if(toSwap) toSwap->_parent = nullptr;
	}
	else setNewCh(node->_parent, node, toSwap);
	delete node;
}

void BST::deleteNode(BSTNode* node)
{
	if (node == nullptr) return;
	BSTNode* toSwap = nullptr;
	if (node->_left == nullptr || node->_right == nullptr)
	{
		deleteOneCh(node);
	}
	else
	{
		toSwap = findMax(node->_right);
		node->_value = toSwap->_value;
		deleteOneCh(toSwap);
	}
}
void BST::printNode(BSTNode* node) const
{
	std::cout << node->_value << ' ';
}