#include "BinaryTree.h"

//-----------------------------------------Tree-----------------------------------------//
//----------------------------------------Element---------------------------------------//
template <typename T> Tree<T>::Element::Element(T Data, Element* pLeft, Element* pRight) : Data(Data), pLeft(pLeft), pRight(pRight)
{
#ifdef DEBUG
	cout << "Element constructor:\t" << this << endl;
#endif // DEBUG

}
template <typename T> Tree<T>::Element::~Element()
{
#ifdef DEBUG
	cout << "Element destructor:\t" << this << endl;
#endif // DEBUG

}
//----------------------------------------Element---------------------------------------//\
//-----------------------------------------Tree-----------------------------------------//
template <typename T> typename Tree<T>::Element* Tree<T>::getRoot()
{
	return this->Root;
}

template <typename T> Tree<T>::Tree() : Root(nullptr)
{
#ifdef DEBUG
	cout << "Three constructor:\t" << this << endl;
#endif // DEBUG

}

template <typename T> Tree<T>::Tree(initializer_list<T> il) : Tree()
{
	for (T i : il) insert(i, Root);
#ifdef DEBUG
	cout << "Tree il constructor:\t" << this << endl;
#endif // DEBUG

}

template <typename T> Tree<T>::~Tree()
{
	Clear();
#ifdef DEBUG
	cout << "Tree destructor:\t" << this << endl;
#endif // DEBUG

}

template <typename T> void Tree<T>::insert(T Data)
{
	insert(Data, Root);
}

template <typename T> T Tree<T>::minValue() const
{
	return minValue(Root);
}

template <typename T> T Tree<T>::maxValue() const
{
	return maxValue(Root);
}

template <typename T> T Tree<T>::Sum() const
{
	return Sum(Root);
}

template <typename T> T Tree<T>::Count() const
{
	return Count(Root);
}

template <typename T> double Tree<T>::Avg() const
{
	return Avg(Root);
}

template <typename T> void Tree<T>::print()const
{
	print(Root);
	cout << endl;
}

template <typename T> void Tree<T>::print_tree() const
{
	int Depth = 0;
	print_tree(Depth, Root);
}

template <typename T> void Tree<T>::depth_print(int depth) const
{
	depth_print(Root, depth, 28);
}

template <typename T> void Tree<T>::tree_print() const
{
	tree_print(Root, 28);
}

template <typename T>void Tree<T>::Clear()
{
	Clear(Root);
	Root = nullptr;
}

template <typename T> int Tree<T>::Depth() const
{
	return Depth(Root);
}

template <typename T>void Tree<T>::Erase(T Data)
{
	Erase(Data, Root);
}

template <typename T> void Tree<T>::balance()
{
	balance(Root);
}

template <typename T>void Tree<T>::insert(T Data, Element* Root)
{
	if (this->Root == nullptr) this->Root = new Element(Data);
	if (Root == nullptr) return;
	if (Data < Root->Data)
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

template <typename T>void Tree<T>::Erase(T Data, Element*& Root)
{
	if (Root == nullptr) return;
	Erase(Data, Root->pLeft);
	Erase(Data, Root->pRight);
	if (Data == Root->Data)
	{
		if (Root->pLeft == Root->pRight)
		{
			delete Root;
			Root = nullptr;
		}
		else
		{
			if (Count(Root->pLeft) > Count(Root->pRight))
			{
				Root->Data = maxValue(Root->pLeft);
				Erase(maxValue(Root->pLeft), Root->pLeft);
			}
			else
			{
				Root->Data = minValue(Root->pRight);
				Erase(minValue(Root->pRight), Root->pRight);
			}
		}
	}
}

template <typename T> T Tree<T>::minValue(Element* Root) const
{
	if (this->Root == nullptr) return 0;
	return Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
}

template <typename T> T Tree<T>::maxValue(Element* Root) const
{
	if (this->Root == nullptr) return 0;
	return Root->pRight == nullptr ? Root->Data : maxValue(Root->pRight);
}

template <typename T> T Tree<T>::Sum(Element* Root) const
{
	if (this->Root == nullptr) return 0;
	return Root == nullptr ? 0 : Sum(Root->pLeft) + Sum(Root->pRight) + Root->Data;
}

template <typename T> T Tree<T>::Count(Element* Root) const
{
	return Root == nullptr ? 0 : Count(Root->pLeft) + Count(Root->pRight) + 1;
}

template <typename T> double Tree<T>::Avg(Element* Root) const
{
	return (double)Sum() / Count(Root);
}

template <typename T> void Tree<T>::print(Element* Root) const
{
	if (Root == nullptr) return;
	print(Root->pLeft);
	cout << Root->Data << "\t";
	print(Root->pRight);
}

template <typename T> void Tree<T>::depth_print(Element* Root, int depth, int width) const
{
	//adjusted_depth - заданная глубина
	if (Root == nullptr)
	{

		return;
	}
	if (depth == 0)
	{
		cout.width(width);
		cout << Root->Data;
		cout.width(width);
		cout << "";
	}
	depth_print(Root->pLeft, depth - 1, width);
	depth_print(Root->pRight, depth - 1, width);
}

template <typename T> void Tree<T>::tree_print(Element* Root, int width, int depth) const
{
	if (Root == nullptr) return;
	if (depth > this->Depth()) return;
	depth_print(Root, depth, width);
	cout << endl;
	cout << endl;
	tree_print(Root, width / 2, depth + 1);
}

template <typename T> void Tree<T>::print_tree(int Depth, Element* Root) const
{
	if (Root == nullptr) return;
	print_tree(Depth + 1, Root->pLeft);
	for (int i = 1; i < Depth; i++)
	{
		cout << "\t";
	}
	if (Root != this->Root)cout << "|-------";
	cout << Root->Data << endl;
	print_tree(Depth + 1, Root->pRight);
}

/*template <typename T> void Tree<T>::balance(Element*& Root)
{
	if (Root == nullptr) return;
	if (abs(Count(Root->pLeft) - Count(Root->pRight)) > 1)
	{
		int Data = Root->Data;
		Erase(Root->Data);
		insert(Data);
		balance();
	}
	balance(Root->pLeft);
	balance(Root->pRight);
}*/

template <typename T> void Tree<T>::balance(Element* Root)
{
	if (Root == nullptr) return;
	if (abs(Count(Root->pLeft) - Count(Root->pRight)) < 2) return;
	if (Count(Root->pLeft) < Count(Root->pRight))
	{
		if (Root->pLeft)insert(Root->Data, Root->pLeft);
		else Root->pLeft = new Element(Root->Data);
		Root->Data = minValue(Root->pRight);
		Erase(minValue(Root->pRight), Root->pRight);
		balance(Root);
	}
	else
	{
		if (Root->pRight)insert(Root->Data, Root->pRight);
		else Root->pRight = new Element(Root->Data);
		Root->Data = maxValue(Root->pLeft);
		Erase(maxValue(Root->pLeft), Root->pLeft);
		balance(Root);
	}
	balance(Root->pLeft);
	balance(Root->pRight);
}

template <typename T> void Tree<T>::Clear(Element* Root)
{
	if (Root == nullptr) return;
	Clear(Root->pLeft);
	Clear(Root->pRight);
	delete Root;
}

template <typename T> int Tree<T>::Depth(Element* Root) const
{
	if (Root == nullptr) return 0;
	int l_depth = Depth(Root->pLeft) + 1;
	int r_depth = Depth(Root->pRight) + 1;
	return l_depth < r_depth ? r_depth : l_depth;
}
//-----------------------------------------Tree-----------------------------------------//
//--------------------------------------------------------------------------------------//
//--------------------------------------UniqueTree--------------------------------------//
template <typename T> void UniqueTree<T>::insert(T Data)
{
	insert(Data, Tree<T>::Root);
}

template <typename T> void UniqueTree<T>::insert(T Data, typename Tree<T>::Element* Root)
{
	if (this->Root == nullptr)this->Root = new typename Tree<T>::Element(Data);
	if (Root == nullptr) return;
	if (Data < Root->Data)
	{
		if (Root->pLeft == nullptr) Root->pLeft = new typename Tree<T>::Element(Data);
		else insert(Data, Root->pLeft);
	}
	else if (Data > Root->Data)
	{
		if (Root->pRight == nullptr) Root->pRight = new typename Tree<T>::Element(Data);
		else insert(Data, Root->pRight);
	}
}

//--------------------------------------UniqueTree--------------------------------------//
//--------------------------------------------------------------------------------------//
//---------------------------------------Functions--------------------------------------//
template <typename T, typename U>
void Measure(const char* message, const Tree<U>& tree, T(Tree<U>::* member_function)() const)
{
	cout << message;
	clock_t start = clock();
	T value = (tree.*member_function)();
	clock_t end = clock();
	cout << value << endl;
	cout << "Completed in:  " << double(end - start) / CLOCKS_PER_SEC << " sec." << endl;
}
//---------------------------------------Functions--------------------------------------//