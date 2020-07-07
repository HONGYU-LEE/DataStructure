int Length( List L )
{
    int n=0;
    List p = L;
    while(p != NULL)
    {
        n++;
        p = p->Next;
    }
    return n;
}
