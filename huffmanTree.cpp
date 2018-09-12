#include <iostream>
#include <vector>
#include <string>
using std::vector;
using std::string;

template <typename T>
class stack
{
private:
	struct stackNode
	{
		T val;
		stackNode *next = NULL;
	};

	stackNode *topElem = NULL;

public:
	void push(T data)
	{
		stackNode *temp = new stackNode;
		temp->val = data;
		temp->next = topElem;
		topElem = temp;
	}

	T pop()
	{
		if (!topElem)
			return 0;
		stackNode *temp = topElem;
		T tempVal = temp->val;
		topElem = topElem->next;
		delete temp;
		return tempVal;
	}

	T top() {
		return topElem->val;
	}

	bool empty() {
		return topElem ? false : true;
	}
};

//	To store the characters and their weight
template <typename T>
struct rawHuffmanData
{
	vector<T> weight;
	vector<unsigned char> ch;
};

template<typename T>
class huffmanTree
{
private:
	class huffNode
	{
	public:
		T weight;
		unsigned char ch;
		huffNode *left, *right;

		huffNode()
		{
			weight = 0;
			ch = 0;
			left = right = NULL;
		}
	};

	//	To store the huffman code table
	struct huffmanTable
	{
		unsigned char ch;
		string code;
	};

	huffNode *root;
	vector<huffmanTable> table;

public:
	void create(const rawHuffmanData<T>&);
	void generateTable();
};

template <typename T>
void huffmanTree<T>::create(const rawHuffmanData<T> &raw)
{
	//	Copy raw data into a data vector and huffmanTree::table vector
	vector<huffNode*> data(raw.ch.size());
	for (int i = 0; i < (int)data.size(); i++)
	{
		data[i] = new huffNode;
		data[i]->ch = raw.ch[i];
		//huffmanTable temp = { raw.ch[i], NULL };
		//table.push_back(temp);
		data[i]->weight = raw.weight[i];
	}

	//	InsertionSort data in ascending order
	for (int i = 1; i < (int)data.size(); i++)
	{
		huffNode *key = data[i];
		int j = i - 1;
		while (j >= 0 && data[j]->weight > key->weight)
		{//	with float or double: data[j]->weight - key->weight > 0
			data[j + 1] = data[j];
			--j;
		}
		data[j + 1] = key;
	}

	// Combine 2 nodes and make them tree
	huffNode *min, *n_min;
	while (data.size() > 0)
	{
		min = data[0];
		n_min = data[1];

		// Combine 2 nodes
		huffNode *temp = new huffNode;
		temp->weight = min->weight + n_min->weight;
		temp->left = min;
		temp->right = n_min;

		// Delete used nodes
		data.erase(data.begin());
		data.erase(data.begin());

		// Insert temp into data in ascending order
		if (data.size() > 0)
		{
			for (auto i = data.begin(); i != data.end(); i++)
			{
				if (temp->weight <= (*i)->weight)
				{//	with float and double: temp->weight - (*i)->weight <= 0
					data.insert(i, temp);
					break;
				}
				else if (temp->weight > (*i)->weight && i + 1 == data.end())
				{
					data.insert(data.end(), temp);
					break;
				}
			}
		}
		root = temp;
	}
}

//template <typename T>
typedef int T;
void huffmanTree<T>::generateTable()
{
	int cnt = 0;
	stack<huffNode*> s;
	huffNode *temp = root;

	while (temp || !s.empty())
	{
		while (temp)
		{
			s.push(temp);
			temp = temp->left;
		}
		if (!s.empty())
		{
			temp = s.pop();
			if (!temp->right)
			{
				table.push_back({ temp->ch,"" });
			}
			temp = temp->right;
		}
	}
}

int main()
{
	rawHuffmanData<int> v = { {2,1,3,5,4,7,6},
						{'a','b','c','d','e','f','g'} };
	huffmanTree<int> h;
	h.create(v);
	h.generateTable();
	return 0;
}