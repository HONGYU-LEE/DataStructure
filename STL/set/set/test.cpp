#include"set.hpp"

using namespace std;

int main()
{
	lee::set<int> s;
	s.insert(3);
	s.insert(4);
	s.insert(1);
	s.insert(2);
	s.insert(5);

	lee::set<int>::iterator it = s.begin();
	while (it != s.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
	return 0;
}