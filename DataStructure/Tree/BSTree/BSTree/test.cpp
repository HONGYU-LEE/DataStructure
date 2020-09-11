#include"BSTree_KV.hpp"

using namespace std;

int main()
{
	int arr[] = { 5, 3, 7, 9, 1, 4 };
	lee::BSTree<int, char> tree;
	tree.Insert(3, 'A');
	tree.Insert(5, 'a');
	tree.Insert(7, 'd' );
	tree.Insert(9, 'f');
	tree.Insert(1,'e');
	tree.Insert(4, 'g');
	tree.InordTravel();

	cout << endl;

	//lee::BSTree<int> temp(tree);
	//temp.InordTravel();

	lee::BSTree<int, char> tree1;
	tree1.Insert(1, 'i');
	tree1.Insert(3, 'u');
	tree1.Insert(4, 'j');
	tree1.Insert(5, 'k');
	tree1.Insert(7, 'm');
	tree1.Insert(0, 'n');
	tree1.InordTravel();

	tree = tree1;

	tree1.InordTravel();
	tree.InordTravel();
	tree1.Insert(33, 'z');
	tree.Insert(55, 'x');

	tree1.InordTravel();
	tree.InordTravel();

	return 0;
}