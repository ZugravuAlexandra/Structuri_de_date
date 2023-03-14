def merge_sort(L):
    if len(L) > 1:
        mijloc = len(L) // 2
        stanga= L[:mijloc]
        dreapta= L[mijloc:]

        merge_sort(stanga)
        merge_sort(dreapta)

        i=j=k=0

        while i < len(stanga) and j < len(dreapta):
            if stanga[i]<dreapta[j]:
                L[k]=stanga[i]
                i+=1
            else:
                L[k]=dreapta[j]
                j+=1
            k+=1
        while i < len(stanga):
            L[k]=stanga[i]
            i+=1
            k+=1
        while j < len(dreapta):
            L[k]=dreapta[j]
            j+=1
            k+=1
    return L
L=[int(x) for x in input("elem ").split()]
print(merge_sort(L))
