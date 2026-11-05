#include <iostream>
#include <algorithm>

constexpr int MAXN = 1e6;

void SiftDown(int* ar, int n, int index) {

    bool is_parent_greater = false;
    while (index * 2 + 1 < n && is_parent_greater != true) {
        int left = index * 2 + 1;
        int bigchild = left;
        if (index * 2 + 2 < n && ar[left] < ar[index * 2 + 2]) {     
            bigchild = index * 2 + 2;
        }
        if (ar[index] < ar[bigchild]) {
            std::swap(ar[index], ar[bigchild]);
            index = bigchild;
        }
        else {
            is_parent_greater = true;
        }
    }

}

void HeapBuild(int* ar, int n) {

    int last_parent_index = (n - 2) / 2;
    // std::cout << last_parent_index << '\n';
    for (int i = last_parent_index; i >= 0; --i) {
        SiftDown(ar, n, i);
    }

}

void HeapSort(int* ar, int n) {

    for (int i = n - 1; i > 0; --i) {
        std::swap(ar[0], ar[i]);
        SiftDown(ar, i, 0);
    }

}

int main() {

    int ar[MAXN];
    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> ar[i];
    }

    HeapBuild(ar, n);

    // for (int i = 0; i < n; ++i) {
        // std::cout << ar[i] << ' ';
    // }
    // std::cout << '\n';

    HeapSort(ar, n);

    for (int i = 0; i < n; ++i) {
        std::cout << ar[i] << ' ';
    }
    std::cout << '\n';
    
    return 0;
}