#include<unordered_map>
#include<list>

using namespace std;

class LFUNode
{
public:
    LFUNode(int key, int value, int freq)
        : _key(key)
        , _value(value)
        , _freq(freq)
    {}

    int _key;   
    int _value;
    int _freq;  //访问次数
};

class LFUCache {
public:
    LFUCache(int capacity) 
        : _capacity(capacity)
        , _minFreq(0)
    {}
    
    int get(int key) 
    {
        if(_capacity == 0)
        {
            return -1;
        }

        auto it = _keyTable.find(key);  //查找到对应的节点
        if(it != _keyTable.end())
        {
            list<LFUNode>::iterator node = it->second;         //记录节点的value以及freq
            int value = node->_value, freq = node->_freq;

            _freqTable[freq].erase(node); //从freq表中的对应链表删除当前节点
            if(_freqTable[freq].empty() && _minFreq == freq)  //如果删除后链表为空，则判断是否需要更新最小freq
            {
                _minFreq++;
            }

            _freqTable[freq + 1].push_front(LFUNode(key, value, freq + 1)); //讲更新后的节点头插入下一个freq的链表中，保证按照插入时间排序
            it->second = _freqTable[freq + 1].begin();  //更新迭代器

            return value;
        }
        else
        {
            return -1;
        }
    }
    
    void put(int key, int value) 
    {
        if(_capacity == 0)
        {
            return;
        }

        auto it = _keyTable.find(key);  //查找key是否存在，判断是更新还是插入
        if(it != _keyTable.end())   //如果存在，则是更新
        {
            list<LFUNode>::iterator node = it->second;
            int freq = node->_freq;
            
            _freqTable[freq].erase(node);
            if(_freqTable[freq].empty() && _minFreq == freq)
            {
                _minFreq++;
            }

            _freqTable[freq + 1].push_front(LFUNode(key, value, freq + 1));
            it->second = _freqTable[freq + 1].begin();
        }
        else    //不存在则是插入
        {
            //如果缓存满了，则要先删除后才能插入
            if(_keyTable.size() == _capacity)
            {
                //查询freq表，获取freq最少且最久没有使用的节点，即freq链表的尾部节点
                LFUNode node = _freqTable[_minFreq].back();
                _keyTable.erase(node._key);        //删除key表中的节点
                _freqTable[node._freq].pop_back();  //删除freq表中的节点
            }

            _freqTable[1].push_front(LFUNode(key, value, 1));          //在freq表中插入新节点
            _keyTable.insert(make_pair(key, _freqTable[1].begin()));//在key表中插入新节点
            _minFreq = 1;   //插入新元素，它为最小的
        }
    }
private:
    unordered_map<int, list<LFUNode>::iterator> _keyTable;  //建立key与节点的映射
    unordered_map<int, list<LFUNode>> _freqTable;           //建立freq与节点的映射
    int _minFreq;   //保存当前最小的freq，便于查询
    int _capacity;  //缓存最大容量
};
