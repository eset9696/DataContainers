#include<iostream>

#define tab "\t"
#define delimeter "\n----------------------------------\n"
using namespace std;

class Iterator;
class Element;
class List;
List operator+(const List& left, const List& right);

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
	friend class Iterator;
	friend List operator+(const List& left, const List& right);
};

class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp = nullptr) : Temp(Temp)
	{
		cout << "Iterator constructor:\t" << this << endl;
	}
	~Iterator()
	{
		cout << "Iterator destructor:\t" << this << endl;
	}
	Iterator& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}
	bool operator==(const Iterator& other) const
	{
		return this->Temp == other.Temp;
	}

	bool operator!=(const Iterator& other) const
	{
		return this->Temp != other.Temp;
	}

	int operator*() const
	{
		return this->Temp->data;
	}
};

class List
{
	Element* Head;
	Element* End;
public:

	Iterator begin()
	{
		return Head;
	}

	Iterator end()
	{
		return End->pNext;
	}

	List()
	{
		Head = nullptr;
		End = nullptr;

		cout << "List constructor:\t" << this << endl;
	}

	List(const initializer_list<int>& il) : List()
	{
		for (const int* it = il.begin(); it != il.end(); it++) push_back(*it);
	}

	List(const List& other) : List()
	{
		*this = other;
		cout << "List copy constructor:\t" << this << endl;
	}

	List(List&& other) noexcept : List()
	{
		*this = move(other);
		cout << "List move constructor:\t" << endl;
	}

	~List()
	{
		while (Head) pop_front();
		cout << "List destructor:\t" << this << endl;
	}
	void push_front(int data)
	{
		if (!Head)
		{
			Head = new Element(data, 0, Head);
			End = Head;
			return;
		}
		Head->pPrev = new Element(data, Head->pPrev, Head);
		Head = Head->pPrev;
	}

	void push_back(int data)
	{
		if (End == nullptr) return push_front(data);
		End->pNext = new Element(data, End, End->pNext);
		End = End->pNext;
	}

	void insert(int data, int index)
	{
		if (!index) return push_front(data);
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)
		{
			if (Temp->pNext->pNext) Temp = Temp->pNext;
			else return push_back(data);
		}
		Temp->pNext->pPrev = new Element(data, Temp, Temp->pNext);
		Temp->pNext = Temp->pNext->pPrev;

	}

	void pop_front()
	{
		Element* Erased = Head;
		if (Head->pNext)Head->pNext->pPrev = Head->pPrev;
		Head = Head->pNext;
		delete Erased;
	}

	void pop_back()
	{
		Element* Erased = End;
		if (Erased->pPrev)Erased->pPrev->pNext = Erased->pNext;
		End = Erased->pPrev;
		delete Erased;
	}

	void erase(int index)
	{
		if (!index) return pop_front();
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)
		{
			if (Temp->pNext->pNext) Temp = Temp->pNext;
			else return pop_back();
		}
		Element* erase = Temp->pNext;
		Temp->pNext = erase->pNext;
		Temp->pNext->pPrev = Temp;
		delete erase;
	}

	void print() const
	{
		for(Element* Temp = Head; Temp; Temp = Temp->pNext) 
			cout << Temp->pPrev << tab << Temp << tab << Temp->data << tab << Temp->pNext << endl;
	}

	List& operator=(const List& other)
	{
		if (this == &other) return *this;
		while (this->Head) pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext) push_back(Temp->data);
		cout << "List copy assignment:\t" << this << endl;
		return *this;
	}

	List& operator=(List&& other) noexcept
	{
		if (this == &other) return *this;
		while (Head) pop_front();
		this->Head = other.Head;
		other.Head = nullptr;
		this->End = other.End;
		other.End = nullptr;
		cout << "List move assignment:\t" << this << endl;
	}

	friend List operator+(const List& left, const List& right);
};

List operator+(const List& left, const List& right)
{
	List cat = left;
	for (Element* Temp = right.Head; Temp; Temp = Temp->pNext) cat.push_back(Temp->data);
	return cat;
}

//#define METHODS_CHECK
//#define COPY_SEMANTIC_CHECK
//#define MOVE_SEMANTIC_CHECK
void main()
{
	setlocale(LC_ALL, "");

	List list;

	for (int i = 0; i < 5; i++)list.push_back(rand() % 100);
	list.print();
#ifdef METHODS_CHECK
	cout << delimeter << endl;
	cout << delimeter << endl;
	list.insert(100, 0);
	list.print();
	cout << delimeter << endl;
	list.erase(0);
	list.print();
	cout << delimeter << endl;
	list.pop_fornt();
	list.print();
	cout << delimeter << endl;
	list.pop_back();
	list.print();
#endif // METHODS_CHECK
#ifdef COPY_SEMANTIC_CHECK
	List list2 = list;
	list2.print();
	List list3;
	list3 = list2;
	list3.print();
#endif // COPY_SEMANTIC_CHECK

#ifdef MOVE_SEMANTIC_CHECK
	List list2 = list;
	List list3 = move(list + list2);
	list3.printN();
#endif // MOVE_SEMANTIC_CHECK
	List list1 = { 1, 2, 3, 4, 5 };
	list1.print();
	for (int i : list1)
	{
		cout << i << tab;
	}
	cout << endl;


}