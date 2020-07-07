/*
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};*/
class Partition {
public:
    ListNode* partition(ListNode* pHead, int x) {
        ListNode* SmallList = (ListNode*)malloc(sizeof(ListNode));
        ListNode* BigList = (ListNode*)malloc(sizeof(ListNode));;
        ListNode* SmallHead = SmallList, *BigHead = BigList;
        
        while(pHead)
        {
            if(pHead->val < x)
            {
               SmallList->next = pHead;
               SmallList = pHead;
            }
            else
            {
               BigList->next = pHead;
               BigList = pHead;    
            }
            pHead = pHead->next;
        }
        BigList->next = NULL;
        SmallList->next = BigHead->next;
        
        return SmallHead->next;
    }
};
