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

		char _data;		//��ǰ�ַ�
		bool _isEnd;	//��ǵ�ǰ�Ƿ��ܹ���һ������
		unordered_map<char, TrieNode*> _subNode;	//�ӽڵ�
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

		//������
		TrieTree(const TrieTree&) = delete;
		TrieTree& operator=(const TrieTree&) = delete;

		//�����ַ���
		void insert(const string& str)
		{
			if (str.empty())
			{
				return;
			}

			TrieNode* cur = _root;
			for (size_t i = 0; i < str.size(); i++)
			{
				//����Ҳ������ַ������ڶ�Ӧ���в���
				if (cur->_subNode.find(str[i]) == cur->_subNode.end())
				{
					cur->_subNode.insert(make_pair(str[i], new TrieNode(str[i])));
				}
				cur = cur->_subNode[str[i]];
			}
			//��Ǹõ��ʴ���
			cur->_isEnd = true;
		}

		//�����ַ���
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
			//�����ǰƥ�䵽����һ��ǰ׺����һ�������ĵ��ʣ��򷵻ش���
			return cur->_isEnd == true ? true : false;
		}

		//�����Ƿ�����԰���strΪǰ׺���ַ���
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

		//����������strΪǰ׺���ַ���
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
		//ʹ�û������ҵ����а�����ǰ׺���ַ���
		void _getPrefixWords(TrieNode* cur, string& str, vector<string>& res)
		{
			//�����ǰ�ܹ���һ�����ʣ������������
			if (cur->_isEnd)
			{
				res.push_back(str);
			}

			//ƥ�䵱ǰ���п����ַ�
			for (const auto& sub : cur->_subNode)
			{
				str.push_back(sub.first);	//ƥ�䵱ǰ�ַ�
				_getPrefixWords(sub.second, str, res);	//ƥ����һ���ַ�
				str.pop_back();	//���ݣ������������
			}
		}

		TrieNode* _root;	//���ڵ㣬�洢���ַ�
	};
};