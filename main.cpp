#include <iostream> 
#include <algorithm>
#include <cstdlib>
#include <ctime>

struct pair {
    int x;
    int y;
    int index;
};

void quicksort(pair* ar, int l, int r) {
    if (l >= r) {
        return;
    }
    
    int t = l + rand() % (r - l + 1);
    int pivotx = ar[t].x;
    int pivoty = ar[t].y;

    int i = l, j = r;
    
    while (i <= j) {
        while (ar[i].x > pivotx || (ar[i].x == pivotx 
            && ar[i].y > pivoty)) {
            i++;
        }
        while (pivotx > ar[j].x || (ar[j].x == pivotx 
            && ar[j].y < pivoty)) {
            j--;
        }
        if (i <= j) {
           std::swap(ar[i], ar[j]);
           i++;
           j--; 
        }
    }

    if (l < j) {
        quicksort(ar, l, j);
    }
    if (i < r) {
        quicksort(ar, i, r);
    }
}

const int maxn = 500000;
int headliners[maxn];

int main() {
    int n;
    std::cin >> n;
    pair ar[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> ar[i].x >> ar[i].y;
        ar[i].index = i + 1;
    }
    
    quicksort(ar, 0, n - 1);

    // std::cout << '\n';
    // for (int i = 0; i < n; ++i) {
        // std::cout << ar[i].x << ' ' << ar[i].y << " " << ar[i].index << '\n';
    // }

    headliners[0] = ar[0].index;
    int ind = 1;
    int ymax = ar[0].y;

    for (int i = 1; i < n; ++i) {
        if (ar[i].y > ymax) {
            headliners[ind] = ar[i].index;
            ind++;
            ymax = ar[i].y;
        }
    }

    std::cout << ind << '\n';
    for (int i = 0; i < ind; ++i) {
        std::cout << headliners[i] << ' ';
    }
}