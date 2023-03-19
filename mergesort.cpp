#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void mergesort(vector<int>& v, int st, int m, int dr)
{
    int *b = new int[dr-st+1];
    int i, j, k=0;
    i=st;
    j = m+1;

    while (i <= m && j <= dr)
        if (v[i] > v[j])
            b[k++] = v[j++];
        else
            b[k++] = v[i++];

    while (i <= m)
        b[k++] = v[i++];

    while (j<=dr)
        b[k++] = v[j++];

    k=0;
    for(i=st; i<=dr; i++)
        v[i]=b[k++];

    /// dezalocare vector
    delete[] b;
}

void merge(vector<int>& v, int st, int dr)
{
    if (st < dr)
    {
        int m = st+(dr-st) / 2;
        merge(v, st, m);
        merge(v, m + 1, dr);
        mergesort(v, st, m, dr);
    }
}

int main()
{
    vector<int> a;
    ifstream fin("numere.txt");
    int x;
    while (fin >> x)
    {
        a.push_back(x);
    }
    fin.close();

    merge(a, 0, a.size() - 1);

    for (int i = 0; i < a.size(); i++)
    {
        cout << a[i] << " ";
    }

    return 0;
}
