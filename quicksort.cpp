#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>


void quicksort(int* ar, int l, int r) {
    if ( l >= r) {
        return;
    }
    
    int t = l + rand() % (r - l + 1);
    // int mid = (l + r) / 2;
    // std::swap(ar[t], ar[mid]);
    int pivot = ar[t];

    int i = l;
    int j = r;

    while (i <= j) {
        while (ar[i] < pivot) {
            i++;
        }
        while (ar[j] > pivot) {
            j--;
        }
        if (i < j) {
            std::swap(ar[i], ar[j]);
            i++;
            j--;
        }
    }
    if (l < j) {
        quicksort(ar, l, j);
    }
    if (r > i) {
        quicksort(ar, i, r);
    }

    
}

int main() {
    srand(time(0));
    
    int n;
    std::cin >> n;
    int ar[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> ar[i];
    }

    quicksort(ar, 0, n - 1);

    for (int i = 0; i < n; ++i) {
        std::cout << ar[i] << " ";
    }

    std::cout << '\n';
}