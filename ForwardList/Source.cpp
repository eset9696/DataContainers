#include<iostream>

using namespace std;
class ConstIterator;
class Element;
template <class T> class ForwardList;
template <class T> ForwardList<T> operator+(const ForwardList<T>& left, const ForwardList<T>& right);
#define delimeter "\n-----------------------------\n"

template <class T>
class ForwardList
{
public:
	class Element
	{
		T Data; //данные
		Element* pNext;

	public:
		Element(T Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
		{
			cout << "Element constructor\t" << this << endl;
		}

		~Element()
		{
			cout << "Element destructor\t" << this << endl;
		}

		friend class ForwardList;
		friend ForwardList<T> operator+(const ForwardList<T>& left, const ForwardList<T>& right);
		friend class ConstIterator;
	};

	class ConstIterator
	{
	protected:
		Element* Temp;
	public:
		ConstIterator(Element* Temp = nullptr) :Temp(Temp)
		{
			cout << "Iterator constructor:\t" << this << endl;
		}

		~ConstIterator()
		{
			cout << "Iterator destructor:\t" << this << endl;
		}

		ConstIterator& operator++()
		{
			Temp = Temp->pNext;
			return *this;
		}

		bool operator==(const ConstIterator& other) const
		{
			return this->Temp == other.Temp;

		}

		bool operator!=(const ConstIterator& other) const
		{
			return this->Temp != other.Temp;
		}

		const T& operator*() const
		{
			return Temp->Data;
		}
	}; 

	class Iterator : public ConstIterator
	{
	public:
		Iterator(Element* Temp = nullptr) : ConstIterator(Temp) {}

		T& operator*()
		{
			return ConstIterator::Temp->Data;
		}
	};

	Element* Head; // содержит адрес начального элемента списка

	ForwardList()
	{
		Head = nullptr; // если список пуст, то его голова указывает на ноль
		cout << "FList constructor\t" << this << endl;
	}

	ForwardList(const std::initializer_list<T>& il): ForwardList()
	{
		for(T const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
		cout << "FList move constructor\t" << this << endl;
	}

	ForwardList(const ForwardList& other) :ForwardList()
	{
		*this = other;
		cout << "FList copy constructor\t" << this << endl;
	}

	ForwardList(ForwardList&& other) noexcept :ForwardList()
	{
		*this = std::move(other); // функци€ move() принудительно вызывает MoveAssignment дл€ объекта
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
		this->Head = other.Head;
		other.Head = nullptr;
		cout << "FList move assignment\t" << this << endl;
		return *this;
	}
	
	//Adding elements
	void push_front(T data)
	{
		Head = new Element(data, Head);
	}

	void push_back(T data)
	{
		if (Head == nullptr) return push_front(data);
		Element* el = Head;
		while (el->pNext)
		{
			el = el->pNext;
		}
		el->pNext = new Element(data);
	}

	void insert(T data, int index)
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

	ConstIterator cbegin() const
	{
		return Head;
	}

	ConstIterator cend() const
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

	void print()const
	{
		for(Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << endl;
	}

	friend class Element;
	friend ForwardList operator+<T>(const ForwardList& left, const ForwardList& right);
};

template <class T> ForwardList<T> operator+(const ForwardList<T>& left, const ForwardList<T>& right)
{
	ForwardList<T> cat = left;
	for (auto it = right.cbegin(); it != right.cend(); ++it)cat.push_back(*it); // auto -> ConstIterator? 
	return cat;
}

//#define BASE_CHECK
//#define OPERATOR_PLUS_CHECK
//#define RANGE_BASED_FOR_ARRAY
#define RANGE_BASED_FOR_LIST
//#define MOVE_SEMANTIC_CHECK
void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "¬ведите размер списка: "; cin >> n;
	ForwardList<double> list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(10.12);
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
	ForwardList<double> list2;
	list2 = list;
	list2.print();
	list = list;
	list2.print();
#endif // BASE_CHECK

#ifdef OPERATOR_PLUS_CHECK
	ForwardList<double> list1;
	list1.push_back(3.3);
	list1.push_back(5.3);
	list1.push_back(8.3);
	list1.push_back(13.3);
	list1.push_back(21.3);
	list1.print();
	ForwardList<double> list2;
	list2.push_back(34.3);
	list2.push_back(55.3);
	list2.push_back(89.3);
	list2.print();
	ForwardList<double> list3 = move(list1 + list2);
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
	ForwardList<double> list = { 3.3, 5, 8, 13, 21 };
	list.print();
	for(double i : list)
	{
		cout << i << endl;
	}

#endif // RANGE_BASED_FOR_LIST

#ifdef MOVE_SEMANTIC_CHECK
	ForwardList<double> list1 = { 3.4, 5.1, 8, 13, 21 };
	list1.print();
	cout << delimeter << endl;
	ForwardList<double> list2 = { 34, 55, 89 };
	list2.print();
	cout << delimeter << endl;
	ForwardList<double> list3 = list1 + list2;
	cout << delimeter << endl;
	list3.print();

#endif // MOVE_SEMANTIC_CHECK

}