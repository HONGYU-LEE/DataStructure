#include<unordered_map>
#include<string>
#include<vector>
#include<queue>
#include<iostream>
using namespace std;

namespace lee
{
    struct ACNode
    {
        ACNode(char data = '\0')
            : _data(data)
            , _isEnd(false)
            , _length(-1)
            , _fail(nullptr)
        {}

        char _data;		//当前字符
        bool _isEnd;	//标记当前是否能构成一个单词
        int _length;    //当前模式串长度
        ACNode* _fail;  //失败指针
        unordered_map<char, ACNode*> _subNode;	//子节点
    };

    class AC
    {
    public:
        AC()
            : _root(new ACNode())
        {}

        ~AC()
        {
            delete _root;
        }

        //防拷贝
        AC(const AC&) = delete;
        AC& operator=(const AC&) = delete;

        void buildFailurePointer();             //构建失败指针
        void match(const string& str) const;    //匹配模式串
        void insert(const string& str);         //插入字符串

    private:
        ACNode* _root;  //根节点
    };

    //插入字符串
    void AC::insert(const string& str)
    {
        if (str.empty())
        {
            return;
        }

        ACNode* cur = _root;
        for (size_t i = 0; i < str.size(); i++)
        {
            //如果找不到该字符，则在对应层中插入
            if (cur->_subNode.find(str[i]) == cur->_subNode.end())
            {
                cur->_subNode.insert(make_pair(str[i], new ACNode(str[i])));
            }
            cur = cur->_subNode[str[i]];
        }

        cur->_isEnd = true;         //标记该单词存在
        cur->_length = str.size();  //标记该单词长度
    }

    //构建失败指针
    void AC::buildFailurePointer()
    {
        //借助队列来完成层序遍历
        queue<ACNode*> q;
        q.push(_root);

        while (!q.empty())
        {
            ACNode* parent = q.front();
            q.pop();

            //遍历所有孩子节点
            for (auto& sub : parent->_subNode)
            {
                //如果父节点节点为根节点，则将孩子节点的失效指针全部设置为根节点
                if (parent == _root)
                {
                    sub.second->_fail = _root;
                }
                else
                {
                    ACNode* failParent = parent->_fail;    //父节点的失败指针

                    while (failParent != nullptr)
                    {
                        auto failChild = failParent->_subNode.find(sub.second->_data);    //寻找失败指针中是否存在一个子节点能与我们的子节点匹配

                        if (failChild != failParent->_subNode.end())   //如果存在，则这个子节点就是我们子节点的失败指针
                        {
                            sub.second->_fail = failChild->second;
                            break;
                        }
                        //如果找不到，则继续向上，寻找失败指针的失败指针是否有这么一个节点
                        failParent = failParent->_fail;
                    }
                    //如果一直找到最顶上也找不到，则将失败指针设置为根节点
                    if (failParent == nullptr)
                    {
                        sub.second->_fail = _root;
                    }
                }
                //将子节点加入队列中
                q.push(sub.second);
            }
        }
    }

    //匹配模式串
    void AC::match(const string& str) const
    {
        if (str.empty())
        {
            return;
        }

        ACNode* parent = _root;
        for (int i = 0; i < str.size(); i++)
        {
            ACNode* sub = parent->_subNode[str[i]];
            //如果子节点中找不到，则前往失败指针中寻找
            while (sub == nullptr && parent != _root)
            {
                parent = parent->_fail;
            }

            sub = parent->_subNode[str[i]];
            //如果还是找不到，则说明已经没有任何匹配的了，直接回到根节点
            if (sub == nullptr)
            {
                parent = _root;
            }
            else
            {
                parent = sub;   //继续查找下一个字符
            }

            ACNode* result = parent;
            while (result != _root)
            {
                //如果当前构成一个单词
                if (result->_isEnd == true)
                {
                    //输出匹配的模式串
                    cout << str.substr(i - result->_length + 1, result->_length) << endl;
                }
                result = result->_fail;     //如果无法构成一个单词，则继续前往失败指针中继续寻找
            }
        }
    }
};

int main()
{
    lee::AC ac;
    ac.insert("ass");
    ac.insert("fuck");
    ac.insert("shit");
    ac.insert("cao");
    ac.insert("sb");
    ac.insert("nmsl");
    ac.insert("dead");
    ac.buildFailurePointer();

    ac.match("fuckyou,nmslsb");
    return 0;
}