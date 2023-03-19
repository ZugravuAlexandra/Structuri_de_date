#include <iostream>
#include <fstream>
#include <vector>
#include <chrono> // clock


using namespace std;

void radixSort(vector<int>& v, int base)
{
    ///initializam un vector de vectori care are marimea base
    vector<vector<int>>buckets(base);
    long long exp=1;
    int n = v.size();
    int i,j;
    while(buckets[0].size()!=n)
    {
        for(i=0; i<base; i++)
            buckets[i].clear();
        /// eliberam fiecare compartiment din buckets inainte de fiecare iteratie ca sa nu existe nr ramase din iteratiile anterioare

        for(i=0; i<n; i++)
            buckets[v[i]/exp%base].push_back(v[i]);
        /// punem fiecare numar in v, bazat pe cifra curenta care este determinata prin impartirea la exp si restul de la impartirea cu base

        int k = 0;
        for(i = 0; i < base; i++)
        {
            for(j = 0; j < buckets[i].size(); j++)
                v[k++] = buckets[i][j];
        }
        ///punem numarul in ordinea corecta in vectorul v
        ///folosim k pentru a tine cont de pozitia corecta in vectorul de intrare

        exp *= base;
    }
    return;

}

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

void shell_sort(vector<int>& v)
{
    /// n -> numarul de elemente din vector
    int n = v.size();
    /// k -> gap-ul care tot o sa scada pana la 0
    /// i -> incepe de la a doua jumatate a vectorului
    int i,j,aux,k;
    for(k=n/2; k>0; k=k/2)
        /// sortam " din k in k elemente "
        for(i=k; i<n; i++)
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

void heapfy(vector<int>& v, int i, int n)
{
    int l = 2*i+1;
    int r = 2*i+2;
    int maxi = i;

    if (l < n && v[l] > v[maxi])
        maxi = l;

    if (r < n && v[r] > v[maxi])
        maxi = r;

    if (maxi != i)
    {
        swap(v[i], v[maxi]);
        heapfy(v, maxi, n);
    }
}

void max_heap(vector<int>& v)
{
    int n = v.size();
    for (int i = n/2 - 1; i >= 0; i--)
        heapfy(v, i, n);
}

void heap_sort(vector<int>& v)
{
    int n = v.size();
    max_heap(v);
    for (int i = n - 1; i >= 1; i--)
    {
        swap(v[0], v[i]);
        n=n-1;
        heapfy(v, 0, i);
    }

}

void insertion_sort(vector<int>&v)
{
    int i, j,k;
    int n=v.size();
    for(i=1; i<n; i++)
    {
        j=i-1;
        k=v[i];
        while(j>=0 && k<v[j])
        {
            v[j+1]=v[j];
            j--;
        }
        v[j+1]=k;
    }
}

int main()
{
    vector<int> v;
    ifstream fin("r_10000000.txt");
    int x;
    while (fin >> x)
    {
        v.push_back(x);
    }
    fin.close();
    int st=0, dr=v.size()-1;
    double s=0;
    for (int i=0; i<8; i++)
    {
        auto begin = std::chrono::high_resolution_clock::now();
        ///radixSort(v,1<<16);
        ///merge(v, 0, v.size() - 1);
        shell_sort(v);
        ///heap_sort(v);
        ///insertion_sort(v);
        auto end = std::chrono::high_resolution_clock::now();
        chrono::duration<double> elapsedSeconds = end - begin;
        cout<<elapsedSeconds.count()<<endl;
        s+=elapsedSeconds.count();
    }
    double avg=s/8;
    cout<<avg;

    /*
            for (int i = 0; i < v.size(); i++)
            {
                cout << v[i] << " ";
            }
    */
    return 0;
}
