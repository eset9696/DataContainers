#include<iostream>

using namespace std;
template <typename T> class Iterator;
template <typename T> class Element;
template <typename T> class ForwardList;
template <typename T> ForwardList<T> operator+(const ForwardList<T>& left, const ForwardList<T>& right);
#define delimeter "\n-----------------------------\n"
template <typename T> class Element
{
	T Data; //данные
	Element<T>* pNext; // указатель на следующий элемент

public:
	Element(T Data, Element<T>* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		cout << "Element constructor\t" << this << endl;
	}

	~Element()
	{
		cout << "Element destructor\t" << this << endl;
	}

	friend class ForwardList<T>;
	template <typename T> friend ForwardList<T> operator+(const ForwardList<T>& left, const ForwardList<T>& right);
	friend class Iterator<T>;
};

template <typename T> class Iterator
{
	Element<T>* Temp;

public:
	Iterator(Element<T>* Temp = nullptr) :Temp(Temp)
	{
		cout << "Iterator constructor:\t" << this << endl;
	}

	~Iterator()
	{
		cout << "Iterator destructor:\t" << this << endl;
	}

	Iterator<T>& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}

	bool operator==(const Iterator<T>& other) const
	{
		return this->Temp == other.Temp;

	}

	bool operator!=(const Iterator<T>& other) const
	{
		return this->Temp != other.Temp;
	}

	T operator*()
	{
		return Temp->Data;
	}
};

template <typename T> class ForwardList
{
	Element<T>* Head; // содержит адрес начального элемента списка

public:
	ForwardList()
	{
		Head = nullptr; // если список пуст, то его голова указывает на ноль
		cout << "FList constructor\t" << this << endl;
	}

	ForwardList(const std::initializer_list<T>& il): ForwardList()
	{
		//int* - неконстантный указатель на переменную
		//const int* - неконстантный указатель на константу
		//int* const - константный указатель на неконстантную переменную
		//const int* const - константный указатель на константу
		for(T const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
		cout << "FList move constructor\t" << this << endl;
	}

	ForwardList(const ForwardList<T>& other) :ForwardList()
	{
		/*for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);*/
		*this = other;
		cout << "FList copy constructor\t" << this << endl;
	}

	ForwardList(ForwardList<T>&& other) noexcept :ForwardList()
	{
		*this = std::move(other); // функция move() принудительно вызывает MoveAssignment для объекта
		cout << "FList move constructor\t" << this << endl;
	}

	~ForwardList()
	{
		while (Head) pop_front();
		cout << "FList destructor\t" << this << endl;
	}

	ForwardList<T>& operator=(const ForwardList<T>& other)
	{
		if (this == &other) return *this;
		while (Head)pop_front();
		for (Element<T>* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
		cout << "FList copy assignment\t" << this << endl;
		return *this;
	}

	ForwardList<T>& operator=(ForwardList<T>&& other) noexcept
	{
		if (this == &other) return *this;
		while (Head)pop_front();
		this->Head = other.Head;
		other.Head = nullptr;
		cout << "FList move assignment\t" << this << endl;
		return *this;
	}
	
	//Adding elements
	void push_front(T data)
	{
		Head = new Element<T>(data, Head);
	}

	void push_back(T data)
	{
		if (Head == nullptr) return push_front(data);
		Element<T>* el = Head;
		while (el->pNext)
		{
			el = el->pNext;
		}
		el->pNext = new Element<T>(data);
	}

	void insert(T data, int index)
	{
		if (index == 0) return push_front(data);
		Element<T>* temp = Head;
		for (int i = 0; i < index - 1; i++)
			if (temp->pNext)temp = temp->pNext;
			else return;
		temp->pNext = new Element<T>(data, temp->pNext);
	}

	void pop_front()
	{
		Element<T>* erased = Head;
		Head = Head->pNext;
		delete erased;
	}

	void pop_back()
	{
		Element<T>* el = Head;
		while (el->pNext->pNext) el = el->pNext;
		delete el->pNext;
		el->pNext = nullptr;
	}

	void erase(int index)
	{
		if (index == 0)return pop_front();
		Element<T>* Temp = Head;
		for (int i = 0; i < index - 1; i++)
			if (Temp->pNext)
				Temp = Temp->pNext;
			else return;
		Element<T>* erased = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete erased;
	}

	Iterator<T> begin()
	{
		return Head;
	}

	Iterator<T> end()
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

	friend class Element<T>;
	template <typename T> friend ForwardList<T> operator+(const ForwardList<T>& left, const ForwardList<T>& right);
};

template <typename T> ForwardList<T> operator+(const ForwardList<T>& left, const ForwardList<T>& right)
{
	ForwardList<T> cat = left;
	for (Element<T>* Temp = right.Head; Temp; Temp = Temp->pNext) cat.push_back(Temp->Data);
	return cat;
}

//#define BASE_CHECK
//#define OPERATOR_PLUS_CHECK
//#define RANGE_BASED_FOR_ARRAY
//#define RANGE_BASED_FOR_LIST
#define MOVE_SEMANTIC_CHECK
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

#ifdef MOVE_SEMANTIC_CHECK
	ForwardList<int> list1 = { 3, 5, 8, 13, 21 };
	for(int i: list1)cout << i << "\t"; cout << endl;
	cout << delimeter << endl;
	ForwardList<int> list2 = { 34, 55, 89 };
	for (int i : list2)cout << i << "\t"; cout << endl;
	cout << delimeter << endl;
	ForwardList<int> list3 = list1 + list2;
	cout << delimeter << endl;
	for (int i : list3)cout << i << "\t"; cout << endl;

	ForwardList<double> d_list1 = {2.7, 3.4, 5.1};
	ForwardList<double> d_list2 = {7.3, 8.2, 4.4, 9.5};
	ForwardList<double> d_list3 = d_list1 + d_list2;
	for (double i : d_list3) cout << i << "\t"; cout << endl;
	
#endif // MOVE_SEMANTIC_CHECK

}