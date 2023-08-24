#include<iostream>

#define tab "\t"
#define delimeter "\n-----------------------------------\n"
using namespace std;

class List;
class Element;
class ConstIterator;
class ConstReIterator;

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
	} *Head, *Tail;
	unsigned int size;

public:
	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp) : Temp(Temp)
		{
			cout << "BaseIterator constructor" << this << endl;
		}

		~ConstBaseIterator()
		{
			cout << "BaseIterator destructor" << this << endl;
		}

		bool operator==(const ConstBaseIterator& other) const
		{
			return this->Temp == other.Temp;
		}

		bool operator!=(const ConstBaseIterator& other) const
		{
			return this->Temp != other.Temp;
		}

		const int& operator*() const
		{
			return Temp->Data;
		}
	};

	class ConstIterator : public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp = nullptr) : ConstBaseIterator(Temp)
		{
			cout << "ItConstructor:\t" << this << endl;
		}
		~ConstIterator()
		{
			cout << "ItDestructor:\t" << this << endl;
		}

		ConstIterator& operator++()
		{
			Temp = Temp->pNext;
			return *this;
		}

		ConstIterator operator++(int)
		{
			ConstIterator Old = *this;
			Temp = Temp->pNext;
			return Old;
		}

		ConstIterator& operator--()
		{
			Temp = Temp->pPrev;
			return *this;
		}

		ConstIterator operator--(int)
		{
			ConstIterator Old = *this;
			Temp = Temp->pPrev;
			return Old;
		}
	};

	class ConstReIterator: public ConstBaseIterator
	{
	public:
		ConstReIterator(Element* Temp = nullptr) : ConstBaseIterator(Temp)
		{
			cout << "ReItConstructor:\t" << this << endl;
		}
		~ConstReIterator()
		{
			cout << "ReItDestructor:\t" << this << endl;
		}

		ConstReIterator& operator++()
		{
			Temp = Temp->pPrev;
			return *this;
		}

		ConstReIterator operator++(int)
		{
			ConstReIterator Old = *this;
			Temp = Temp->pPrev;
			return Old;
		}

		ConstReIterator& operator--()
		{
			Temp = Temp->pNext;
			return *this;
		}

		ConstReIterator operator--(int)
		{
			ConstReIterator Old = *this;
			Temp = Temp->pNext;
			return Old;
		}
	};

	class Iterator : public ConstIterator
	{
	public:
		Iterator(Element* Temp = nullptr) : ConstIterator(Temp) {}

		int& operator*()
		{
			return Temp->Data;
		}
	};

	class ReIterator : public ConstReIterator
	{
	public:
		ReIterator(Element* Temp = nullptr) : ConstReIterator(Temp) {}

		int& operator*()
		{
			return Temp->Data;
		}
	};

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

	List(const List& other) : List()
	{
		*this = other;
		cout << "L move Constructor:\t" << this << endl;
	}

	List(List&& other) noexcept : List()
	{
		*this = move(other);
		cout << "L move Constructor:\t" << this << endl;
	}

	~List()
	{
		while (Head) pop_back();
		cout << "LDestructor:\t" << this << endl;
	}

	//Itarators & ReIterators begin() & end()

	ConstIterator cbegin() const
	{
		return Head;
	}

	ConstIterator cend() const
	{
		return nullptr;
	}

	ConstReIterator crbegin() const
	{
		return Tail;
	}

	ConstReIterator crend() const
	{
		return nullptr;
	}

	Iterator begin()
	{
		return Head;
	}

	Iterator end()
	{
		return nullptr;
	}

	ReIterator rbegin()
	{
		return Tail;
	}

	ReIterator rend()
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

	//operators
	
	List& operator=(const List& other)
	{
		if (this == &other) return *this;
		while (Head) pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext) push_back(Temp->Data);
		cout << "L copy assignment:\t" << this << endl;
		return *this;
	}

	List& operator=(List&& other) noexcept
	{
		while (Head) pop_front();
		this->Head = other.Head;
		this->Tail = other.Tail;
		this->size = other.size;
		other.Head = nullptr;
		other.Tail = nullptr;
		other.size = 0;
		cout << "L move assignment:\t" << this << endl;
		return *this;
	}
};
List operator+(const List& left, const List& right)
{
	List cat = left;
	for (List::ConstIterator it = right.cbegin(); it != right.cend(); ++it) cat.push_back(*it);
	return cat;
}

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

	//List list = {3, 5, 8, 13, 21};
	////list.print();

	//for (int i : list)
	//{
	//	cout << i << tab;
	//}
	//cout << endl;

	//for (List::ReIterator b = list.rbegin(), e = list.rend(); b != e; ++b) {
	//	int i = *b;
	//	cout << i << tab;
	//}
	//list.print();

	List list1 = { 3, 5, 8, 13, 21 };
	for (int i : list1) cout << i << tab;

	for (List::Iterator it = list1.begin(); it != list1.end(); ++it)
	{
		*it *= 10;
		cout << *it << tab;
	}
	List list2 = { 34, 55, 88};
	for (int i : list2) cout << i << tab;
	List list3 = list1 + list2;
	for (int i : list3) cout << i << tab;
}
