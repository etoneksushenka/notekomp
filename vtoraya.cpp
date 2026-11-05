    #include <iostream>

struct Pair {
    int first;
    int second;
    int index;
};

void merge(Pair* ar, int l, int mid, int r) {
    int i = 0, j = 0;
    Pair res[r - l];

    while (l + i < mid && mid + j < r) {
        if (ar[l + i].first < ar[mid + j].first) {
            res[i + j] = ar[l + i];
            i++;
        }
        else if (ar[l + i].first == ar[mid + j].first) {
            if (ar[l + i].second <= ar[mid + j].second) {
                res[i + j] = ar[l + i];
                i++;
            }
            else {
                res[i + j] = ar[mid + j];
                j++;
            }
        }
        else {
            res[i + j] = ar[mid + j];
            j++;
        }
    }

    while (l + i < mid) {
        res[i + j] = ar[l + i];
        i++;
    }
    while (mid + j < r) {
        res[i + j] = ar[mid + j];
        j++;
    }

    for (int a = 0; a < i + j; ++a) {
        ar[l + a] = res[a];
    }
}

void mergesort(Pair* ar, int l, int r) {
    if (l + 1 >= r) {
        return;
    } 

    int mid = (l+r) / 2;
    mergesort(ar, l, mid);
    mergesort(ar, mid, r);
    merge(ar, l, mid, r);
}



int main() {
    int n;
    std::cin >> n;
    Pair ar[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> ar[i].first >> ar[i].second;
        ar[i].index = i+1;
    }
    
    mergesort(ar, 0, n);

    for (int i = 0; i < n; ++i) {
        std::cout << ar[i].index << ' ';
    }
    std::cout << '\n';
}