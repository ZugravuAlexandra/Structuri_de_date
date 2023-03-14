def radix_sort(arr, base=10):
    maxi = max(arr)
    nr_cif = 0
    while maxi > 0:
        maxi = maxi // base
        nr_cif += 1
    for i in range(nr_cif):
        buckets = [[] for j in range(base)]
        for numar in arr:
            cifra = (numar // base**i) % base
            buckets[cifra].append(numar)
        arr = []
        for bucket in buckets:
            for numar in bucket:
                arr.append(numar)
    return arr


arr=[int(x) for x in input("Introduceti numerele: ").split()]
base=int(input("baza: "))
arr_sortat=radix_sort(arr,base)
print(arr_sortat)
