# Varianta 1
def poz(l,p,u):
    i=p
    j=u
    d1=0
    d2=-1
    while i<j:
        if l[i]>l[j]:
            l[i],l[j]=l[j],l[i]
            d1,d2=-d2,-d1
        i=i+d1
        j=j+d2
    return i
def quick_sort(l,p,u):
    if p>=u:
        return
    m=poz(l,p,u)
    quick_sort(l,p,m-1)
    quick_sort(l,m+1,u)
l=[2,4,4,3,5]
quick_sort(l,1,4)
print(l)

# varianta 2
def quicksort(L):
    elem=len(L)
    if elem <=1:
        return L
    pivot=L[0]
    #print(pivot)
    stanga=[x for x in L if x < pivot]
    #print(stanga)
    dreapta=[x for x in L if x > pivot]
    print(dreapta)
    mijloc=[x for x in L if x==pivot]
    #print(mijloc)
    return quicksort(stanga) + mijloc + quicksort(dreapta)

L=[int(x) for x in input("elem ").split()]
print(quicksort(L))
