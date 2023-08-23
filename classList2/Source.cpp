#include<iostream>

#define tab "\t"
#define delimeter "\n-----------------------------------\n"
using namespace std;

class List;
class Element;
class Iterator;
class ReIterator;

class List
{
	class Element
	{	
		int Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr) : Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class List;
		friend class Iterator;
	} *Head, *Tail;
	unsigned int size;

	class Iterator
	{
		Element* Temp;
	public:
		Iterator(Element* Temp) : Temp(Temp)
		{
			cout << "ItConstructor:\t" << this << endl;
		}
		~Iterator()
		{
			cout << "ItDestructor:\t" << this << endl;
		}

		Element& operator++()
		{
			Temp = Temp->pNext;
			return *Temp;
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
			return Temp->Data;
		}
	};

	class ReIterator
	{
		Element* Temp;
	public:
		ReIterator(Element* Temp) : Temp(Temp)
		{
			cout << "ReItConstructor:\t" << this << endl;
		}
		~ReIterator()
		{
			cout << "ReItDestructor:\t" << this << endl;
		}

		Element& operator++()
		{
			Temp = Temp->pPrev;
			return *Temp;
		}

		bool operator==(const ReIterator& other)
		{
			return this->Temp == other.Temp;
		}

		bool operator!=(const ReIterator& other)
		{
			return this->Temp != other.Temp;
		}

		int operator*()
		{
			return Temp->Data;
		}
	};

public:
	List()
	{
		Head = Tail = nullptr;
		cout << "LConstructor:\t" << this << endl;
	}

	List(const initializer_list<int> il): List()
	{
		for (const int* it = il.begin(); it != il.end(); it++) push_back(*it);
		cout << "L IL Constructor:\t" << this << endl;
	}

	~List()
	{
		while (Head) pop_back();
		cout << "LDestructor:\t" << this << endl;
	}

	//Itarator

	Iterator begin()
	{
		return Head;
	}

	Iterator end()
	{
		return nullptr;
	}

	ReIterator r_begin()
	{
		return Tail;
	}

	ReIterator r_end()
	{
		return nullptr;
	}

	//Adding elements
	void push_front(int Data)
	{
		if (!Head && !Tail) Head = Tail = new Element(Data);
		else Head = Head->pPrev = new Element(Data, Head);
		size++;
	}

	void push_back(int Data)
	{
		if (!Head && !Tail) Head = Tail = new Element(Data);
		else Tail = Tail->pNext = new Element(Data, nullptr, Tail);
	}

	void insert(int Data, int Index)
	{
		if (Index > size) return;
		if (Index == size) return push_back(Data);
		if (!Index) return push_front(Data);
		Element* Temp;
		if(Index < size / 2)
		{
			Temp = Head;
			for(int i = 0; i < Index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - Index - 1; i++) Temp = Temp->pPrev;
		}
		Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
		size++;
	}

	//Removing elements
	void pop_front()
	{
		if (!Head && !Tail)return;
		if(Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
			return;
		}
		Head = Head->pNext;
		delete Head->pPrev;
		Head->pPrev = nullptr;
		size--;
	}

	void pop_back()
	{
		if (Head == Tail)return pop_front();
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
		size--;
	}

	void erase(int Index)
	{
		if (!Index) pop_front();
		if (Index >= size) return;
		Element* Temp;
		if (Index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < Index; i++) Temp = Temp->pNext;
		}
		else 
		{
			Temp = Tail;
			for (int i = 0; i < size - Index - 1; i++) Temp = Temp->pPrev;
		}
		Temp->pNext->pPrev = Temp->pPrev;
		Temp->pPrev->pNext = Temp->pNext;
		delete Temp;
		Temp = nullptr;
	}

	void print() const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext) 
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	}

	void reverse_print() const
	{
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			cout << Temp->pNext << tab << Temp << tab << Temp->Data << tab << Temp->pPrev << endl;
	}

	friend class Iterator;
};

//#define BASE_CHECK
void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка:\t"; cin >> n;
	List list;
	for (int i = 0; i < n; i++)list.push_front(rand() % 100);
	list.print();
	cout << delimeter << endl;
	list.reverse_print();
	int index;
	int value;
	cout << "Введите индекс добавляемого элемента:\t"; cin >> index;
	cout << "Введите значение добавляемого элемента:\t"; cin >> value;
	list.insert(value, index);
	list.print();
	cout << delimeter << endl;
	list.reverse_print();
	cout << "Введите индекс удаляемого элемента:\t"; cin >> index;
	list.erase(index);
	list.print();
	cout << delimeter << endl;
	list.reverse_print();
#endif // BASE_CHECK

	List list = {3, 5, 8, 13, 21};
	//list.print();

	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;

	auto&& range = list;
	for (auto b = list.r_begin(), e = list.r_end(); b != e; ++b) {
		int i = *b;
		cout << i << tab;
	}
	cout << endl;
}
