void shell_sort(vector<int>& v) {
    /// n -> numarul de elemente din vector
    int n = v.size();
    /// k -> gap-ul care tot o sa scada pana la 0
    /// i -> incepe de la a doua jumatate a vectorului
    int i,j,aux,k;
    for(k=n/2;k>0;k=k/2)
    /// sortam " din k in k elemente "
        for(i=k;i<n;i++)
    {
        j=i-k;
        aux=v[i];
        while(j>=0 && v[j]>aux)
        {
            v[j+k]=v[j];
            j=j-k;
        }
        v[j+k]=aux;
    }
}
