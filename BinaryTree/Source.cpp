#include <iostream>
#include <ctime>

using namespace std;
using std::cin;
using std::cout;
using std::endl;

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
#ifdef DEBUG
			cout << "Element constructor:\t" << this << endl;
#endif // DEBUG

		}
		~Element()
		{
#ifdef DEBUG
			cout << "Element destructor:\t" << this << endl;
#endif // DEBUG

		}
		friend class Tree;
		friend class UniqueTree;
	}*Root;


	

public:
	Element* getRoot()
	{
		return this->Root;
	}

	Tree(): Root(nullptr)
	{
#ifdef DEBUG
		cout << "Three constructor:\t" << this << endl;
#endif // DEBUG

	}

	Tree(initializer_list<int> il) : Tree()
	{
		for (int i : il) insert(i, Root);
#ifdef DEBUG
		cout << "Tree il constructor:\t" << this << endl;
#endif // DEBUG

	}

	~Tree()
	{
		Clear();
#ifdef DEBUG
		cout << "Tree destructor:\t" << this << endl;
#endif // DEBUG

	}

	void insert(int Data)
	{
		insert(Data, Root);
	}

	int minValue() const
	{
		return minValue(Root);
	}

	int maxValue() const
	{
		return maxValue(Root);
	}

	int Sum() const
	{
		return Sum(Root);
	}

	int Count() const
	{
		return Count(Root);
	}

	double Avg() const
	{
		return Avg(Root);
	}

	void print()const
	{
		print(Root);
		cout << endl;
	}

	void Clear()
	{
		Clear(Root);
		Root = nullptr;
	}

	int Depth() const
	{
		return Depth(Root);
	}

	void Measure(clock_t& start, const char* name)
	{
		clock_t point = clock();
		cout << name << " work time: " << double(point - start) / CLOCKS_PER_SEC << " sec." << endl;
		start = clock();
	}
	
private:
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr) this->Root = new Element(Data);
		if (Root == nullptr) return;
		if(Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else
		{
			if (Root->pRight == nullptr) Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}

	int minValue(Element* Root) const
	{
		if (this->Root == nullptr) return 0;
		return Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
	}

	int maxValue(Element* Root) const
	{
		if (this->Root == nullptr) return 0;
		return Root->pRight == nullptr ? Root->Data: maxValue(Root->pRight);
	}

	int Sum(Element* Root) const
	{
		if (this->Root == nullptr) return 0;
		return Root == nullptr ? 0 : Sum(Root->pLeft) + Sum(Root->pRight) + Root->Data;
	}

	int Count(Element* Root) const
	{
		return Root == nullptr ? 0 : Count(Root->pLeft) + Count(Root->pRight) + 1;
	}

	double Avg(Element* Root) const
	{
		return (double)Sum() / Count(Root);
	}

	void print(Element* Root) const
	{
		if (Root == nullptr) return;
		print(Root->pLeft);
		cout << Root->Data << "\t";
		print(Root->pRight);
	}

	void Clear(Element* Root)
	{
		if (Root == nullptr) return;
		Clear(Root->pLeft);
		Clear(Root->pRight);
		delete Root;
	}

	/*void Erase(int Data, Element* Root)
	{
		if (Root == nullptr) return;
		Erase(Data, Root->pLeft);
		if(Root->pLeft->Data == Data)
		{
			Element* Erased = Root->pLeft;
			Root->pLeft->pRight->pLeft = Root->pLeft->pLeft;
			Root->pLeft = Root->pLeft->pRight;
		}
		Erase(Data, Root->pRight);
		delete Root;
	}*/

	int Depth(Element* Root) const
	{
		if (Root == nullptr) return 0;
		int l_depth = Depth(Root->pLeft) + 1;
		int r_depth = Depth(Root->pRight) + 1;
		return l_depth < r_depth ? r_depth : l_depth;
	}

	

};

class UniqueTree: public Tree
{
public:
	void insert(int Data)
	{
		insert(Data, Root);
	}
private:
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr) this->Root = new Element(Data);
		if (Root == nullptr) return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else if (Data > Root->Data)
		{
			if (Root->pRight == nullptr) Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
};


#define BASE_CHECK
//#define RANGE_BASED_FOR_TREE_CHECK
//#define DEPTH_CHECK
void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Enter tree size:\n"; cin >> n;

	Tree tree;
	clock_t start = clock();
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	tree.Measure(start, "insert");
	clock_t end = clock();
	cout << "insert time:\t" << double(end - start)/CLOCKS_PER_SEC << endl;
	//tree.print();

	cout << "Min value in tree:\t" << endl;
	start = clock();
	int min = tree.minValue();
	end = clock();
	cout << min << endl;
	cout << "min time:\t" << double(end - start) / CLOCKS_PER_SEC << endl;
	///////////////////////////////////////
	cout << "Max value in tree:\t";
	start = clock();
	int max = tree.maxValue();
	end = clock();
	cout << max << endl;
	cout << "max time:\t" << double(end - start) / CLOCKS_PER_SEC << endl;
	///////////////////////////////////
	cout << "Sum of tree elements:\t";
	start = clock();
	int sum = tree.Sum();
	end = clock();
	cout << sum << endl;
	cout << "Sum time:\t" << double(end - start) / CLOCKS_PER_SEC << endl;
	///////////////////////////
	cout << "Number of tree elements:\t";
	start = clock();
	int num = tree.Count();
	end = clock();
	cout << num << endl;
	cout << "Count time:\t" << double(end - start) / CLOCKS_PER_SEC << endl;
	//////////////////////////////////////////
	cout << "Arithmetic mean of tree elements:\t";
	start = clock();
	double avg = tree.Avg();
	end = clock();
	cout << avg << endl;
	cout << "Avg time:\t" << double(end - start) / CLOCKS_PER_SEC << endl;
	//////////////////////////////////////////
	cout << "Depth of tree:\t";
	start = clock();
	int depth = tree.Depth();
	end = clock();
	cout << depth << endl;
	cout << "Depth time:\t" << double(end - start) / CLOCKS_PER_SEC << endl;


	UniqueTree u_tree;
	start = clock();
	for (int i = 0; i < n; i++)
	{
		u_tree.insert(rand() % 100);
	}
	u_tree.Measure(start, "insert()");
	//u_tree.print();
	cout << "Min value in unique tree:\t" << u_tree.minValue() << endl;
	u_tree.Measure(start, "minValue()");
	cout << "Max value in unique tree:\t" << u_tree.maxValue() << endl;
	u_tree.Measure(start, "maxValue()");
	cout << "Sum of unique tree elements:\t" << u_tree.Sum() << endl;
	u_tree.Measure(start, "Sum()");
	cout << "Number of unique tree elements:\t" << u_tree.Count() << endl;
	u_tree.Measure(start, "Count()");
	cout << "Arithmetic mean of unique tree elements:\t" << u_tree.Avg() << endl;
	u_tree.Measure(start, "Avg()");
	cout << "Depth of tree:\t" << u_tree.Depth() << endl;
	u_tree.Measure(start, "Depth()");

#endif // BASE_CHECK

#ifdef RANGE_BASED_FOR_TREE_CHECK
	Tree tree = {0, 1, 1, 2, 3, 5};
	tree.print();
#endif // RANGE_BASED_FOR_TREE_CHECK

#ifdef DEPTH_CHECK
	Tree tree = { 50, 25, 75, 16, 32, 64, 90 };
	tree.print();
	cout << "Depth of tree:\t" << tree.Depth() << endl;
#endif // DEPTH_CHECK

}