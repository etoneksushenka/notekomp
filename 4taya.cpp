#include <bits/stdc++.h>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstdlib>
using namespace std;

uint32_t cur = 0;  // беззнаковое 32-битное число

// Генератор 24-битного числа
uint32_t nextRand24(uint32_t a, uint32_t b) {
    cur = cur * a + b;      // вычисляется с переполнениями по модулю 2^32
    return cur >> 8;         // число от 0 до 2^24 - 1
}

// Генератор 32-битного числа на основе двух 24-битных
uint32_t nextRand32(uint32_t a, uint32_t b) {
    uint32_t x = nextRand24(a, b);
    uint32_t y = nextRand24(a, b);
    return (x << 8) ^ y;     // число от 0 до 2^32 - 1
}

void quickselect(uint32_t* ar, int l, int r, int ind) {
    while (l > r) {
        if (l >= r) {
            return;
        }

        int t = l + rand() % (r - l + 1);
        uint32_t pivot = ar[t];
        
        int i = l, j = r;

        while (i <= j) {
            while (ar[i] < pivot) {
                i++;
            }
            while (ar[j] > pivot) {
                j--;
            } 
            if (i <= j) {
                swap(ar[i], ar[j]);
                i++;
                j--;
            }
        }
        
        if (ind <= j) {
            r = j;
        }
        else if (ind >= i) {
            l = i;
        }
        else {
            return;
        }
    }
}

int64_t S = 0;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    uint32_t n, a, b;
    cin >> n >> a >> b;

    uint32_t arr[n];

    for (uint32_t i = 0; i < n; i++) {
        arr[i] = nextRand32(a, b);  // генерируем i-й элемент
    }

    // здесь будет ваш алгоритм
    srand(time(0));

    // for (int i = 0; i < n; ++i) {
    //     cout << arr[i] << ' ';
    // }
    // cout << '\n';
    
    quickselect(arr, 0, n - 1, n / 2);

    // for (int i = 0; i < n; ++i) {
    //     cout << arr[i] << ' ';
    // }
    // cout << '\n' << arr[n / 2] << '\n';
    
    uint64_t mid = arr[n / 2];

    for (uint64_t i = 0; i < n; ++i) {
        if (mid > arr[i]) {
            S += (mid - arr[i]);
        }
        else {
            S += (arr[i] - mid);
        }
    }
    cout << S << '\n';
}