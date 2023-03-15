#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void mergesort(vector<int>& a, int st, int m, int dr)
{
    int b[100];
    int i, j, k;
    i = 0; j = st;
    /// copiem prima jumatate a vectorului a in b
    while (j <= m)
        b[i++] = a[j++];
    i = 0; k = st;
    /// copiem inapoi cel mai mare element la fiecare pas
    while (k < j && j <= dr)
        if (b[i] <= a[j])
            a[k++] = b[i++];
        else
            a[k++] = a[j++];
    /// copiem elementele ramase daca mai exista
    while (k < j)
        a[k++] = b[i++];
}

void merge(vector<int>& a, int st, int dr)
{
    if (st < dr)
    {
        int m = (st + dr) / 2;
        merge(a, st, m);
        merge(a, m + 1, dr);
        mergesort(a, st, m, dr);
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
