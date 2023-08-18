#include<iostream>

using namespace std;
class Iterator;
class Element;
class ForwardList;
ForwardList operator+(const ForwardList& left, const ForwardList& right);

class Element
{
	int Data; //данные
	Element* pNext; // указатель на следующий элемент

public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		cout << "Element constructor\t" << this << endl;
	}

	~Element()
	{
		cout << "Element destructor\t" << this << endl;
	}

	friend class ForwardList;
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
	friend class Iterator;
};

class Iterator
{
	Element* Temp;

public:
	Iterator(Element* Temp = nullptr) :Temp(Temp)
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

	int operator*()
	{
		return Temp->Data;
	}
};

class ForwardList
{
	Element* Head; // содержит адрес начального элемента списка

public:
	ForwardList()
	{
		Head = nullptr; // если список пуст, то его голова указывает на ноль
		cout << "FList constructor\t" << this << endl;
	}

	ForwardList(const std::initializer_list<int>& il): ForwardList()
	{
		//int* - неконстантный указатель на переменную
		//const int* - неконстантный указатель на константу
		//int* const - константный указатель на неконстантную переменную
		//const int* const - константный указатель на константу
		for(int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
		cout << "FList move constructor\t" << this << endl;
	}

	ForwardList(const ForwardList& other) :ForwardList()
	{
		/*for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);*/
		*this = other;
		cout << "FList copy constructor\t" << this << endl;
	}

	ForwardList(ForwardList&& other) noexcept :ForwardList()
	{
		*this = other;
		cout << "FList move constructor\t" << this << endl;
	}

	~ForwardList()
	{
		while (Head) pop_front();
		cout << "FList destructor\t" << this << endl;
	}

	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other) return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
		cout << "FList copy assignment\t" << this << endl;
		return *this;
	}

	ForwardList& operator=(ForwardList&& other) noexcept
	{
		if (this == &other) return *this;
		while (Head)pop_front();
		Head = other.Head;
		other.Head = nullptr;
		cout << "FList move assignment\t" << this << endl;
		return *this;
	}
	
	//Adding elements
	void push_front(int data)
	{
		Head = new Element(data, Head);
	}

	void push_back(int data)
	{
		if (Head == nullptr) return push_front(data);
		Element* el = Head;
		while (el->pNext)
		{
			el = el->pNext;
		}
		el->pNext = new Element(data);
	}

	void insert(int data, int index)
	{
		if (index == 0) return push_front(data);
		Element* temp = Head;
		for (int i = 0; i < index - 1; i++)
			if (temp->pNext)temp = temp->pNext;
			else return;
		temp->pNext = new Element(data, temp->pNext);
	}

	void pop_front()
	{
		Element* erased = Head;
		Head = Head->pNext;
		delete erased;
	}

	void pop_back()
	{
		Element* el = Head;
		while (el->pNext->pNext) el = el->pNext;
		delete el->pNext;
		el->pNext = nullptr;
	}

	void erase(int index)
	{
		if (index == 0)return pop_front();
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)
			if (Temp->pNext)
				Temp = Temp->pNext;
			else return;
		Element* erased = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete erased;
	}

	Iterator begin()
	{
		return Head;
	}

	Iterator end()
	{
		return nullptr;
	}

	void print()const
	{
		//Element* el = Head; // Итератор - эуказатель при помощи которого можно получить доступ к элементам структуры данных
		//while (el)
		//{
		//	cout << el << "\t" << el->Data << "\t" << el->pNext << endl;
		//	el = el->pNext;
		//}
		for(Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << endl;
	}

	friend class Element;
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
};

ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList cat = left;
	for (Element* Temp = right.Head; Temp; Temp = Temp->pNext) cat.push_back(Temp->Data);
	return cat;
}

//#define BASE_CHECK
//#define OPERATOR_PLUS_CHECK
//#define RANGE_BASED_FOR_ARRAY
#define RANGE_BASED_FOR_LIST
void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.print();
	/*int value;
	int index;
	cout << "Enter value:\t";
	cin >> value;
	cout << "Enter index:\t";
	cin >> index;
	list.insert(value, index);
	list.print();
	list.erase(index);
	list.print();*/
	//ForwardList list2 = list;
	ForwardList list2;
	list2 = list;
	list2.print();
	list = list;
	list2.print();
#endif // BASE_CHECK

#ifdef OPERATOR_PLUS_CHECK
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);
	list1.print();
	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	list2.print();
	ForwardList list3 = move(list1 + list2);
	list3.print();
#endif // OPERATOR_PLUS_CHECK

#ifdef RANGE_BASED_FOR_ARRAY
	int list[] = { 3, 5, 8, 13, 21 };
	for (int i : list)
	{
		cout << i << endl;
	}
#endif // RANGE_BASED_FOR_ARRAY

#ifdef RANGE_BASED_FOR_LIST
	ForwardList list = { 3, 5, 8, 13, 21 };
	list.print();
	for(int i : list)
	{
		cout << i << endl;
	}

#endif // RANGE_BASED_FOR_LIST

}