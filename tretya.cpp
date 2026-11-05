#include <bits/stdc++.h>
#include <iostream>
using namespace std;

const int MAXN = 1'000'000;  // максимум n по условию
uint32_t arr[MAXN];

int64_t kvo = 0;

uint32_t cur = 0;              // текущее значение генератора

// Генератор 24-битных чисел по условию задачи
uint32_t nextRand24(uint32_t a, uint32_t b) {
    // 32-битные переполнения (uint32_t автоматически усекает до 2^32)
    cur = cur * a + b;
    return cur >> 8;  // берём старшие 24 бита (сдвиг вправо на 8)
}

void merge(uint32_t* ar, int l, int mid, int r) {
    int i = 0, j = 0;
    uint32_t res[r - l];
    
    while (l + i < mid && mid + j < r) {
        if (ar[l + i] <= ar[mid + j]) {
            res[i + j] = ar[l + i];
            i++;
        }
        else {
            res[i + j] = ar[mid + j];
            j++;
            kvo+=mid - (l + i);
        }
    }
    
    while (l + i < mid) {
        res[i + j] = ar[l + i];
        i++;
    }
    while (mid + j < r) {
        res [i + j] = ar[mid +j];
        j++;
    }

    for (int q = 0; q < i + j; ++q) {
        ar[l + q] = res[q];
    }
}

void mergesort(uint32_t* ar, int l, int r) {
    if (l + 1 >= r) {
        return;
    }

    int mid = (l + r) / 2;
    mergesort(ar, l, mid);
    mergesort(ar, mid, r);
    merge(ar, l, mid, r);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    uint32_t n, m, a, b;
    cin >> n >> m >> a >> b;

    // Генерируем n элементов
    for (uint32_t i = 0; i < n; i++) {
        uint32_t x = nextRand24(a, b) % m; // получаем 24-битное значение по модулю m
        arr[i] = x;                        // записываем в массив
    }

    // for (uint32_t i = 0; i < n; ++i) {
        // cout << arr[i] << ' ';
    // } 

    // cout << '\n';

    mergesort(arr, 0, n);
    
    // for (int i = 0; i < n; ++i) {
        // cout << arr[i] << ' ';
    // }   

    cout << kvo << '\n';
}