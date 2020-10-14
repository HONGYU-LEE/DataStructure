#include<iostream>
#include"TrieTree.hpp"

using namespace std;

int main()
{
	lee::TrieTree trie;

	trie.insert("hello");
	trie.insert("helo");
	trie.insert("hill");
	trie.insert("world");
	trie.insert("test");
	trie.insert("cpp");
	trie.insert("我");
	trie.insert("我爱学习");
	trie.insert("我爱C++");
	trie.insert("你");

	for (auto str : trie.getPrefixWords("我"))
	{
		cout << str << endl;
	}
	for (auto str : trie.getPrefixWords("h"))
	{
		cout << str << endl;
	}
	cout << trie.find("我") << endl;
	cout << trie.find("它") << endl;
	cout << trie.find("cpp") << endl;
	cout << trie.find("java") << endl;
	cout << trie.startsWith("h") << endl;


	return 0;
}