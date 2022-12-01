#include <iostream>
#include <conio.h>
#include <fstream>
using namespace std;
class AVLNode
{
private:
	int info, value;
	AVLNode *left;
	AVLNode *right;
	AVLNode *parent;
	int height;

public:
	AVLNode();
	AVLNode(int info, int value);
	int getInfo();
	void setInfo(int info);
	int getValue();
	void setValue(int value);
	AVLNode *getLeft();
	void setLeft(AVLNode *left);
	AVLNode *getRight();
	void setRight(AVLNode *right);
	int isLeaf();
	AVLNode *getParent();
	void setParent(AVLNode *parent);
	int getHeight();
	void setHeight(int b);
};
AVLNode::AVLNode()
{
	this->info = -1;
	this->value = -1;
	this->left = this->right = NULL;
	this->parent = NULL;
	this->height = 0;
}
AVLNode::AVLNode(int info, int value)
{
	this->info = info;
	this->value = value;
	this->left = this->right = NULL;
	this->parent = NULL;
	this->height = 0;
}
int AVLNode::getInfo()
{
	return this->info;
}
void AVLNode::setInfo(int info)
{
	this->info = info;
}
int AVLNode::getValue()
{
	return this->value;
}
void AVLNode::setValue(int value)
{
	this->value = value;
}
AVLNode *AVLNode::getLeft()
{
	return this->left;
}
void AVLNode::setLeft(AVLNode *left)
{
	this->left = left;
}
AVLNode *AVLNode::getRight()
{
	return this->right;
}
void AVLNode::setRight(AVLNode *right)
{

	this->right = right;
}
int AVLNode::isLeaf()
{

	if (this->left == NULL && this->right == NULL)
		return 1;
	return 0;
}
AVLNode *AVLNode::getParent()
{
	return this->parent;
}
void AVLNode::setParent(AVLNode *parent)
{
	this->parent = parent;
}
int AVLNode::getHeight()
{
	return this->height;
}
void AVLNode::setHeight(int B)
{
	this->height = B;
}

int Max(int a, int b)
{
	return (a > b) ? a : b;
}
class quotaAVL
{
public:
	void insert(int info, int value);
	void Delete(int info);
	AVLNode *search(int info);
	AVLNode *AVL_insert(AVLNode *parent, int info, int value);
	AVLNode *Delete(AVLNode *p, int data);
	AVLNode *search(AVLNode *p, int data);
	AVLNode *singleRightRotation(AVLNode *k2);
	AVLNode *singleLeftRotation(AVLNode *k1);
	AVLNode *doubleLeftRightRotation(AVLNode *k3);
	AVLNode *doubleRightLeftRotation(AVLNode *k1);
	void inorder(AVLNode *node);
	string writeTofile(AVLNode *node);
	int updateQuota(int info, int num);
	int height(AVLNode *node);
	AVLNode *Right_move(AVLNode *t);
	AVLNode *Left_move(AVLNode *t);
	int getBalanceFactor(AVLNode *b);
	quotaAVL();

public:
	AVLNode *root;
};
quotaAVL::quotaAVL()
{
	this->root = NULL;
}
AVLNode *quotaAVL::doubleRightLeftRotation(AVLNode *k1)
{
	if (k1 == NULL)
		return NULL;
	k1->setRight(singleRightRotation(k1->getRight()));
	return singleLeftRotation(k1);
}

AVLNode *quotaAVL::doubleLeftRightRotation(AVLNode *k3)
{
	if (k3 == NULL)
		return NULL;
	k3->setLeft(singleLeftRotation(k3->getLeft()));
	return singleRightRotation(k3);
}
AVLNode *quotaAVL::singleLeftRotation(AVLNode *k1)
{
	if (k1 == NULL)
		return NULL;
	AVLNode *k2 = k1->getRight();
	k1->setRight(k2->getLeft());
	k2->setLeft(k1);
	int h = Max(height(k1->getLeft()),
				height(k1->getRight()));
	k1->setHeight(h + 1);
	h = Max(height(k2->getRight()),
			k1->getHeight());
	k2->setHeight(h + 1);

	return k2;
}
AVLNode *quotaAVL::singleRightRotation(AVLNode *k2)
{
	if (k2 == NULL)
		return NULL;
	AVLNode *k1 = k2->getLeft();
	k2->setLeft(k1->getRight());
	k1->setRight(k2);

	int leftheight = height(k2->getLeft());
	int rightheight = height(k2->getRight());
	int h = Max(leftheight, rightheight);
	k2->setHeight(h + 1);
	h = Max(height(k1->getLeft()), k2->getHeight());
	k1->setHeight(h + 1);
	return k1;
}
void quotaAVL::insert(int info, int value)
{
	root = AVL_insert(root, info, value);
}
AVLNode *quotaAVL::AVL_insert(AVLNode *parent, int info, int value)
{
	if (parent == NULL)
		return (new AVLNode(info, value));
	if (info < parent->getInfo())
		parent->setLeft(AVL_insert(parent->getLeft(), info, value));
	else if (info > parent->getInfo())
		parent->setRight(AVL_insert(parent->getRight(), info, value));
	else
		return parent;

	// balance the tree
	parent->setHeight(1 + Max(height(parent->getLeft()),
							  height(parent->getRight())));
	int balanceFactor = getBalanceFactor(parent);
	if (balanceFactor > 1)
	{
		if (info < parent->getLeft()->getInfo())
		{
			return singleRightRotation(parent);
		}
		else if (info > parent->getLeft()->getInfo())
		{
			parent->setLeft(singleLeftRotation(parent->getLeft()));
			return singleRightRotation(parent);
		}
	}
	if (balanceFactor < -1)
	{
		if (info > parent->getRight()->getInfo())
		{
			return singleLeftRotation(parent);
		}
		else if (info > parent->getRight()->getInfo())
		{
			parent->setRight(singleRightRotation(parent->getRight()));
			return singleLeftRotation(parent);
		}
	}
	return parent;
}
void quotaAVL::Delete(int data)
{
	root = Delete(root, data);
}
AVLNode *quotaAVL::search(int data)
{
	return search(root, data);
}
AVLNode *quotaAVL::Delete(AVLNode *t, int data)
{
	if (t->getLeft() == NULL && t->getRight() == NULL)
	{
		if (t == this->root)
			this->root = NULL;
		else
			return NULL;
	}

	AVLNode *x;
	AVLNode *y;
	if (t->getInfo() < data)
	{
		t->setRight(Delete(t->getRight(), data));
	}
	else if (t->getInfo() > data)
	{
		t->setLeft(Delete(t->getLeft(), data));
	}
	else
	{
		if (t->getLeft() != NULL)
		{
			y = Right_move(t->getLeft());
			t->setInfo(y->getInfo());
			t->setLeft(Delete(t->getLeft(), y->getInfo()));
		}
		else
		{
			y = Left_move(t->getRight());
			t->setInfo(y->getInfo());
			t->setRight(Delete(t->getRight(), y->getInfo()));
		}
	}

	if (getBalanceFactor(t) == 2 && getBalanceFactor(t->getLeft()) == 1)
	{
		t = singleLeftRotation(t);
	}
	else if (getBalanceFactor(t) == 2 && getBalanceFactor(t->getLeft()) == -1)
	{
		t = doubleLeftRightRotation(t);
	}
	else if (getBalanceFactor(t) == 2 && getBalanceFactor(t->getLeft()) == 0)
	{
		t = singleLeftRotation(t);
	}
	else if (getBalanceFactor(t) == -2 && getBalanceFactor(t->getLeft()) == -1)
	{
		t = singleLeftRotation(t);
	}
	else if (getBalanceFactor(t) == -2 && getBalanceFactor(t->getRight()) == 1)
	{
		t = doubleRightLeftRotation(t);
	}
	else if (getBalanceFactor(t) == -2 && getBalanceFactor(t->getRight()) == 0)
	{
		t = singleLeftRotation(t);
	}
	return t;
}

AVLNode *quotaAVL::search(AVLNode *t, int data)
{
	if (t == NULL)
	{
		return NULL;
	}

	if (t->getInfo() != data)
	{
		if (t->getRight() == NULL && t->getLeft() == NULL)
		{
			return NULL;
		}
		else
		{
			if (t->getInfo() < data)
			{
				return search(t->getRight(), data);
			}
			else if (t->getInfo() > data)
			{
				return search(t->getLeft(), data);
			}
		}
	}
	return t;
}

AVLNode *quotaAVL::Right_move(AVLNode *t)
{
	{
		while (t->getRight() != NULL)
			t->setRight(t->getRight());
		return t;
	}
}
AVLNode *quotaAVL::Left_move(AVLNode *t)
{
	while (t->getLeft() != NULL)
		t->setLeft(t->getLeft());
	return t;
}
int quotaAVL::height(AVLNode *node)
{
	if (node != NULL)
		return node->getHeight();
	return -1;
}
int quotaAVL::getBalanceFactor(AVLNode *b)
{
	if (b == NULL)
		return 0;
	return height(b->getLeft()) - height(b->getRight());
}
void quotaAVL::inorder(AVLNode *node)
{
	if (node != NULL)
	{
		inorder(node->getLeft());
		if (node->getValue() == 0)
			cout << node->getInfo() << " ";
		// cout << node->getInfo()<< " : " << node->getValue() << endl;
		inorder(node->getRight());
	}
}

string quotaAVL::writeTofile(AVLNode *node)
{
	if (node != NULL)
	{

		return writeTofile(node->getLeft()) + to_string(node->getInfo()) + "," + to_string(node->getValue()) + "\n" + writeTofile(node->getRight());
	}
	return "";
}
int quotaAVL::updateQuota(int info, int num)
{
	AVLNode *temp = search(info);
	if (temp->getValue() + num > 0)
	{
		search(info)->setValue(num + temp->getValue());
		return 1;
	}
	return 0;
}