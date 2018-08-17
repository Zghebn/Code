#include <iostream>
#include <vector>

template <typename T>
class stack
{
private:
	struct stk
	{
		T data;
		stk *prev;
	};
	stk *top;

public:
	stack() {
		top = NULL;
	}

	void push(T data)
	{
		stk *temp = new stk;
		temp->data = data;
		temp->prev = top;
		top = temp;
	}

	T pop()
	{
		if (top == NULL)
			return NULL;
		T temp = top->data;
		stk *topTemp = top->prev;
		delete top;
		top = topTemp;
		return temp;
	}

	T topElem() {
		return top->data;
	}

	bool isEmpty() {
		return top ? false : true;
	}
};

template <typename T>
class queue
{
private:
	struct node
	{
		T val;
		node *next;
		node() :next(NULL) {};
	};
	node *frnt, *rear;
	int len;

public:
	queue()
	{
		frnt = rear = NULL;
		len = 0;
	}

	void in(T elem)
	{
		node *temp = new node;
		temp->val = elem;
		if (rear == NULL)
			rear = temp;
		else
		{
			rear->next = temp;
			rear = temp;
		}
		if (frnt == NULL)
			frnt = temp;
		len++;
	}

	T de()
	{
		if (frnt == NULL)
			return 0;
		T deVal = frnt->val;
		node *temp = frnt;
		frnt = frnt->next;
		if (frnt == NULL)
			rear = NULL;
		delete temp;
		len--;
		return deVal;
	}

	int size() {
		return len;
	}

	bool isEmpty() {
		return len ? false : true;
	}

	T front() {
		return frnt ? frnt->val : NULL;
	}
};
struct node
{
	int val;
	node *left;
	node *right;
};
void createTree(node *&root)
{
	node *&temp = root;
	int data;
	std::cin >> data;
	if (data == -1)
	{
		temp = NULL;
		return;
	}
	temp = new node;
	temp->val = data;

	createTree(temp->left);
	createTree(temp->right);
}

void preOrder(node *root)
{
	node *temp = root;
	if (temp == NULL)
		return;
	std::cout << temp->val << ' ';
	preOrder(temp->left);
	preOrder(temp->right);
}
void iterativePreorder(node *root)
{
	node *temp = root;
	stack<node*> S;
	while (temp || !S.isEmpty())
	{
		while (temp)
		{
			std::cout << temp->val << ' ';
			S.push(temp);
			temp = temp->left;
		}
		if (!S.isEmpty())
		{
			temp = S.pop();
			temp = temp->right;
		}
	}
}

void inOrder(node *root)
{
	node *temp = root;
	if (temp == NULL)
		return;
	inOrder(temp->left);
	std::cout << temp->val << ' ';
	inOrder(temp->right);
}
void iterativeInorder(node *root)
{
	node *temp = root;
	stack<node*> S;
	while (temp || S.isEmpty() == false)
	{
		while (temp)
		{
			S.push(temp);
			temp = temp->left;
		}
		if (S.isEmpty() == false)
		{
			temp = S.pop();
			std::cout << temp->val;
			temp = temp->right;
		}
	}
	std::cout << std::endl;
}

void postOrder(node *root)
{
	node *temp = root;
	if (temp == NULL)
		return;
	postOrder(temp->left);
	postOrder(temp->right);
	std::cout << temp->val << ' ';
}
void iterativePostorder(node *root)
{
	if (!root)
		return;
	stack<node*> S;
	node *cur = root, *visited = NULL;
	while (cur || S.isEmpty() == false)
	{
		while (cur)
		{
			S.push(cur);
			cur = cur->left;
		}
		cur = S.topElem();
		if (cur->right == NULL || cur->right == visited)
		{
			S.pop();
			std::cout << cur->val << ' ';
			visited = cur;
			cur = NULL;
		}
		else
		{
			cur = cur->right;
		}
	}
}

void levelOrder(node *root)
{
	if (!root)
		return;
	queue<node*> q;
	q.in(root);
	while (q.isEmpty() == false)
	{
		node *temp = q.de();
		std::cout << temp->val << ' ';
		if (temp->left)
			q.in(temp->left);
		if (temp->right)
			q.in(temp->right);
	}
}
std::vector<std::vector<int>> levelOrder2(node* root)
{	// Unfinished
	std::vector<std::vector<int>> v;
	std::vector<int> sub;
	if (!root)
		return v;
	queue<node*> q;
	q.in(root);
	node *temp, *right = root, *prev;
	while (q.isEmpty() == false)
	{
		temp = q.de();
		sub.push_back(temp->val);
		if (right == temp)
		{
			v.push_back(sub);
			sub.clear();
			if (right->right)
				right = right->right;
			else if (right->left)
				right = right->left;
			else if (prev->right)
				right = prev->right;
			else
				right = right->left;
		}
		if (temp->left)
			q.in(temp->left);
		if (temp->right)
			q.in(temp->right);
		prev = temp;
	}
	return v;
}

int main()
{
	node *root;
	createTree(root);	// 1 2 4 8 -1 -1 9 -1 -1 5 10 -1 -1 11 -1 -1 3 6 12 -1 -1 13 -1 -1 7 14 -1 -1 15 -1 -1
	levelOrder(root);
	return 0;
}