#include<iostream>

#define tab "\t"
#define delimeter "\n----------------------------------\n"
using namespace std;

class Iterator;
class Element;
class List;

class Element
{
	int data;
	Element* pPrev;
	Element* pNext;
public:
	Element(int data, Element* pPrev = nullptr, Element* pNext = nullptr) :data(data), pPrev(pPrev), pNext(pNext)
	{
		cout << "Element constructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "Element destructor:\t" << this << endl;
	}
	friend class List;
};

class List
{
	Element* Head;
	Element* End;
public:
	List()
	{
		Head = nullptr;
		End = nullptr;

		cout << "List constructor:\t" << this << endl;
	}
	~List()
	{
	
		cout << "List destructor:\t" << this << endl;
	}

	void push_front(int data)
	{
		Head = new Element(data, End, Head);
		if (!End) End = Head;
	}

	void push_back(int data)
	{
		Head = new Element(data, Head, End);
	}

	void printN() const
	{
		Element* Temp = Head;
		while(Temp)
		{
			cout << Temp->pPrev << tab << Temp << tab << Temp->data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;
		}
	}

	void printP() const
	{
		Element* Temp = End;
		while (Temp)
		{
			cout << Temp->pPrev << tab << Temp << tab << Temp->data << tab << Temp->pNext << endl;
			Temp = Temp->pPrev;
		}
	}
};

void main()
{
	setlocale(LC_ALL, "");

	List list;

	for (int i = 0; i < 2; i++)list.push_front(rand() % 100);
	list.printN();
	cout << delimeter << endl;
	list.printP();
}