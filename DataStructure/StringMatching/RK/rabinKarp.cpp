#include<string>
#include<iostream>

using namespace std;

//字符串哈希函数，这里使用的是最简单的按位相加
int hashFunc(const string& str)
{
    int hashCode = 0;
    for(int i = 0; i < str.size(); i++)
    {
        hashCode += (str[i] - 'a');
    }

    return hashCode;
}

//获取移动到下一个位置后的字符串哈希值，即减去开头的哈希值，加上末尾的哈希值
int nextHash(const string& str, int hash, int begin, int end)
{
    hash -= (str[begin] - 'a');
    hash += (str[end] - 'a');

    return hash;
}

int rabinKarp(const string& str, const string& pattern)
{
    //不满足条件则直接返回false
    if(str.empty() || pattern.empty() || str.size() < pattern.size())
    {
        return -1;
    }

    int len1 = str.size(), len2 = pattern.size();
    int patternHash = hashFunc(pattern);
    int subHash = hashFunc(str.substr(0, len2));

    for(int i = 0; i < (len1 - len2 + 1); i++)
    {
        //如果当前的哈希值相同，则遍历比较字符串是否也相同，如果不同则没有必要进行比较
        if(patternHash == subHash && pattern == str.substr(i, len2))
        {
            return i;   //如果当前匹配，则返回匹配主串的起始位置
        }

        //如果主串中剩余字符还能与模式串进行对比，则更新哈希值
        if(len1 - i > len2)
        {
            subHash = nextHash(str, subHash, i, i + len2);
        }
    }

    return -1;
}

int main()
{
    string s1, s2;
    while(cin >> s1 >> s2)
    {
        cout << rabinKarp(s1, s2) << endl;
    }
    
    return 0;
}