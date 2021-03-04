#pragma once
template <class T>
class Stack
{
private:
	struct Node
	{
		Node(T data, Node* prev = nullptr, Node* next = nullptr)
		{
			this->data = data;
			this->prev = prev;
			this->next = next;
		};
		Node() {};
		T data;
		Node* prev;
		Node* next;
	};
	size_t sizeStack;
	Node* head;
	Node* tail;
public:
	Stack()
	{
		tail = nullptr;
		head = nullptr;
		sizeStack = 0;
	}
	~Stack()
	{
		tail = nullptr;
		head = nullptr;
		sizeStack = 0;
	}
	void push(T data)
	{
		if (isEmpte())
		{
			head = new Node;
			head->data = data;
			tail = head;
		}
		else
		{
			tail->next = new Node;
			tail->next->prev = tail;
			tail = tail->next;
			tail->data = data;
		}
		sizeStack++;
	}
	T top()
	{
		if (isEmpte()) return NULL;
		else return tail->data;
	}
	void pop()
	{
		if (!isEmpte())
		{
			if (sizeStack == 1)
			{
				delete tail;
			}
			else
			{
				Node* cur = tail;
				cur->prev->next = NULL;
				tail = cur->prev;
				delete cur;
				sizeStack--;
			}
		}
	}
	bool isEmpte()
	{
		if (sizeStack == 0) return true;
		else return false;
	}
};
