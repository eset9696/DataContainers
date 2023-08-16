#include<iostream>

using namespace std;

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

	ForwardList(const ForwardList& other)
	{
		Head = new Element(other.Head->Data);
		Element* el = Head;
		Element* el_other = other.Head;
		while (el_other->pNext)
		{
			while (el->pNext)
			{
				el = el->pNext;
			}
			el_other = el_other->pNext;
			el->pNext = new Element(el_other->Data);
			
		}
		cout << "FList copy constructor\t" << this << endl;
	}
	ForwardList(ForwardList&& other) noexcept
	{
		Head = other.Head;
		other.Head = nullptr;
		cout << "FList move constructor\t" << this << endl;
	}

	~ForwardList()
	{
		Element* el = Head->pNext;
		delete Head;
		while (el)
		{
			Head = el;
			el = Head->pNext;
			delete Head;
		}
		cout << "FList destructor\t" << this << endl;
	}

	ForwardList& operator=(const ForwardList& other)
	{
		Head = new Element(other.Head->Data);
		Element* el = Head;
		Element* el_other = other.Head;
		while (el_other->pNext)
		{
			while (el->pNext)
			{
				el = el->pNext;
			}
			el_other = el_other->pNext;
			el->pNext = new Element(el_other->Data);

		}
		cout << "FList copy assignment\t" << this << endl;
		return *this;
	}
	ForwardList& operator=(ForwardList&& other) noexcept
	{
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
		Element* el = Head;
		while (el->pNext)
		{
			el = el->pNext;
		}
		el->pNext = new Element(data);
	}
	void insert(int data, int index)
	{
		Element* el = Head;
		int pos = 0;
		while (pos != index - 1)
		{
			el = el->pNext;
			pos++;
		}
		el->pNext = new Element(data, el->pNext);
	}

	void pop_front()
	{
		Element* el = Head;
		el = el->pNext;
		delete Head;
		Head = el;
	}
	void pop_back()
	{
		Element* el = Head;
		while (el->pNext->pNext)
		{
			el = el->pNext;
		}
		delete el->pNext;
		el->pNext = nullptr;
	}
	void erase(int index)
	{
		int pos = 0;
		Element* el = Head;
		while (pos != index - 1)
		{
			el = el->pNext;
			pos++;
		}
		Element* temp = el->pNext->pNext;
		delete el->pNext;
		el->pNext = temp;
	}

	void print()const
	{
		Element* el = Head; // »тератор - эуказатель при помощи которого можно получить доступ к элементам структуры данных
		while (el)
		{
			cout << el << "\t" << el->Data << "\t" << el->pNext << endl;
			el = el->pNext;
		}
	}
};



void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "¬ведите размер списка: "; cin >> n;
	ForwardList list;
	for(int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();
	cout << endl;
	list.erase(2);
	list.print();
	list.push_back(100);
	list.print();
	cout << "move" << endl;
	ForwardList list1 = move(list);
	list1.print();
	ForwardList list2;
	list2 = list1;
	list2.print();
}