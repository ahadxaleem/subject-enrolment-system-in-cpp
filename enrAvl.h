#include<iostream>
#include<conio.h>
#include<vector>
using namespace std;
class enrAVLNode
{
private:
	int	info;
	int time;
	char verdig;
	vector<int> nrc;
	enrAVLNode* left;		
	enrAVLNode* right;		
	enrAVLNode* parent;	
	int	height;		

public:
	enrAVLNode();
	enrAVLNode(int info,char verdig);
	int getInfo();
	int getTime();
	char getVerDig();
	vector<int> getNRC();
	void clearNRC();
	void setVarDig(char dig);
	void addNRC(int nrc);
	void setInfo(int info);
	void setTime(int time);
	enrAVLNode* getLeft();
	void setLeft(enrAVLNode* left);
	enrAVLNode* getRight();
	void setRight(enrAVLNode* right);
	int isLeaf();
	enrAVLNode* getParent();
	void setParent(enrAVLNode* parent);
	int getHeight();
	void setHeight(int b);

};
enrAVLNode::enrAVLNode()
{
	this->info = -1;
	this->left = this->right = NULL;
	this->parent = NULL;
	this->height = 0;

}
enrAVLNode::enrAVLNode(int info,char verdig)
{
	this->info = info;
	this->verdig=verdig;
	this->left = this->right = NULL;
	this->parent = NULL;
	this->height = 0;

}
int enrAVLNode::getInfo()
{
	return this->info;
}
int enrAVLNode::getTime()
{
	return this->time;
}
char enrAVLNode::getVerDig()
{
	return this->verdig;
}
vector<int> enrAVLNode::getNRC(){
	return this->nrc;
}
void enrAVLNode::clearNRC(){
	this->nrc.clear();
}
void enrAVLNode::setInfo(int info)
{
	this->info = info;

}
void enrAVLNode::setTime(int time)
{
	this->time = time;

}
void enrAVLNode::setVarDig(char verdig)
{
	this->verdig = verdig;

}
void enrAVLNode::addNRC(int nrc){
	this->nrc.push_back(nrc);
}
enrAVLNode* enrAVLNode::getLeft()
{
	return this->left;

}
void enrAVLNode::setLeft(enrAVLNode* left)
{
	this->left = left;
}
enrAVLNode* enrAVLNode::getRight()
{
	return this->right;

}
void enrAVLNode::setRight(enrAVLNode* right)
{

	this->right = right;

}
int enrAVLNode::isLeaf()
{

	if (this->left == NULL && this->right == NULL)
		return 1;
	return 0;
}
enrAVLNode* enrAVLNode::getParent()
{
	return this->parent;

}
void enrAVLNode::setParent(enrAVLNode* parent)
{
	this->parent = parent;


}
int enrAVLNode::getHeight()
{
	return this->height;
}
void enrAVLNode::setHeight(int B)
{
	this->height = B;

}

int enrMax(int a, int b)
{
	return (a > b) ? a : b;
}
class enrAVL {
public:
	void insert(int info,char verdig);
	void Delete(int info);
	enrAVLNode *search(int info);
	enrAVLNode *search(enrAVLNode *p, int data);
	enrAVLNode *searchTime(int time);
	enrAVLNode *searchTime(enrAVLNode *p, int data);
	enrAVLNode* AVL_insert(enrAVLNode* parent, int info,char verdig);
	enrAVLNode* Delete(enrAVLNode* p, int data);
	void addNRC(int info,int nrc);
	void setTime(int info,int time);
	void clearNRC(int info);
	enrAVLNode* singleRightRotation(enrAVLNode* k2);
	enrAVLNode* singleLeftRotation(enrAVLNode* k1);
	enrAVLNode* doubleLeftRightRotation(enrAVLNode* k3);
	enrAVLNode* doubleRightLeftRotation(enrAVLNode* k1);
	void inorder(enrAVLNode* node);
	int height(enrAVLNode* node);
	enrAVLNode* Right_move(enrAVLNode* t);
	enrAVLNode* Left_move(enrAVLNode* t);
	int getBalanceFactor(enrAVLNode *b);
	enrAVL();
public:
	enrAVLNode* root;
};
enrAVL::enrAVL()
{
	this->root = NULL;
}
enrAVLNode* enrAVL::doubleRightLeftRotation(enrAVLNode* k1)
{
	if (k1 == NULL) return NULL;
	k1->setRight(singleRightRotation(k1->getRight()));
	return singleLeftRotation(k1);
}

enrAVLNode *enrAVL::search(int data)
{
	return search(root, data);
}

enrAVLNode *enrAVL::search(enrAVLNode *t, int data)
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

enrAVLNode *enrAVL::searchTime(int time)
{
	return searchTime(root, time);
}

enrAVLNode *enrAVL::searchTime(enrAVLNode *t, int time)
{
	if (t != NULL)
	{
		if(t->getTime()==time)
			return t;
		enrAVLNode* temp1 = searchTime(t->getLeft(),time);
		enrAVLNode* temp2 = searchTime(t->getRight(),time);
		if(temp1==NULL&&temp2==NULL){
			return NULL;
		}
		else if(temp1==NULL){
			return temp2;
		}
		else{
			return temp1;
		}
	}
	return t;
}

void enrAVL::addNRC(int info,int nrc)
{
	search(info)->addNRC(nrc);
}
void enrAVL::setTime(int info,int time){
	search(info)->setTime(time);
}

void enrAVL::clearNRC(int info)
{
	search(info)->clearNRC();
}

enrAVLNode* enrAVL::doubleLeftRightRotation(enrAVLNode* k3)
{
	if (k3 == NULL) return NULL;
	k3->setLeft(singleLeftRotation(k3->getLeft()));
	return singleRightRotation(k3);

}
enrAVLNode* enrAVL::singleLeftRotation(enrAVLNode* k1)
{
	if (k1 == NULL) return NULL;
	enrAVLNode* k2 = k1->getRight();
	k1->setRight(k2->getLeft()); 
	k2->setLeft(k1);
	int h = enrMax(height(k1->getLeft()),
		height(k1->getRight()));
	k1->setHeight(h + 1);
	h = enrMax(height(k2->getRight()),
		k1->getHeight());
	k2->setHeight(h + 1);

	return k2;
}
enrAVLNode* enrAVL::singleRightRotation(enrAVLNode* k2)
{
	if (k2 == NULL) return NULL;
	enrAVLNode* k1 = k2->getLeft();
	k2->setLeft(k1->getRight());
	k1->setRight(k2);

	int leftheight = height(k2->getLeft());
	int rightheight = height(k2->getRight());
	int h = enrMax(leftheight, rightheight);
	k2->setHeight(h + 1);
	h = enrMax(height(k1->getLeft()), k2->getHeight());
	k1->setHeight(h + 1);
	return k1;
}
void enrAVL::insert(int info,char verdig)
{
	root = AVL_insert(root, info,verdig);
}
enrAVLNode* enrAVL::AVL_insert(enrAVLNode* parent, int info,char verdig)
{
	if (parent == NULL)
		return(new enrAVLNode(info,verdig));
	if (info < parent->getInfo())
		parent->setLeft(AVL_insert(parent->getLeft(), info,verdig));
	else if (info > parent->getInfo())
		parent->setRight(AVL_insert(parent->getRight(), info,verdig));
	else
		return parent;

	// balance the tree
	parent->setHeight(1 + enrMax(height(parent->getLeft()),
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
void enrAVL::Delete(int data)
{
	root = Delete(root, data);
}
enrAVLNode* enrAVL::Delete(enrAVLNode* t, int data)
{
	if (t->getLeft() == NULL && t->getRight() == NULL)
	{
		if (t == this->root)
			this->root = NULL;
		else
			return NULL;
	}

	enrAVLNode *x;
	enrAVLNode *y;
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
enrAVLNode* enrAVL::Right_move(enrAVLNode* t)
{
	{
		while (t->getRight() != NULL)
			t->setRight(t->getRight());
		return t;
	}
}
enrAVLNode*enrAVL::Left_move(enrAVLNode* t)
{
	while (t->getLeft() != NULL)
		t->setLeft(t->getLeft());
	return t;
}
int enrAVL::height(enrAVLNode* node)
{
	if (node != NULL)
		return node->getHeight();
	return -1;
}
int enrAVL::getBalanceFactor(enrAVLNode * b)
{
	if (b == NULL)
		return 0;
	return height(b->getLeft()) - height(b->getRight());
}
void enrAVL::inorder(enrAVLNode* node)
{
	if (node != NULL)
	{
		inorder(node->getLeft());
		cout << node->getInfo() << " ";
		vector<int> temp=node->getNRC();
		for(int i=0;i<temp.size();i++)
			cout<<temp[i]<<" ";
		cout<<endl;
		inorder(node->getRight());
	}
}