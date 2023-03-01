#include"BasicTree.h"

enum{BLACK, RED};



class RBNode : public basic_node<RBNode, int>
{
public:
	RBNode() : basic_node(nullptr, nullptr, nullptr, 0), _color(BLACK)
	{

	}
	RBNode(RBNode* parent, RBNode* right, RBNode* left, const int value, const int color) :
		basic_node(parent, right, left, value), _color(color)
	{

	}

public:
	int _color;
};


class RBTree : public basic_tree<RBNode, int>
{
public:

	~RBTree()
	{
		clear();
	}
	void insert(const int value) override;
	void deleteNode(RBNode* node) override;

	void printNode(RBNode* node) const override;

private:

	void setNewCh(RBNode* parent, RBNode* prevChild, RBNode* newChild, RBNode*& sibling);

	void deleteRoot();

	void fixInsertion(RBNode* node);
	void fixInsertionL(RBNode* node, RBNode* parent);
	void fixInsertionR(RBNode* node, RBNode* parent);
	void fixDeletion(RBNode* dbParent, RBNode* sibling, const int deletedColor);
};