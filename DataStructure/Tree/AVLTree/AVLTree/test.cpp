#include"AVLTree.hpp"
#include<iostream>
using namespace std;

int main()
{
	lee::AVLTree<int, string> tree;
	tree.Insert(make_pair(3, "php"));
	tree.Insert(make_pair(1, "c++"));
	tree.Insert(make_pair(2, "c#"));
	tree.Insert(make_pair(7, "go"));
	tree.Insert(make_pair(11, "js"));
	tree.Insert(make_pair(19, "lua"));
	tree.Insert(make_pair(5, "sql"));
	tree.Insert(make_pair(8, "java"));
	tree.Insert(make_pair(4, "python"));
	tree.erase(7);

	tree.InOrderTravel();

	return 0;
}
