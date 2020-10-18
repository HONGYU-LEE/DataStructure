#include<string>
#include<iostream>
#include<vector>

using namespace std;

//构建坏后缀规则的下标数组
void generateBC(const string& pattern, vector<int>& indexArr)
{
    //记录模式串中每个下标最后出现的位置
    for(int i = 0; i < pattern.size(); i++)
    {
        indexArr[pattern[i]] = i; 
    }
}

//构建好后缀规则的前缀和后缀数组
void generateGS(const string& pattern, vector<int>& suffix, vector<bool>& prefix)
{
    int len = suffix.size();

    //匹配区间[0 ~ len - 1],len时即为整个模式串，不可能存在前缀
    for(int i = 0; i < len - 1; i++)
    {
        int j = i;
        int size = 0;

        while(j >= 0 && pattern[j] == pattern[len - 1 - size])
        {
            //继续匹配下一个位置
            j--;    
            size++; 

            suffix[size] = j + 1;   //记录匹配后缀的子串的位置
        }
        //如果子串一直匹配到开头，则说明该子串为前缀，此时前缀与后缀匹配
        if(j == -1)
        {
            prefix[size] = true;
        }
    }
}

int moveByGS(int index, const vector<int>& suffix, const vector<bool>& prefix)
{
    int len = suffix.size();    //模式串长度
    int size = len - 1 - index;   //后缀长度
    //如果存在与后缀匹配的子串，则直接返回它们的偏移量
    if(suffix[size] != -1)
    {
        return index - suffix[size] + 1;
    }

    //如果没有匹配的后缀，那么判断后缀中是否有部分与前缀匹配
    for(int i = index + 2; i <= len - 1; i++)
    {
        if(prefix[len - i] == true)
        {
            return i;
        }
    }
    //如果也不存在，则说明没有任何匹配，直接偏移整个模式串的长度
    return len;
}

int boyerMoore(const string& str, const string& pattern)
{
    //不满足条件则直接返回false
    if(str.empty() || pattern.empty() || str.size() < pattern.size())
    {
        return -1;
    }
    
    int len1 = str.size(), len2 = pattern.size();
    vector<int> indexArr(128, -1);    //标记匹配坏字符的字符下标
    vector<int> suffix(len2, -1);       //标记匹配后缀的子串下标
    vector<bool> prefix(len2, false);        //标记是否匹配前缀
    generateBC(pattern, indexArr);
    generateGS(pattern, suffix, prefix);

    int i = 0;
    while(len1 - i >= len2)
    {
        int j;
        //模式串从后往前匹配
        for(j = len2 - 1; j >= 0; j--)
        {
            //如果当前字符不匹配
            if(str[i + j] != pattern[j])
            {
                break;
            }
        }
        //如果全部匹配，则返回主串起始位置
        if(j < 0)
        {
            return i;
        }
        int badMove = (j - indexArr[str[i + j]]); //坏后缀规则偏移量
        badMove = (badMove == 0) ? 1 : badMove;   //防止倒退
        int goodMove = 0;   //好后缀规则偏移量

        //如果一个都不匹配，则不存在后缀
        if(j < len2 - 1)
        {
            goodMove = moveByGS(j, suffix, prefix);   //计算出好后缀的偏移量
        }

        i += max(goodMove, badMove);  //加上最大的那个
    }
    return -1;
}

int main()
{
    string s1, s2;
    while(cin >> s1 >> s2)
    {
        cout << boyerMoore(s1, s2) << endl;
    }
    
    return 0;
}