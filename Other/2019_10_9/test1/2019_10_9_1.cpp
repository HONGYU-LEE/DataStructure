List Reverse( List L )
{
    List p,t,s;
    p = L;
    if(p == NULL) 
        return NULL;
    s = p->Next;
    p->Next = NULL; 
    while(s!= NULL)
    {
        t = s->Next;
        s->Next = p;
        p = s;
        s = t;
    }

    L = p;
    return L;
}
