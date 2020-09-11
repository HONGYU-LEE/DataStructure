#include"SkipList.hpp"

using namespace std;

int main()
{
	lee::SkipList<int> sl;
	sl.insert(1);
	sl.insert(3);
	sl.insert(5);
	sl.insert(7);
	sl.insert(9);
	sl.insert(11);
	sl.insert(13);
	sl.insert(15);
	sl.insert(17);
	sl.printAll();

	return 0;
}