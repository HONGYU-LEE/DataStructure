#include<unordered_map>
#include<string>
#include<vector>

using std::vector;
using std::string;
using std::unordered_map;
using std::make_pair;

namespace lee
{
	struct TrieNode
	{
		TrieNode(char data = '\0')
			: _data(data)
			, _isEnd(false)
		{}

		char _data;		//当前字符
		bool _isEnd;	//标记当前是否能构成一个单词
		unordered_map<char, TrieNode*> _subNode;	//子节点
	};

	class TrieTree
	{
	public:
		TrieTree()
			: _root(new TrieNode())
		{}

		~TrieTree()
		{
			delete _root;
		}

		//防拷贝
		TrieTree(const TrieTree&) = delete;
		TrieTree& operator=(const TrieTree&) = delete;

		//插入字符串
		void insert(const string& str)
		{
			if (str.empty())
			{
				return;
			}

			TrieNode* cur = _root;
			for (size_t i = 0; i < str.size(); i++)
			{
				//如果找不到该字符，则在对应层中插入
				if (cur->_subNode.find(str[i]) == cur->_subNode.end())
				{
					cur->_subNode.insert(make_pair(str[i], new TrieNode(str[i])));
				}
				cur = cur->_subNode[str[i]];
			}
			//标记该单词存在
			cur->_isEnd = true;
		}

		//查找字符串
		bool find(const string& str)
		{
			if (str.empty())
			{
				return false;
			}

			TrieNode* cur = _root;
			for (size_t i = 0; i < str.size(); i++)
			{
				if (cur->_subNode.find(str[i]) == cur->_subNode.end())
				{
					return false;
				}
				cur = cur->_subNode[str[i]];
			}
			//如果当前匹配到的是一个前缀而非一个完整的单词，则返回错误
			return cur->_isEnd == true ? true : false;
		}

		//查找是否存在以包含str为前缀的字符串
		bool startsWith(const string& str)
		{
			if (str.empty())
			{
				return false;
			}

			TrieNode* cur = _root;
			for (size_t i = 0; i < str.size(); i++)
			{
				if (cur->_subNode.find(str[i]) == cur->_subNode.end())
				{
					return false;
				}
				cur = cur->_subNode[str[i]];
			}
			return true;
		}

		//返回所有以str为前缀的字符串
		vector<string> getPrefixWords(const string& str)
		{
			if (str.empty())
			{
				return {};
			}

			TrieNode* cur = _root;
			for (size_t i = 0; i < str.size(); i++)
			{
				if (cur->_subNode.find(str[i]) == cur->_subNode.end())
				{
					return {};
				}
				cur = cur->_subNode[str[i]];
			}
			vector<string> res;
			string s = str;

			_getPrefixWords(cur, s, res);
			
			return res;
		}

	private:
		//使用回溯来找到所有包含该前缀的字符串
		void _getPrefixWords(TrieNode* cur, string& str, vector<string>& res)
		{
			//如果当前能构成一个单词，则加入结果集中
			if (cur->_isEnd)
			{
				res.push_back(str);
			}

			//匹配当前所有可能字符
			for (const auto& sub : cur->_subNode)
			{
				str.push_back(sub.first);	//匹配当前字符
				_getPrefixWords(sub.second, str, res);	//匹配下一个字符
				str.pop_back();	//回溯，尝试其他结果
			}
		}

		TrieNode* _root;	//根节点，存储空字符
	};
};