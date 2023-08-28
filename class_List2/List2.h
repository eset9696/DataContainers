#pragma once
#include<iostream>

#define tab "\t"
#define delimeter "\n-----------------------------------\n"
using namespace std;

template <typename T> class List;
class Element;
class ConstIterator;
class ConstReIterator;
template <typename T> List<T> operator+(const List<T>& left, const List<T>& right);

template <typename T> class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr);
		~Element();
		friend class List<T>;
	} *Head, * Tail;
	unsigned int size;

public:

	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp);

		~ConstBaseIterator();

		bool operator==(const ConstBaseIterator& other) const;

		bool operator!=(const ConstBaseIterator& other) const;

		const T& operator*() const;
	};

	class ConstIterator : public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp = nullptr);
		~ConstIterator();


		ConstIterator& operator++();

		ConstIterator operator++(int);

		ConstIterator& operator--();

		ConstIterator operator--(int);
	};

	class Iterator : public ConstIterator
	{
	public:
		Iterator(Element* Temp = nullptr);

		T& operator*();
	};

	class ConstReIterator : public ConstBaseIterator
	{
	public:
		ConstReIterator(Element* Temp = nullptr);
		~ConstReIterator();

		ConstReIterator& operator++();

		ConstReIterator operator++(int);

		ConstReIterator& operator--();

		ConstReIterator operator--(int);
	};

	class ReIterator : public ConstReIterator
	{
	public:
		ReIterator(Element* Temp = nullptr);

		T& operator*();
	};

	List();
	List(const initializer_list<T> il);
	List(const List<T>& other);
	List(List<T>&& other) noexcept;
	~List();

	//Itarators & ReIterators begin() & end()

	ConstIterator cbegin() const;
	ConstIterator cend() const;
	ConstReIterator crbegin() const;
	ConstReIterator crend() const;

	Iterator begin();
	Iterator end();
	ReIterator rbegin();
	ReIterator rend();

	//Adding elements
	void push_front(T Data);
	void push_back(T Data);
	void insert(T Data, int Index);

	//Removing elements
	void pop_front();
	void pop_back();
	void erase(int Index);

	void print() const;
	void reverse_print() const;

	//operators

	List<T>& operator=(const List<T>& other);
	List<T>& operator=(List<T>&& other) noexcept;
};