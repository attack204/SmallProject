quicksort(A, l, r) {
    if l < r:
    then q <- partition(A, l, r)
    quicksort(A, l, q - 1)
    quicksort(A, l + 1, r)
}
partition(A, l, r) {
    x <- A[r]
    i <- l-1  
    for j <- l to r-1 
        do if A[j] <= x
            then i++;
            swap(A[i], A[j])
            swap(A[i+1], A[r])
    return i + 1
}