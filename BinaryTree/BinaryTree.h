#pragma once
#include <iostream>
#include <ctime>

using namespace std;
using std::cin;
using std::cout;
using std::endl;

template <typename T> class Tree;
class Element;
template <typename T> class UniqueTree;
template <typename T, typename U>
void Measure(const char* message, const Tree<U>& tree, T(Tree<U>::* member_function)() const);

template <typename T>
class Tree
{
protected:
	class Element
	{
		T Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(T Data, Element* pLeft = nullptr, Element* pRight = nullptr);
		~Element();
		friend class Tree<T>;
		friend class UniqueTree<T>;
	}*Root;

public:
	Element* getRoot();

	Tree();

	Tree(initializer_list<T> il);

	~Tree();

	void insert(T Data);

	T minValue() const;

	T maxValue() const;

	T Sum() const;

	T Count() const;

	double Avg() const;

	void print()const;

	void print_tree() const;

	void depth_print(int depth) const;

	void tree_print() const;

	void Clear();

	int Depth() const;

	void Erase(T Data);

	void balance();
private:
	void insert(T Data, Element* Root);

	void Erase(T Data, Element*& Root);

	T minValue(Element* Root) const;

	T maxValue(Element* Root) const;

	T Sum(Element* Root) const;

	T Count(Element* Root) const;

	double Avg(Element* Root) const;

	void print(Element* Root) const;

	void depth_print(Element* Root, int depth, int width) const;

	void tree_print(Element* Root, int width, int depth = 0) const;

	void print_tree(int Depth, Element* Root) const;

	/*void balance(Element*& Root);
	}*/

	void balance(Element* Root);

	void Clear(Element* Root);

	int Depth(Element* Root) const;

};

template <typename T>
class UniqueTree : public Tree<T>
{
public:
	void insert(T Data);
private:
	void insert(T Data, typename Tree<T>::Element* Root);
};