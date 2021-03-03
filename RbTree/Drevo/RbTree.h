#pragma once
#pragma once
#include <iostream>

enum color {RED, BLACK};
template <typename Tkey, typename Tdata>
class RBTree
{
private:
	struct Node 
	{
		Node(Tkey key = 0, Tdata data = 0, Node* parent = nullptr, Node* l = nullptr, Node* r = nullptr, color Color = BLACK)
		{
			this->key = key;
			this->parent = parent;
			this->left = l;
			this->right = r;
			this->Color = Color;
			this->data = data;
		}
		~Node()
		{
			key = NULL; data = NULL;
			parent = nullptr;
			left = nullptr; right = nullptr;
		}
		color Color = BLACK;
		Tkey key;
		Tdata data;
		Node* left;
		Node* right;
		Node* parent;
	};
	Node* nil = new Node;
	Node* root = nil;
public:
	/////////////////////////////////////////////////////////////////// turns
	void left_turn(Node*);
	void right_turn(Node*);
	/////////////////////////////////////////////////////////////////// insert
	void insert(Tkey, Tdata);
	void restoring_insert(Node*);
	/////////////////////////////////////////////////////////////////// remove
	void replacement(Node*, Node*);
	void remove(Tkey);
	void restoring_remove(Node*);
	/////////////////////////////////////////////////////////////////// clear
	void clear();
	/////////////////////////////////////////////////////////////////// print
	void print_recursion(Node*);
	void print_to_console();
	/////////////////////////////////////////////////////////////////// get keys and get valuse
	size_t get_sizeTree();
	size_t get_size(Node*, size_t);
	Tkey* get_keys();
	Tdata* get_values();
	/////////////////////////////////////////////////////////////////// find
	bool find(Tkey);
	Node* findNode(Tkey key)
	{
		if (root != nil)
		{
			Node* cur = root;
			while (cur != nil)
			{
				if (key == cur->key)
					return cur;
				if (key > cur->key)
					cur = cur->right;
				else
					cur = cur->left;
			}
		}
		else return nil;
	};
	/////////////////////////////////////////////////////////////////// max/min
	Node* MAXNode(Node* subRoot)
	{
		if (subRoot != nil)
		{
			Node* cur = subRoot;
			while (cur->right != nil)
			{
				cur = cur->right;
			}
			return cur;
		}
		else return nil;
	};
	Node* MINNode(Node* subRoot)
	{
		if (subRoot != nil)
		{
			Node* cur = subRoot;
			while (cur->left != nil)
			{
				cur = cur->left;
			}
			return cur;
		}
		else return nil;
	};
};


