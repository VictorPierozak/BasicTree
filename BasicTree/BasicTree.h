#pragma once
#include<stack>
template<typename nodeType, typename valueType>
class basic_node
{
public:
	nodeType* _parent;
	nodeType* _right;
	nodeType* _left;

	valueType _value;

	basic_node() : _parent(nullptr), _right(nullptr), _left(nullptr), _value()
	{

	}
	basic_node(nodeType* parent, nodeType* right, nodeType* left, const valueType value) :
		_parent(parent), _right(right), _left(left), _value(value)
	{

	}
};

//nodeType should inherts from basic_node

template<typename nodeType, typename valueType>
class basic_tree
{
public:

	basic_tree() :_root(nullptr)
	{

	}

	virtual ~basic_tree();

	virtual void insert(const valueType value) = 0;
	virtual void deleteNode(nodeType* node) = 0;

	virtual void clear();

	void inOrder(bool print = false) const;
	void preOrder(bool print = false) const;
	void postOrder(bool print = false) const;

	nodeType* findValue(const valueType) const;
	nodeType* findMin(nodeType* = _root) const;
	nodeType* findMax(nodeType* = _root) const;

	nodeType* findN(nodeType* = _root) const;
	nodeType* findP(nodeType* = _root) const;

	nodeType* returnRoot() const
	{
		return _root;
	}

protected:

	void rightRotation(nodeType* node);
	void leftRotation(nodeType* node);

	virtual void printNode(nodeType* node) const = 0;

	void setNewCh(nodeType* parent, nodeType* prevChild, nodeType* newChild);
	void swapValues(nodeType* A, nodeType* B);

	nodeType* _root;

};

template<typename nodeType, typename valueType>
void basic_tree<nodeType, valueType>::swapValues(nodeType* A, nodeType* B)
{
	valueType tmp = A->_value;
	A->_value = B->_value;
	B->_value = tmp;
}
template<typename nodeType, typename valueType>
basic_tree<nodeType, valueType>::~basic_tree()
{
	
}

template<typename nodeType, typename valueType>
void basic_tree<nodeType, valueType>::clear()
{
	while (_root != nullptr)
		deleteNode(_root);
}

template<typename nodeType, typename valueType>
void basic_tree<nodeType, valueType>::inOrder(bool print) const
{
	std::stack<nodeType*> nodesToVisit;
	nodeType* current = _root;

	while (true)
	{
		if (current == nullptr)
		{
			if (nodesToVisit.empty())
				break;
			current = nodesToVisit.top();
			nodesToVisit.pop();
			if (print) printNode(current);
			current = current->_right;
			continue;
		}
		nodesToVisit.push(current);
		current = current->_left;
	}
}

template<typename nodeType, typename valueType>
void basic_tree<nodeType, valueType>::preOrder(bool print) const
{
	std::stack<nodeType*> nodesToVisit;
	nodeType* current = _root;

	while (true)
	{
		if (current == nullptr)
		{
			if (nodesToVisit.empty())
				break;
			current = nodesToVisit.top();
			nodesToVisit.pop();
			current = current->_right;
			continue;
		}
		if (print) printNode(current);
		nodesToVisit.push(current);
		current = current->_left;
	}
}

template<typename nodeType, typename valueType>
void basic_tree<nodeType, valueType>::postOrder(bool print) const
{
	std::stack<nodeType*> nodesToVisit;
	nodeType* current = _root;

	while (true)
	{
		if (current == nullptr)
		{
			if (nodesToVisit.empty())
				break;
			current = nodesToVisit.top();
			nodesToVisit.pop();
			if (print) printNode(current);
			current = current->_left;
			continue;
		}
		nodesToVisit.push(current);
		current = current->_right;
	}
}

template<typename nodeType, typename valueType>
nodeType* basic_tree<nodeType, valueType>::findValue(const valueType value) const
{
	nodeType* current = _root;
	while (current != nullptr)
	{
		if (current->_value == value) break;
		if (current->_value > value)
			current = current->_left;
		else current = current->_right;
	}
	return current;
}

template<typename nodeType, typename valueType>
nodeType* basic_tree<nodeType, valueType>::findMin(nodeType* node) const
{
	if (node == nullptr) return nullptr;
	while (node->_left)
		node = node->_left;
	return node;
}

template<typename nodeType, typename valueType>
nodeType* basic_tree<nodeType, valueType>::findMax(nodeType* node) const
{
	if (node == nullptr) return nullptr;
	while (node->_right)
		node = node->_right;
	return node;
}

template<typename nodeType, typename valueType>
nodeType* basic_tree<nodeType, valueType>::findN(nodeType* node) const
{
	nodeType* N = nullptr;
	if (node->_right) N = findMin(node->_right);
	else
	{
		while (node != nullptr && node->_parent != nullptr)
		{
			if (node->_parent->_left == node)
			{
				N = node->_parent;
				break;
			}
			node = node->_parent;
		}
	}
	return N;
}

template<typename nodeType, typename valueType>
nodeType* basic_tree<nodeType, valueType>::findP(nodeType* node) const
{
	nodeType* P = nullptr;
	if (node->_left) P = findMax(node->_left);
	else
	{
		while (node != nullptr && node->_parent != nullptr)
		{
			if (node->_parent->_right == node)
			{
				P = node->_parent;
				break;
			}
			node = node->_parent;
		}
	}
	return P;
}

template<typename nodeType, typename valueType>
void basic_tree<nodeType, valueType>::rightRotation(nodeType* node)
{
	if (node->_left == nullptr) return;
	nodeType* left = node->_left;
	nodeType* parent = node->_parent;

	node->_left = left->_right;
	if (node->_left)
		node->_left->_parent = node;
	left->_right = node;
	node->_parent = left;
	left->_parent = parent;
	if (parent)
		if (parent->_left == node)
			parent->_left = left;
		else parent->_right = left;
	if (node == _root)
		_root = left;
}

template<typename nodeType, typename valueType>
void basic_tree<nodeType, valueType>::leftRotation(nodeType* node)
{
	if (node->_right == nullptr) return;
	nodeType* right = node->_right;
	nodeType* parent = node->_parent;

	node->_right = right->_left;
	if (node->_right)
		node->_right->_parent = node;
	right->_left = node;
	node->_parent = right;
	right->_parent = parent;
	if (parent)
		if (parent->_left == node)
			parent->_left = right;
		else parent->_right = right;

	if (node == _root)
		_root = right;
}

template<typename nodeType, typename valueType>
void basic_tree<nodeType, valueType>::setNewCh(nodeType* parent, nodeType* prevChild, nodeType* newChild)
{
	if (parent->_left == prevChild)
		parent->_left = newChild;
	else parent->_right = newChild;
	if (newChild) newChild->_parent = parent;
}