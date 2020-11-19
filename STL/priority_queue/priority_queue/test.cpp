#include<iostream>
#include"priority_queue.hpp"

using namespace std;

int main()
{
	int arr[5] = { 1 , 8, 9, 4, 5 };
	lee::priority_queue<int, vector<int>, less<int>> heap(begin(arr), end(arr));

	//heap.pop();
	//cout << heap.top();
	/*cout << "size: " << heap.size() << " empty: " << heap.empty() << endl;*/

	for (size_t i = 0;  !heap.empty(); i++)
	{
		cout << heap.top() << ends;
		heap.pop();
	}
	cout << endl;

	cout << "size: " << heap.size() << " empty: " << heap.empty() << endl;
	return 0;
}