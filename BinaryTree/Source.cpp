#include <iostream>

using namespace std;

class Tree
{
protected:
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr) : Data(Data), pLeft(pLeft), pRight(pRight)
		{
			cout << "Element constructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "Element destructor:\t" << this << endl;
		}
		friend class Tree;
		friend class UniqueTree;
		friend class Iterator;
	}*Root, *Temp;
	//class BaseIterator
	//{
	//	Element* Temp;
	//public:
	//	BaseIterator(Element* Temp = nullptr): Temp(Temp)
	//	{
	//		cout << "BIterator constructor:\t" << this << endl;
	//	}
	//	~BaseIterator()
	//	{
	//		cout << "Iterator destructor:\t" << this << endl;
	//	}
	//	BaseIterator& operator++()
	//	{
	//		Temp = Temp->pRight;
	//		return *this;
	//	}
	//	bool operator==(const BaseIterator& other)
	//	{
	//		return this->Temp == other.Temp;
	//	}
	//	bool operator!=(const BaseIterator& other)
	//	{
	//		return this->Temp != other.Temp;
	//	}
	//	int operator*()
	//	{
	//		return Temp->Data;
	//	}
	//	friend class Tree;
	//};

public:
	Element* getRoot()
	{
		return this->Root;
	}

	//BaseIterator begin()
	//{
	//	return Root;
	//}

	//BaseIterator end()
	//{
	//	return nullptr;
	//}

	Tree(): Root(nullptr)
	{
		cout << "Three constructor:\t" << this << endl;
	}

	Tree(initializer_list<int> il) : Tree()
	{
		for (const int* it = il.begin(); it != il.end(); it++) insert(*it);
		cout << "Tree il constructor:\t" << this << endl;
	}

	~Tree()
	{

		cout << "Tree destructor:\t" << this << endl;
	}

	void insert(int Data)
	{
		if (this->Root == nullptr)
		{
			this->Root = new Element(Data);
			Temp = this->Root;
			return;
		}
		if (Temp == nullptr) return;
		if(Data < Temp->Data)
		{
			if (Temp->pLeft == nullptr)Temp->pLeft = new Element(Data), Temp = this->Root;
			else Temp = Temp->pLeft, insert(Data);
		}
		else
		{
			if (Temp->pRight == nullptr) Temp->pRight = new Element(Data), Temp = this->Root;
			else Temp = Temp->pRight, insert(Data);
		}
	}

	/*void erase(int Data)
	{
		if (this->Root == nullptr)
		{
			return;
		}
		if (Data < Iterator->Data)
		{
			if (Iterator->pLeft == nullptr) return;
			else Iterator = Iterator->pLeft, erase(Data);
		}
		else if (Data > Iterator->Data)
		{
			if (Iterator->pRight == nullptr) return;
			else Iterator = Iterator->pRight, erase(Data);
		}
		else
		{
			delete Iterator;
			Iterator = this->Root;
			return;
		}
	}*/

	int minValue()
	{
		int min;
		if (Temp == nullptr) return 0;
		if(Temp->pLeft == nullptr) 
		{
			min = Temp->Data;
			Temp = this->Root;
			return min;
		}
		else
		{
			Temp = Temp->pLeft;
			return minValue();
		}
	}

	int maxValue()
	{
		int max;
		if (Temp == nullptr) return 0;
		if (Temp->pRight == nullptr)
		{
			max = Temp->Data;
			Temp = this->Root;
			return max;
		}
		else
		{
			Temp = Temp->pRight;
			return maxValue();
		}
	}

	int Sum()
	{
		int sum = 0;
		if (Temp == nullptr) return sum;
		else
		{
			Temp->pLeft;
			sum += Sum();
			Temp->pRight;
			sum += Sum();
			sum += Temp->Data;
			Temp = this->Root;
			return sum;
		}
		//return Root == nullptr ? 0 : Sum(Root->pLeft) + Sum(Root->pRight) + Root->Data;
	}

	int Count(Element* Root)
	{
		return Root == nullptr ? 0 : Count(Root->pLeft) + Count(Root->pRight) + 1;
	}

	double Avg(Element* Root)
	{
		return (double)Sum() / Count(Root);
	}

	void print(Element* Root)
	{
		if (Root == nullptr) return;
		print(Root->pLeft);
		cout << Root->Data << "\t";
		print(Root->pRight);
	}
	friend class Iterator;
};

class UniqueTree: public Tree
{
public:
	void insert(int Data)
	{
		if (this->Root == nullptr)
		{
			this->Root = new Element(Data);
			Temp = this->Root;
			return;
		}
		if (Temp == nullptr) return;
		if (Data < Temp->Data)
		{
			if (Temp->pLeft == nullptr)Temp->pLeft = new Element(Data), Temp = this->Root;
			else Temp = Temp->pLeft, insert(Data);
		}
		else
		{
			if (Temp->pRight == nullptr) Temp->pRight = new Element(Data), Temp = this->Root;
			else Temp = Temp->pRight, insert(Data);
		}
	}
};


#define BASE_CHECK
//#define RANGE_BASED_FOR_TREE_CHECK
void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Enter tree size:\n"; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		int num = rand() % 100;
		cout << num << "\t";
		tree.insert(num);
	}
	tree.print(tree.getRoot());
	cout << endl;
	cout << "Min value in tree:\t" << tree.minValue() << endl;
	cout << "Max value in tree:\t" << tree.maxValue() << endl;
	cout << "Sum of tree elements:\t" << tree.Sum() << endl;
	cout << "Number of tree elements:\t" << tree.Count(tree.getRoot()) << endl;
	cout << "Arithmetic mean of tree elements:\t" << tree.Avg(tree.getRoot()) << endl;

	UniqueTree u_tree;
	for (int i = 0; i < n; i++)
	{
		u_tree.insert(rand() % 100);
	}
	u_tree.print(u_tree.getRoot());
	cout << endl;
	cout << "Min value in unique tree:\t" << u_tree.minValue() << endl;
	cout << "Max value in unique tree:\t" << u_tree.maxValue() << endl;
	cout << "Sum of unique tree elements:\t" << u_tree.Sum() << endl;
	cout << "Number of unique tree elements:\t" << u_tree.Count(u_tree.getRoot()) << endl;
	cout << "Arithmetic mean of unique tree elements:\t" << u_tree.Avg(u_tree.getRoot()) << endl;
#endif // BASE_CHECK

#ifdef RANGE_BASED_FOR_TREE_CHECK
	Tree tree = {10, 12, 9, 3, 4, 56};
	tree.print(tree.getRoot());
	tree.erase(10);
	tree.print(tree.getRoot());
#endif // RANGE_BASED_FOR_TREE_CHECK

}