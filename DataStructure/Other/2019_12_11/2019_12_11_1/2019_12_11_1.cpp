/*
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};*/
class Solution {
public:
    ListNode* FindKthToTail(ListNode* pListHead, unsigned int k) {
        ListNode* p = pListHead, *q = pListHead;
        if(pListHead == NULL || k == 0)
            return NULL;
        for(int i = 1; i < k; i++) 
        {
            if(NULL == p->next)
                return NULL;
            p = p->next;
        }

        while(p->next)
        {
            q = q->next;
            p = p->next;
        }
        
        return q;
    }
};
