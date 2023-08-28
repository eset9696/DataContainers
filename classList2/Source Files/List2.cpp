#include "../Header Files/List2.h"

//////////////////////////////////////////////////////////////////////////////////////////
//											Element										//
template <typename T> List<T>::Element::Element(T Data, Element* pNext, Element* pPrev) : Data(Data), pNext(pNext), pPrev(pPrev)
{
#ifdef DEBUG
	cout << "EConstructor:\t" << this << endl;
#endif // DEBUG
}
template <typename T> List<T>::Element::~Element()
{
#ifdef DEBUG
	cout << "EDestructor:\t" << this << endl;
#endif // DEBUG

}
//											Element										//
//////////////////////////////////////////////////////////////////////////////////////////
///------------------------------------------------------------------------------------///
//////////////////////////////////////////////////////////////////////////////////////////
//									Base Iterator methods								//
template <typename T> List<T>::ConstBaseIterator::ConstBaseIterator(Element* Temp) : Temp(Temp)
{
#ifdef DEBUG
	cout << "BaseIterator constructor" << this << endl;
#endif // DEBUG

}

template <typename T> List<T>::ConstBaseIterator::~ConstBaseIterator()
{
#ifdef DEBUG
	cout << "BaseIterator destructor" << this << endl;
#endif // DEBUG

}

template <typename T> bool List<T>::ConstBaseIterator::operator==(const ConstBaseIterator& other) const
{
	return this->Temp == other.Temp;
}

template <typename T> bool List<T>::ConstBaseIterator::operator!=(const ConstBaseIterator& other) const
{
	return this->Temp != other.Temp;
}

template <typename T> const T& List<T>::ConstBaseIterator::operator*() const
{
	return Temp->Data;
}
//									Base Iterator methods								//
//////////////////////////////////////////////////////////////////////////////////////////
///------------------------------------------------------------------------------------///

//////////////////////////////////////////////////////////////////////////////////////////
//										Iterator methods   			   				    //
template <typename T> List<T>::ConstIterator::ConstIterator(Element* Temp) : ConstBaseIterator(Temp)
{
#ifdef DEBUG
	cout << "ItConstructor:\t" << this << endl;
#endif // DEBUG

}
template <typename T> List<T>::ConstIterator::~ConstIterator()
{
#ifdef DEBUG
	cout << "ItDestructor:\t" << this << endl;
#endif // DEBUG

}

template <typename T> typename List<T>::ConstIterator& List<T>::ConstIterator::operator++()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}

template <typename T> typename List<T>::ConstIterator List<T>::ConstIterator::operator++(int)
{
	ConstIterator Old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return Old;
}

template <typename T> typename List<T>::ConstIterator& List<T>::ConstIterator::operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}

template <typename T> typename List<T>::ConstIterator List<T>::ConstIterator::operator--(int)
{
	ConstIterator Old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return Old;
}

template <typename T> List<T>::Iterator::Iterator(Element* Temp) : ConstIterator(Temp) {}

template <typename T> T& List<T>::Iterator::operator*()
{
	return ConstBaseIterator::Temp->Data;
}
//										Iterator methods   			   				     //
///////////////////////////////////////////////////////////////////////////////////////////
///-------------------------------------------------------------------------------------///

//////////////////////////////////////////////////////////////////////////////////////////
//									Reverse Iterator methods							//
template <typename T> List<T>::ConstReIterator::ConstReIterator(Element* Temp) : ConstBaseIterator(Temp)
{
#ifdef DEBUG
	cout << "ReItConstructor:\t" << this << endl;
#endif // DEBUG

}

template <typename T> List<T>::ConstReIterator::~ConstReIterator()
{
#ifdef DEBUG
	cout << "ReItDestructor:\t" << this << endl;
#endif // DEBUG

}

template <typename T> typename List<T>::ConstReIterator& List<T>::ConstReIterator::operator++()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}

template <typename T> typename List<T>::ConstReIterator List<T>::ConstReIterator::operator++(int)
{
	ConstReIterator Old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return Old;
}

template <typename T> typename List<T>::ConstReIterator& List<T>::ConstReIterator::operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}

template <typename T> typename List<T>::ConstReIterator List<T>::ConstReIterator::operator--(int)
{
	ConstReIterator Old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return Old;
}

template <typename T> List<T>::ReIterator::ReIterator(Element* Temp) : ConstReIterator(Temp) {}

template <typename T> T& List<T>::ReIterator::operator*()
{
	return ConstBaseIterator::Temp->Data;
}
//									Reverse Iterator methods						 	 //
///////////////////////////////////////////////////////////////////////////////////////////
///-------------------------------------------------------------------------------------///

//////////////////////////////////////////////////////////////////////////////////////////
//										 List methods									//
template <typename T> List<T>::List()
{
	Head = Tail = nullptr;
	cout << "LConstructor:\t" << this << endl;
}

template <typename T> List<T>::List(const initializer_list<T> il) : List()
{
	for (const T* it = il.begin(); it != il.end(); it++) push_back(*it);
	cout << "L IL Constructor:\t" << this << endl;
}

template <typename T> List<T>::List(const List<T>& other) : List()
{
	*this = other;
	cout << "L move Constructor:\t" << this << endl;
}

template <typename T> List<T>::List(List<T>&& other) noexcept : List()
{
	*this = move(other);
	cout << "L move Constructor:\t" << this << endl;
}

template <typename T> List<T>::~List()
{
	while (Head) pop_back();
	cout << "LDestructor:\t" << this << endl;
}

//Itarators & ReIterators begin() & end()

template <typename T> typename List<T>::ConstIterator List<T>::cbegin() const
{
	return Head;
}

template <typename T> typename List<T>::ConstIterator List<T>::cend() const
{
	return nullptr;
}

template <typename T> typename List<T>::ConstReIterator List<T>::crbegin() const
{
	return Tail;
}

template <typename T> typename List<T>::ConstReIterator List<T>::crend() const
{
	return nullptr;
}

template <typename T> typename List<T>::Iterator List<T>::begin()
{
	return Head;
}

template <typename T> typename List<T>::Iterator List<T>::end()
{
	return nullptr;
}

template <typename T> typename List<T>::ReIterator List<T>::rbegin()
{
	return Tail;
}

template <typename T> typename List<T>::ReIterator List<T>::rend()
{
	return nullptr;
}

//Adding elements
template <typename T> void List<T>::push_front(T Data)
{
	if (!Head && !Tail) Head = Tail = new Element(Data);
	else Head = Head->pPrev = new Element(Data, Head);
	size++;
}

template <typename T> void List<T>::push_back(T Data)
{
	if (!Head && !Tail) Head = Tail = new Element(Data);
	else Tail = Tail->pNext = new Element(Data, nullptr, Tail);
}

template <typename T> void List<T>::insert(T Data, int Index)
{
	if (Index > size) return;
	if (Index == size) return push_back(Data);
	if (!Index) return push_front(Data);
	Element* Temp;
	if (Index < size / 2)
	{
		Temp = Head;
		for (int i = 0; i < Index; i++)Temp = Temp->pNext;
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
template <typename T> void List<T>::pop_front()
{
	if (!Head && !Tail)return;
	if (Head == Tail)
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

template <typename T> void List<T>::pop_back()
{
	if (Head == Tail)return pop_front();
	Tail = Tail->pPrev;
	delete Tail->pNext;
	Tail->pNext = nullptr;
	size--;
}

template <typename T> void List<T>::erase(int Index)
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

template <typename T> void List<T>::print() const
{
	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
}

template <typename T> void List<T>::reverse_print() const
{
	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		cout << Temp->pNext << tab << Temp << tab << Temp->Data << tab << Temp->pPrev << endl;
}

//operators

template <typename T> List<T>& List<T>::operator=(const List<T>& other)
{
	if (this == &other) return *this;
	while (Head) pop_front();
	for (Element* Temp = other.Head; Temp; Temp = Temp->pNext) push_back(Temp->Data);
	cout << "L copy assignment:\t" << this << endl;
	return *this;
}

template <typename T> List<T>& List<T>::operator=(List<T>&& other) noexcept
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

template <typename T> List<T> operator+(const List<T>& left, const List<T>& right)
{
	List<T> cat = left;
	for (typename List<T>::ConstIterator it = right.cbegin(); it != right.cend(); ++it) cat.push_back(*it);
	return cat;
}
//									 	 List methods							 		  //
////////////////////////////////////////////////////////////////////////////////////////////
///--------------------------------------------------------------------------------------///