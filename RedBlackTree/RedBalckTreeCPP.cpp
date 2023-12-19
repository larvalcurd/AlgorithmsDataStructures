#include <iostream>

using namespace std;

struct Node 
{
	int data; 
	Node* parent; 
	Node* left; 
	Node* right; 
	int color; 
};

typedef Node* NodePtr;

class RBTree 
{
private:
	NodePtr root;
	NodePtr TNULL;

	void initializeNULLNode(NodePtr node, NodePtr parent) 
	{
		node->data = 0;
		node->parent = parent;
		node->left = nullptr;
		node->right = nullptr;
		node->color = 0;
	}

	void preOrderHelper(NodePtr node) 
	{
		if (node != TNULL) 
		{
			cout << node->data << " ";
			preOrderHelper(node->left);
			preOrderHelper(node->right);
		}
	}

	void inOrderHelper(NodePtr node) 
	{
		if (node != TNULL) 
		{
			inOrderHelper(node->left);
			cout << node->data << " ";
			inOrderHelper(node->right);
		}
	}

	void postOrderHelper(NodePtr node) 
	{
		if (node != TNULL) 
		{
			postOrderHelper(node->left);
			postOrderHelper(node->right);
			cout << node->data << " ";
		}
	}

	NodePtr searchParentHelper(NodePtr node, int key) 
	{
		if (node == TNULL || key == node->left->data || key == node->right->data)
		{
			return node;
		}

		if (key < node->data)
		{
			return searchTreeHelper(node->left, key);
		}
		return searchTreeHelper(node->right, key);
	}

	NodePtr searchTreeHelper(NodePtr node, int key) 
	{
		if (node == TNULL || key == node->data) 
		{
			return node;
		}

		if (key < node->data) 
		{
			return searchTreeHelper(node->left, key);
		}
		return searchTreeHelper(node->right, key);
	}

	void fixDelete(NodePtr x) 
	{
		NodePtr s;
		while (x != root && x->color == 0) 
		{
			if (x == x->parent->left) 
			{
				s = x->parent->right;
				if (s->color == 1) 
				{
					s->color = 0;
					x->parent->color = 1;
					leftRotate(x->parent);
					s = x->parent->right;
				}

				if (s->left->color == 0 && s->right->color == 0) 
				{
					s->color = 1;
					x = x->parent;
				}
				else {
					if (s->right->color == 0) 
					{
						s->left->color = 0;
						s->color = 1;
						rightRotate(s);
						s = x->parent->right;
					}
					s->color = x->parent->color;
					x->parent->color = 0;
					s->right->color = 0;
					leftRotate(x->parent);
					x = root;
				}
			}
			else {
				s = x->parent->left;
				if (s->color == 1) 
				{
					s->color = 0;
					x->parent->color = 1;
					rightRotate(x->parent);
					s = x->parent->left;
				}

				if (s->right->color == 0 && s->right->color == 0) 
				{
					s->color = 1;
					x = x->parent;
				}
				else {
					if (s->left->color == 0) 
					{
						s->right->color = 0;
						s->color = 1;
						leftRotate(s);
						s = x->parent->left;
					}
					s->color = x->parent->color;
					x->parent->color = 0;
					s->left->color = 0;
					rightRotate(x->parent);
					x = root;
				}
			}
		}
		x->color = 0;
	}


	void rbTransplant(NodePtr u, NodePtr v) 
	{
		if (u->parent == nullptr) 
		{
			root = v;
		}
		else if (u == u->parent->left) 
		{
			u->parent->left = v;
		}
		else 
		{
			u->parent->right = v;
		}
		v->parent = u->parent;
	}

	void deleteNodeHelper(NodePtr node, int key) 
	{
		NodePtr z = TNULL;
		NodePtr x, y;
		while (node != TNULL) 
		{
			if (node->data == key) 
			{
				z = node;
			}

			if (node->data <= key) 
			{
				node = node->right;
			}
			else 
			{
				node = node->left;
			}
		}

		if (z == TNULL) 
		{
			cout << "Couldn't find key in the tree" << endl;
			return;
		}

		y = z;
		int y_original_color = y->color;
		if (z->left == TNULL) 
		{
			x = z->right;
			rbTransplant(z, z->right);
		}
		else if (z->right == TNULL) 
		{
			x = z->left;
			rbTransplant(z, z->left);
		}
		else 
		{
			y = minimum(z->right);
			y_original_color = y->color;
			x = y->right;
			if (y->parent == z) 
			{
				x->parent = y;
			}
			else 
			{
				rbTransplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}

			rbTransplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}
		delete z;
		if (y_original_color == 0) 
		{
			fixDelete(x);
		}
	}

	void fixInsert(NodePtr k) 
	{
		NodePtr u;
		while (k->parent->color == 1) 
		{
			if (k->parent == k->parent->parent->right) 
			{
				u = k->parent->parent->left; 
				if (u->color == 1) 
				{
					u->color = 0;
					k->parent->color = 0;
					k->parent->parent->color = 1;
					k = k->parent->parent;
				}
				else {
					if (k == k->parent->left) 
					{
						k = k->parent;
						rightRotate(k);
					}
					k->parent->color = 0;
					k->parent->parent->color = 1;
					leftRotate(k->parent->parent);
				}
			}
			else {
				u = k->parent->parent->right;

				if (u->color == 1) 
				{
					u->color = 0;
					k->parent->color = 0;
					k->parent->parent->color = 1;
					k = k->parent->parent;
				}
				else 
				{
					if (k == k->parent->right) 
					{
						k = k->parent;
						leftRotate(k);
					}
					k->parent->color = 0;
					k->parent->parent->color = 1;
					rightRotate(k->parent->parent);
				}
			}
			if (k == root) 
			{
				break;
			}
		}
		root->color = 0;
	}

	void printHelper(NodePtr root, string indent, bool last) 
	{
		if (root != TNULL) 
		{
			cout << indent;
			if (last) 
			{
				cout << "R----";
				indent += "     ";
			}
			else 
			{
				cout << "L----";
				indent += "|    ";
			}

			string sColor = root->color ? "RED" : "BLACK";
			cout << root->data << "(" << sColor << ")" << endl;
			printHelper(root->left, indent, false);
			printHelper(root->right, indent, true);
		}
	}

public:
	RBTree() 
	{
		TNULL = new Node;
		TNULL->color = 0;
		TNULL->left = nullptr;
		TNULL->right = nullptr;
		root = TNULL;
	}

	void preorder() 
	{
		preOrderHelper(this->root);
	}

	void inorder() 
	{
		inOrderHelper(this->root);
	}

	void postorder() 
	{
		postOrderHelper(this->root);
	}

	NodePtr searchTree(int k) 
	{
		return searchTreeHelper(this->root, k);
	}

	NodePtr minimum(NodePtr node) 
	{
		while (node->left != TNULL) 
		{
			node = node->left;
		}
		return node;
	}

	NodePtr maximum(NodePtr node) 
	{
		while (node->right != TNULL) 
		{
			node = node->right;
		}
		return node;
	}

	NodePtr successor(NodePtr x) 
	{
		if (x->right != TNULL) 
		{
			return minimum(x->right);
		}

		NodePtr y = x->parent;
		while (y != TNULL && x == y->right) 
		{
			x = y;
			y = y->parent;
		}
		return y;
	}

	NodePtr predecessor(NodePtr x) 
	{
		if (x->left != TNULL) 
		{
			return maximum(x->left);
		}

		NodePtr y = x->parent;
		while (y != TNULL && x == y->left) 
		{
			x = y;
			y = y->parent;
		}

		return y;
	}

	void leftRotate(NodePtr x) 
	{
		NodePtr y = x->right;
		x->right = y->left;
		if (y->left != TNULL) 
		{
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) 
		{
			this->root = y;
		}
		else if (x == x->parent->left) 
		{
			x->parent->left = y;
		}
		else {
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}

	void rightRotate(NodePtr x) 
	{
		NodePtr y = x->left;
		x->left = y->right;
		if (y->right != TNULL) 
		{
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) 
		{
			this->root = y;
		}
		else if (x == x->parent->right) 
		{
			x->parent->right = y;
		}
		else 
		{
			x->parent->left = y;
		}
		y->right = x;
		x->parent = y;
	}

	void insert(int key) 
	{
		NodePtr node = new Node;
		node->parent = nullptr;
		node->data = key;
		node->left = TNULL;
		node->right = TNULL;
		node->color = 1; 

		NodePtr y = nullptr;
		NodePtr x = this->root;

		while (x != TNULL) 
		{
			y = x;
			if (node->data < x->data) 
			{
				x = x->left;
			}
			else 
			{
				x = x->right;
			}
		}

		node->parent = y;
		if (y == nullptr) 
		{
			root = node;
		}
		else if (node->data < y->data) 
		{
			y->left = node;
		}
		else 
		{
			y->right = node;
		}

		if (node->parent == nullptr) 
		{
			node->color = 0;
			return;
		}

		if (node->parent->parent == nullptr) 
		{
			return;
		}

		fixInsert(node);
	}

	NodePtr getRoot() 
	{
		return this->root;
	}

	void deleteNode(int data) 
	{
		deleteNodeHelper(this->root, data);
	}

	void prettyPrint() 
	{
		if (root) 
		{
			printHelper(this->root, "", true);
		}
	}

};

int main() 
{
	RBTree NewTree;
	NewTree.insert(2);
	NewTree.prettyPrint();
	NewTree.insert(4);
	NewTree.prettyPrint();
	NewTree.insert(8);
	NewTree.prettyPrint();
	NewTree.insert(16);
	NewTree.prettyPrint();
	NewTree.insert(32);
	NewTree.prettyPrint();
	NewTree.insert(64);
	NewTree.prettyPrint();
	NewTree.insert(128);
	NewTree.prettyPrint();
	NewTree.insert(256);
	NewTree.prettyPrint();
	NewTree.insert(512);
	NewTree.prettyPrint();
	NewTree.insert(1024);
	NewTree.prettyPrint();
	NewTree.insert(3);
	NewTree.prettyPrint();
	NewTree.insert(9);
	NewTree.prettyPrint();
	NewTree.insert(27);
	NewTree.prettyPrint();
	NewTree.insert(81);
	NewTree.prettyPrint();
	NewTree.insert(243);
	NewTree.prettyPrint();
	NewTree.insert(729);
	NewTree.prettyPrint();
	NewTree.insert(4);
	NewTree.prettyPrint();
	NewTree.insert(16);
	NewTree.prettyPrint();
	NewTree.insert(64);
	NewTree.prettyPrint();
	NewTree.insert(256);
	NewTree.prettyPrint();
	NewTree.insert(1024);
	NewTree.prettyPrint();
	NewTree.insert(5);
	NewTree.prettyPrint();
	NewTree.insert(25);
	NewTree.prettyPrint();
	NewTree.insert(125);
	NewTree.prettyPrint();
	NewTree.insert(625);
	NewTree.prettyPrint();
	NewTree.insert(1);
	NewTree.prettyPrint();
	NewTree.insert(7);
	NewTree.prettyPrint();
	NewTree.insert(11);
	NewTree.prettyPrint();
	NewTree.insert(13);
	NewTree.prettyPrint();
	NewTree.insert(17);
	NewTree.prettyPrint();
	NewTree.insert(-100);
	NewTree.prettyPrint();
	NewTree.insert(-123);
	NewTree.prettyPrint();
	NewTree.insert(777);
	NewTree.prettyPrint();
	NewTree.insert(666);
	NewTree.prettyPrint();
	NewTree.insert(6);
	NewTree.prettyPrint();
	NewTree.insert(22);
	NewTree.prettyPrint();
	NewTree.insert(-13);
	NewTree.prettyPrint();
	NewTree.insert(-789);
	NewTree.prettyPrint();
	NewTree.insert(1111);
	NewTree.prettyPrint();
	NewTree.insert(1234);
	NewTree.prettyPrint();
	NewTree.insert(321);
	NewTree.prettyPrint();
	NewTree.insert(-654);
	NewTree.prettyPrint();
	NewTree.insert(-223);
	NewTree.prettyPrint();
	NewTree.insert(228);
	NewTree.prettyPrint();
	NewTree.insert(3337);
	NewTree.prettyPrint();
	NewTree.insert(987);
	NewTree.prettyPrint();
	NewTree.insert(765);
	NewTree.prettyPrint();
	NewTree.insert(18);
	NewTree.prettyPrint();
	NewTree.insert(133);
	NewTree.prettyPrint();
	NewTree.insert(62);
	NewTree.prettyPrint();
	return 0;
}