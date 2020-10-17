#include<string>
#include<iostream>

using namespace std;

int bruteForce(const string& str, const string& pattern)
{
    //不满足条件则直接返回false
    if(str.empty() || pattern.empty() || str.size() < pattern.size())
    {
        return -1;
    }

    int i = 0, j = 0;
    int len1 = str.size(), len2 = pattern.size();
    
    while(i < str.size())
    {
        while(j < pattern.size())
        {
            //如果当前不匹配
            if(str[i + j] != pattern[j])
            {
                i++;    //主串移动到下一个位置
                j = 0;  //模式串回到起始位置
                break;
            }
            j++;    //如果模式串当前位置匹配，则继续匹配下一个位置
        }
        //如果模式串全部匹配，则返回匹配的位置
        if(j == pattern.size())
        {
            return i;
        }
    }
    return -1;
}

int main()
{
    string s1, s2;
    while(cin >> s1 >> s2)
    {
        cout << bruteForce(s1, s2) << endl;
    }
    
    return 0;
}