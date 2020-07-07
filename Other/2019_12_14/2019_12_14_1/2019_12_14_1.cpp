class PalindromeList {
public:
    bool chkPalindrome(ListNode* A) {
        ListNode* fast = A, *slow = A, *cur = NULL;
        
        while(fast && fast->next)
        {
                fast = fast->next->next;
                slow = slow->next;
        }
        cur = slow->next;
        
        while(cur)
        {
            ListNode* temp = cur->next;
            cur->next = slow;
            slow = cur;
            cur = temp;
        }
        
        while(A != slow)
        {
            if(A->val == slow->val)
            {
                slow = slow->next;
                A = A->next;
            }
            else if(A->next == slow)
                return true;
            else
            {
                return false;
            }
        }
        return true;    
    }
};
