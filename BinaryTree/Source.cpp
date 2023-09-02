#include <iostream>

using namespace std;

class Three
{
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr) : Data(Data), pLeft(pLeft), pRight(pRight)
		{
			cout << "Element constructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "Element destructor:\t" << this << endl;
		}
		friend class Three;
	}*Root;

public:
	Three(): Root(nullptr)
	{
		cout << "Three constructor:\t" << this << endl;
	}
	~Three()
	{
		cout << "Three destructor:\t" << this << endl;
	}

};

void main()
{
	setlocale(LC_ALL, "");

}