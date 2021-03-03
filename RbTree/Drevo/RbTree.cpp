#include "RbTree.h";
#include <Windows.h>
#include <iostream>
#include <stack>


using namespace std;
////////////////////////////////////////////////////////////////////////////////////////////////////// TURNS
template <typename Tkey, typename Tdata>
void RBTree<Tkey, Tdata>::left_turn(Node* X)
{
	Node* Y = X->right;
	X->right = Y->left;
	if (Y->left != nil) //2//
	{
		Y->left->parent = X;
	}
	Y->parent = X->parent;
	if (X->parent == nil) //3//
	{
		root = Y;
	}
	else if (X == X->parent->left) //4//
	{
		X->parent->left = Y;
	}
	else //5//
	{
		X->parent->right = Y;
	}
	Y->left = X;
	X->parent = Y;
}
template <typename Tkey, typename Tdata>
void RBTree<Tkey, Tdata>::right_turn(Node* Y)
{
	Node* X = Y->left;
	Y->left = X->right;

	if (X->right != nil)
	{
		X->right->parent = Y;
	}
	X->parent = Y->parent;

	if (Y->parent == nil)
	{
		root = X;
	}
	else if (Y == Y->parent->right)
	{
		Y->parent->right = X;
	}
	else
	{
		Y->parent->left = X;
	}
	X->right = Y;
	Y->parent = X;
}
////////////////////////////////////////////////////////////////////////////////////////////////////// INSERT
template <typename Tkey, typename Tdata>
void RBTree<Tkey, Tdata>::insert(Tkey key, Tdata data)
{
	if (!find(key))
	{
		if (root == nil)
		{
			root = new Node;
			root->left = nil;
			root->right = nil;
			root->parent = nil;
			root->key = key;
			root->data = data;
			root->Color = BLACK;
			restoring_insert(root);
		}
		else
		{
			Node* cur = root;
			Node* newNode = new Node;
			while (cur != nil)
			{
				if (key >= cur->key) // right subtree
				{
					if (cur->right != nil)
					{
						cur = cur->right;
					}
					else if (cur->right == nil) // if nil, then add
					{
						cur->right = newNode;
						newNode->parent = cur;
						newNode->key = key;
						newNode->data = data;
						newNode->Color = RED; // new Node - RED
						newNode->left = nil;
						newNode->right = nil;
						cur = nil;
					};
				}
				else if (key < cur->key) // left subtree
				{
					if (cur->left != nil)
					{
						cur = cur->left;
					}
					else if (cur->left == nil)
					{
						cur->left = newNode;
						newNode->parent = cur;
						newNode->key = key;
						newNode->data = data;
						newNode->Color = RED;

						newNode->left = nil;
						newNode->right = nil;
						cur = nil;
					}
				}
			}
			restoring_insert(newNode);
		}
	}
}
template <typename Tkey, typename Tdata>
void RBTree<Tkey, Tdata>::restoring_insert(Node* newNode)
{
	Node* P = nil; // parent
	Node* GP = nil; // grand parent
	Node* U = nil; // uncle
	if (newNode == root)////////////////////////////////////////////////////////////////////// situation1 // ROOT
	{
		newNode->Color = BLACK;
	}
	else
	{ // Node != root => Node has a parent
		if (newNode->parent->Color == BLACK) ///////////////////////////////////////////////// sitiation2 // OKAY	
		{
			return;
		}
		else
		{
			if (newNode != root) //////////////////////////////////////////////////////////// found P / GP / U ///
			{
				P = newNode->parent;
				if (P->parent != nil)
				{
					GP = P->parent;
					if (P == GP->left) U = GP->right;
					else if (P == GP->right) U = GP->left;
				}
			}

			if ((U != nil) && (U->Color == RED) && (GP->Color == BLACK))///////////////////// sitiation3
			{ // parent - RED
				P->Color = BLACK;
				U->Color = BLACK;
				GP->Color = RED;
				restoring_insert(GP);
			}
			else
			{
				if ((newNode == P->right) && (P == GP->left))//////////////////////////////// sitiation4
				{
					left_turn(P);
					newNode = newNode->left;
					P = newNode->parent;
					GP = P->parent;
				}
				else if ((newNode == P->left) && (P == GP->right))
				{
					right_turn(P);
					newNode = newNode->right;
					P = newNode->parent;
					GP = P->parent;
				}
				//////////////////////////////////////////////////////////////////////////// situation5
				P->Color = BLACK;
				GP->Color = RED;
				if ((newNode == P->left) && (P == GP->left))
				{
					right_turn(GP);
				}
				else if ((newNode == P->right) && (P == GP->right))
				{
					left_turn(GP);
				}
			}
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////// REMOVE
template <typename Tkey, typename Tdata>
void RBTree<Tkey, Tdata>::replacement(Node* parent, Node* child)
{
	if (parent == root)
	{
		root = child;
	}
	else if (parent == parent->parent->left)
	{
		parent->parent->left = child;
	}
	else
	{
		parent->parent->right = child;
	}
	child->parent = parent->parent;
}
template <typename Tkey, typename Tdata>
void RBTree<Tkey, Tdata>::remove(Tkey key)
{
	if (find(key))
	{
		Node* z = findNode(key);
		Node* x;
		Node* y = z;
		color OriginalColor = y->Color;

		if (z->right == nil)
		{
			x = z->left;
			replacement(z, z->left);
		}
		else if (z->left == nil)
		{
			x = z->right;
			replacement(z, z->right); 
		}
		else
		{
			y = MINNode(z->right); // or Max left Node
			OriginalColor = y->Color;
			x = y->right;

			if (y->parent == z)
			{
				x->parent = y;
			}
			else
			{
				replacement(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}
			replacement(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->Color = z->Color;
		}

		if (OriginalColor == BLACK)
		{
			restoring_remove(x);
		}
		delete(z);
	}
}
template <typename Tkey, typename Tdata>
void RBTree<Tkey, Tdata>::restoring_remove(Node* x)
{
	Node* w; // - brother
	while ((x != root) && (x->Color == BLACK))
	{
		if (x == x->parent->left)
		{
			w = x->parent->right;
			// case 1
			if (w->Color == RED) // Brother - RED
			{
				w->Color = BLACK;
				x->parent->Color = RED;
				left_turn(x->parent);
				w = x->parent->right;
			}
			// case 2
			if (w->left->Color == BLACK && w->right->Color == BLACK)
			{
				w->Color = RED;
				x = x->parent;
			}
			// case 3
			else if (w->right->Color == BLACK)
			{
				w->left->Color = BLACK;
				w->Color = RED;
				right_turn(w);
				w = x->parent->right;
			}
			// case 4
			else
			{
				w->Color = x->parent->Color;
				x->parent->Color = BLACK;
				w->right->Color = BLACK;
				left_turn(x->parent);
				x = root;
			}
		}
		else if(x == x->parent->right)
		{
			w = x->parent->left;
			// case 1
			if (w->Color == RED)
			{
				w->Color = BLACK;
				x->parent->Color = RED;
				right_turn(x->parent);
				w = x->parent->left;
			}
			// case 2
			if (w->right->Color == BLACK && w->left->Color == BLACK)
			{
				w->Color = RED;
				x = x->parent;
			}
			// case 3
			else if (w->left->Color == BLACK)
			{
				w->right->Color = BLACK;
				w->Color = RED;
				left_turn(w);
				w = x->parent->left;
			}
			// case 4
			else
			{
				w->Color = x->parent->Color;
				x->parent->Color = BLACK;
				w->left->Color = BLACK;
				right_turn(x->parent);
				x = root;
			}
		}
	}
	x->Color = BLACK;
}
////////////////////////////////////////////////////////////////////////////////////////////////////// CLEAR
template <typename Tkey, typename Tdata>
void RBTree<Tkey, Tdata>::clear()
{
	cout << endl << " Clear...";
	while (root != nil)
	{
		remove(root->key);
	}
	cout << endl << " The tree is empty.";
}
////////////////////////////////////////////////////////////////////////////////////////////////////// PRINT
template <typename Tkey, typename Tdata>
void RBTree<Tkey, Tdata>::print_recursion(Node* cur)
{
	/////////////////////////////////////////////////////////////////////////////////////////// Colors
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (cur->Color == RED) SetConsoleTextAttribute(hConsole, (WORD)((4 << 4) | 0)); // color text Node RED
	else SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15)); // color text Node BLACK
	//////////////////////////////////////////////////////////////////////////////////////////////////

	cout << "("  << cur->data << ")" << cur->key;
	if (cur->left != nil) print_recursion(cur->left);
	if (cur->right != nil) print_recursion(cur->right);

	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
}
template <typename Tkey, typename Tdata>
void RBTree<Tkey, Tdata>::print_to_console() 
{ // obhod v depth
	cout << endl << " Drevo:";
	if (root != nil)
	{
		print_recursion(root);
		cout << " Root: " << root->key;
	}
	else cout << endl << " Empty ";
};
////////////////////////////////////////////////////////////////////////////////////////////////////// GET_KEYS and GET_VALUSE
//////////////////////////////////////////////////////////////get_size
template <typename Tkey, typename Tdata>
size_t RBTree<Tkey, Tdata>::get_size(Node* cur, size_t size)
{
	if (cur == nil) return 0;
	else
	{
		if (cur == root) size = 1;
		if (cur->left != nil)
		{
			size++;
			size = get_size(cur->left, size);
		}
		if (cur->right != nil)
		{
			size++;
			size = get_size(cur->right, size);
		}
		return size;
	}
}
template <typename Tkey, typename Tdata>
size_t RBTree<Tkey, Tdata>::get_sizeTree()
{
	return get_size(root, 0);
}
//////////////////////////////////////////////////////////////get_keys
template <typename Tkey, typename Tdata>
Tkey* RBTree<Tkey, Tdata>::get_keys()
{
	if (root != nil)
	{
		Tkey* Array = new Tkey[get_sizeTree()];
		Node* cur = root;
		stack<Node*> Stack;
		Stack.push(cur);
		for (int i = 0; i < get_sizeTree(); i++)
		{
			cur = Stack.top();
			Stack.pop();
			Array[i] = cur->key;
			if (cur->right != nil)
				Stack.push(cur->right);
			if (cur->left != nil)
				Stack.push(cur->left);
		}
		return Array;
	}
	else return nullptr;
}
//////////////////////////////////////////////////////////////get_values
template <typename Tkey, typename Tdata>
Tdata* RBTree<Tkey, Tdata>::get_values()
{
	if (root != nil)
	{
		Tdata* Array = new Tdata[get_sizeTree()];
		Node* cur = root;
		stack<Node*> Stack;
		Stack.push(root);
		for (int i = 0; i < get_sizeTree(); i++)
		{
			cur = Stack.top();
			Stack.pop();
			Array[i] = cur->data;
			if (cur->right != nil)
				Stack.push(cur->right);
			if (cur->left != nil)
				Stack.push(cur->left);
		}
		return Array;
	}
	else return nullptr;
}
////////////////////////////////////////////////////////////////////////////////////////////////////// FIND
template <typename Tkey, typename Tdata>
bool RBTree<Tkey, Tdata>::find(Tkey key)
{
	if (root != nil)
	{
		Node* cur = root;
		while (cur != nil)
		{
			if (key == cur->key)
				return true;
			if (key > cur->key)
				cur = cur->right;
			else
				cur = cur->left;
		}
		return false;
	}
	else return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////// THE END
