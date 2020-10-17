#include<iostream>
#include<string>
#include<vector>

using namespace std;



size_t getIndex(const string& str, int index)
{
    //如果超出字符串长度，则补零
    if(index >= str.size())
    {
        return 0;
    }
    return str[index];
}

void RadixSort(vector<string>& arr, int maxLen)
{
    vector<string> temp(arr);    //临时数组，用来保留每一趟的结果

    for(int i = maxLen - 1; i >= 0; i--)
    {
        vector<int> count(128, 0);  //统计数组

        //统计每种数字出现的次数
        for(int j = 0; j < arr.size(); j++)
        {
            int index = getIndex(arr[j], i);
            count[index]++;
        }

        //保证计数排序稳定，对数组变形，统计数组的每一个位置的值为前面所有数字的数量合
        //变形后每个位置的值即为该数据的排序的序号
        int sum = 0;
        for(int j = 0; j < count.size(); j++)
        {
            sum += count[j];
            count[j] = sum;
        }

        //按照原数组的数据的位置，倒序将数据放回原位，确保稳定性
        for(int j = arr.size() - 1; j >= 0; j--)
        {
            int index = getIndex(arr[j], i);
            temp[count[index] - 1] = arr[j];
            count[index]--;
        }
        arr = temp;
    }
    //arr = temp; //将临时数据拷贝回原数组
}
int main()
{
	vector<string> arr = { "hello", "world", "hellp", "hill", "ha", "path", "class", "alter" };

	RadixSort(arr, 5);
	
    for(auto& str : arr)
    {
        cout << str << ends;
    }
	return 0;
}
