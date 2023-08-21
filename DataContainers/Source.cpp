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
	Iterator(Element* temp): Temp(temp)
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

	bool operator==(const Iterator& other)
	{
		return this->Temp == other.Temp;
	}

	bool operator!=(const Iterator& other)
	{
		return this->Temp != other.Temp;
	}

	int operator*()
	{
		return Temp->data;
	}
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

	List(const List& other): List()
	{
		*this = other;
		cout << "List copy constructor:\t" << this << endl;
	}

	List(List&& other): List()
	{
		*this = std::move(other);
		cout << "List move constructor:\t" << this << endl;
	}

	List(const initializer_list<int>& il)
	{
		for (const int* it = il.begin(); it != il.end(); it++) push_back(*it);
		cout << "List IL constructor:\t" << this << endl;
	}

	~List()
	{
		while (Head) pop_front();
		cout << "List destructor:\t" << this << endl;
	}

	Iterator begin()
	{
		return Head;
	}

	Iterator end()
	{
		return End->pNext;
	}

	void push_front(int data)
	{
		if(!Head)
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
		if (!End) return push_front(data);
		End->pNext = new Element(data, End, End->pNext);
		End = End->pNext;
	}

	void insert(int data, int index)
	{
		if (!index) return push_front(data);
		Element* Temp = Head;
		for(int i = 0; i < index - 1; i++)
		{
			if (Temp->pNext) Temp = Temp->pNext;
			else return;
		}
		Temp->pNext->pPrev = new Element(data, Temp, Temp->pNext);
		Temp->pNext = Temp->pNext->pPrev;
	}

	void pop_front()
	{
		Element* Erased = Head;
		if(Head->pNext) Head->pNext->pPrev = Head;
		Head = Head->pNext;
		delete Erased;
	}

	void pop_back()
	{
		Element* Erased = End;
		if (End->pPrev) End->pPrev->pNext = End;
		End = End->pPrev;
		delete Erased;
	}
	
	void erase(int index)
	{
		if (!index) return pop_front();
		Element* Temp = Head;
		for(int i = 0; i < index - 1; i++) 
		{
			if (Temp->pNext->pNext) Temp = Temp->pNext;
			else return;
		}
		Element* Erased = Temp->pNext;
		Temp->pNext->pNext->pPrev = Temp;
		Temp->pNext = Temp->pNext->pNext;
		delete Erased;
	}

	void printN() const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << tab << Temp << tab << Temp->data << tab << Temp->pNext << endl;
	}

	void printP() const
	{
		for (Element* Temp = End; Temp; Temp = Temp->pPrev)
			cout << Temp->pNext << tab << Temp << tab << Temp->data << tab << Temp->pPrev << endl;
	}

	List& operator=(const List& other)
	{
		if (this == &other) return *this;
		while (Head) pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext) push_back(Temp->data);
		cout << "List copy assignment:\t" << this << endl;
		return *this;
	}

	List& operator=(List&& other)
	{
		if (this == &other) return *this;
		while (Head) pop_front();
		this->Head = other.Head;
		other.Head = nullptr;
		cout << "List move assignment:\t" << this << endl;
		return *this;
	}
	friend class Iterator;
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
#define RANGE_BASED_FOR_LIST_CHECK
void main()
{
	setlocale(LC_ALL, "");

#ifdef METHODS_CHECK

	List list;

	for (int i = 0; i < 5; i++)list.push_back(rand() % 100);

	list.printN();
	cout << delimeter << endl;
	list.printP();
	list.insert(100, 2);
	list.printN();
	list.erase(2);
	list.printN();
	list.pop_front();
	list.printN();
	list.pop_back();
	list.printN();

#endif // METHODS_CHECK
#ifdef COPY_SEMANTIC_CHECK

	List list1;

	for (int i = 0; i < 5; i++)list1.push_back(rand() % 100);
	list1.printN();

	List list2 = list1;
	list2.printN();

#endif // COPY_SEMANTIC_CHECK

#ifdef MOVE_SEMANTIC_CHECK

	List list1;

	for (int i = 0; i < 5; i++)list1.push_back(rand() % 100);
	list1.printN();

	List list2 = list1;
	for (int i = 0; i < 5; i++)list2.push_front(rand() % 100);
	list2.printN();

	List list3 = list1 + list2;
	list3.printN();

#endif // MOVE_SEMANTIC_CHECK

#ifdef RANGE_BASED_FOR_LIST_CHECK

	List list1 = { 1, 2, 3, 4, 5 };

	list1.printN();

	for (int i : list1) cout << i << tab;
	cout << endl;

#endif // RANGE_BASED_FOR_LIST_CHECK

}