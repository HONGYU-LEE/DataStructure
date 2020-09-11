struct Node* buildLinkedList(int* arr, int n)
{
    struct Node *head,*p,*s;
    int i=0;
    p = head = (struct Node *)malloc(sizeof(struct Node));
    for(i=0; i<n; i++)
    {
        s = (struct Node *)malloc(sizeof(struct Node));
        s->data = arr[i];
        s->link = NULL;
        p->link = s;
        p = s;
    }
    p->link = NULL;
    return head;
}
void printLinkedList(struct Node* head)
{
    head = head->link; 
    printf("%d",head->data);
	head=head->link;
    while(head != NULL)
    {
        printf(" %d",head->data);
		head=head->link;
    }
}
