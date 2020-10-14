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
	trie.insert("��");
	trie.insert("�Ұ�ѧϰ");
	trie.insert("�Ұ�C++");
	trie.insert("��");

	for (auto str : trie.getPrefixWords("��"))
	{
		cout << str << endl;
	}
	for (auto str : trie.getPrefixWords("h"))
	{
		cout << str << endl;
	}
	cout << trie.find("��") << endl;
	cout << trie.find("��") << endl;
	cout << trie.find("cpp") << endl;
	cout << trie.find("java") << endl;
	cout << trie.startsWith("h") << endl;


	return 0;
}