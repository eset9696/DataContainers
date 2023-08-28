#include "List2.h"
#include "List2.cpp"

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

	cout << "List2 separated" << endl;

	List<int> list1 = { 3, 5, 8, 13, 21 };
	for (int i : list1) cout << i << tab;

	for (List<int>::Iterator it = list1.begin(); it != list1.end(); ++it)
	{
		*it *= 10;
		cout << *it << tab;
	}
	List<int> list2 = { 34, 55, 88 };
	for (int i : list2) cout << i << tab;
	List<int> list3 = list1 + list2;
	for (int i : list3) cout << i << tab;
	List<double> d_list1 = { 2.7, 3.14, 5.1 };
	List<double> d_list2 = { 4.4, 8.3 };
	List<double> d_list3 = d_list1 + d_list2;
	for (double i : d_list3) cout << i << tab;
}