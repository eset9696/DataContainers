#include "BinaryTree.h"
#include "BinaryTree.cpp"

//#define BASE_CHECK
//#define OLD_PERFORMANCE_CHECK
//#define RANGE_BASED_FOR_TREE_CHECK
//#define DEPTH_CHECK
//#define BALANCE_CHECK
void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Enter tree size:\n"; cin >> n;

	Tree<int> tree;
	clock_t start1 = clock();
	clock_t start = clock();
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
#ifdef OLD_PERFORMANCE_CHECK
	//Measure("insert", tree, &Tree::insert);
	clock_t end = clock();
	cout << "insert time:\t" << double(end - start) / CLOCKS_PER_SEC << endl;
	//tree.print();

	cout << "Min value in tree:\t" << endl;
	start = clock();
	int min = tree.minValue();
	end = clock();
	cout << min << endl;
	cout << "min time:\t" << double(end - start) / CLOCKS_PER_SEC << endl;
	///////////////////////////////////////
	cout << "Max value in tree:\t";
	start = clock();
	int max = tree.maxValue();
	end = clock();
	cout << max << endl;
	cout << "max time:\t" << double(end - start) / CLOCKS_PER_SEC << endl;
	///////////////////////////////////
	cout << "Sum of tree elements:\t";
	start = clock();
	int sum = tree.Sum();
	end = clock();
	cout << sum << endl;
	cout << "Sum time:\t" << double(end - start) / CLOCKS_PER_SEC << endl;
	///////////////////////////
	cout << "Number of tree elements:\t";
	start = clock();
	int num = tree.Count();
	end = clock();
	cout << num << endl;
	cout << "Count time:\t" << double(end - start) / CLOCKS_PER_SEC << endl;
	//////////////////////////////////////////
	cout << "Arithmetic mean of tree elements:\t";
	start = clock();
	double avg = tree.Avg();
	end = clock();
	cout << avg << endl;
	cout << "Avg time:\t" << double(end - start) / CLOCKS_PER_SEC << endl;
	//////////////////////////////////////////
	cout << "Depth of tree:\t";
	start = clock();
	int depth = tree.Depth();
	end = clock();
	cout << depth << endl;
	cout << "Depth time:\t" << double(end - start) / CLOCKS_PER_SEC << endl;
#endif // OLD_PERFORMANCE_CHECK
	Measure("Min value in tree: ", tree, &Tree<int>::minValue);
	Measure("Max value in tree: ", tree, &Tree<int>::maxValue);
	Measure("Sum of tree elements: ", tree, &Tree<int>::Sum);
	Measure("Number of tree elements: ", tree, &Tree<int>::Count);
	Measure("Avg value of tree elements: ", tree, &Tree<int>::Avg);
	Measure("Depth of tree: ", tree, &Tree<int>::Depth);

	cout << "==================================== Unique Tree ====================================" << endl;

	UniqueTree<int> u_tree;
	for (int i = 0; i < n; i++)
	{
		u_tree.insert(rand() % 100);
	}
	//u_tree.print();
	cout << "Min value in unique tree:\t" << u_tree.minValue() << endl;
	cout << "Max value in unique tree:\t" << u_tree.maxValue() << endl;
	cout << "Sum of unique tree elements:\t" << u_tree.Sum() << endl;
	cout << "Number of unique tree elements:\t" << u_tree.Count() << endl;
	cout << "Arithmetic mean of unique tree elements:\t" << u_tree.Avg() << endl;
	cout << "Depth of tree:\t" << u_tree.Depth() << endl;

#endif // BASE_CHECK

#ifdef RANGE_BASED_FOR_TREE_CHECK
	//Tree tree = { 2000, 1998, 1900, 1800, 1700, 1600, 1500, 1400, 1300, 1200, 1100, 1000, 900, 800 };
	//Tree tree = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711 };
	Tree tree = {10, 20, 5, 6, 3, 15, 2, 4, 1};
	//tree.print();
	//tree.print_tree();
	tree.balance();
	cout << "-----------------------------------------------------" << endl;
	//tree.print();
	//tree.print_tree();
#endif // RANGE_BASED_FOR_TREE_CHECK

#ifdef DEPTH_CHECK
	Tree tree = { 50, 25, 75, 16, 32, 64, 90, 28, 29 };
	tree.print();
	cout << "Depth of tree:\t" << tree.Depth() << endl;
	/*int depth;
	cout << "Enter depth of tree:\t"; cin >> depth;
	tree.depth_print(depth);*/
	tree.tree_print();
#endif // DEPTH_CHECK

	Tree<int> tree = { 89, 55, 34, 21, 13, 8, 5, 3, 3 };
	UniqueTree <double> u_tree;
	for (int i = 0; i < 10; i++)
	{
		u_tree.insert(i + 1.15*3);
		u_tree.insert(i + 1.15*3);
	}

	tree.tree_print();
	u_tree.print_tree();
	Measure("Avg work time:\t", tree, &Tree<int>::Avg);
	tree.balance();
	u_tree.balance();
	tree.tree_print();
	u_tree.print_tree();
}