void quick_sort(vector<int>&v, int st, int dr)
{
    int i=st, j=dr, aux, mij=v[(st+dr)/2];
    while(i<=j)
    {
        while(v[i]<mij)
            i++;
        while(v[j]>mij)
            j--;
        if(i<=j)
        {
            aux=v[i];
            v[i]=v[j];
            v[j]=aux;
            i++;
            j--;
        }
    }
    if (st<j)
        quick_sort(v,st,j);
    if(dr>i)
        quick_sort(v,i,dr);
}
