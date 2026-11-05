#include <iostream>

struct Name {
    int t;
    int f;
    // int t2;
};

struct Core {
    int finish;
    int rate;
};

constexpr int MAXN = 3 * 1e5;

int arn[MAXN + 1];
Name arm[MAXN + 1];
Core cores[MAXN + 1];

void minSiftDown(int* ar, int n, int index) {
    bool is_parent_greater = false;
    while (index * 2 + 1 < n && is_parent_greater == false) {
        int left = index * 2 + 1;
        int max_child = left;
        if (index * 2 + 2 < n && ar[index * 2 + 2] < ar[left]) {
            max_child = index * 2 + 2;
        } 
        if (ar[index] > ar[max_child]) {
            std::swap(ar[index], ar[max_child]);
            index = max_child;
        }
        else {
            is_parent_greater = true;
        }
    }
}

void minSiftDown2(Core* ar, int n, int index) {
    bool is_parent_greater = false;
    while (index * 2 + 1 < n && is_parent_greater == false) {
        int left = index * 2 + 1;
        int max_child = left;
        if (index * 2 + 2 < n && ar[index * 2 + 2].finish < ar[left].finish) {
            max_child = index * 2 + 2;
        } 
        if (ar[index].finish > ar[max_child].finish) {
            std::swap(ar[index], ar[max_child]);
            index = max_child;
        }
        else {
            is_parent_greater = true;
        }
    }
}

void minSiftUp(int* ar, int index) {
    bool is_child_lower = false;
    while (index > 0 && is_child_lower == false) {
        int parent = (index - 1) / 2;
        if (ar[index] < ar[parent]) {
            std::swap(ar[index], ar[parent]);
            index = parent;
        }
        else {
            is_child_lower = true;
        }
    }
}

void minSiftUp2(Core* ar, int index) {
    bool is_child_lower = false;
    while (index > 0 && is_child_lower == false) {
        int parent = (index - 1) / 2;
        if (ar[index].finish < ar[parent].finish) {
            std::swap(ar[index], ar[parent]);
            index = parent;
        }
        else {
            is_child_lower = true;
        }
    }
}

void HeapBuild(int* ar, int n) {
    int lastindex = (n - 2) / 2;
    for (int i = lastindex; i >= 0; --i) {
        minSiftDown(ar, n, i);
    }
}

int main() {
    long long sum = 0;
    int n, m;
    std::cin >> n >> m;
    int coresize = 0;
    int freesize = n;
    for (int i = 0; i < n; ++i) {
        std::cin >> arn[i];
    }
    HeapBuild(arn, n);
    for (int i = 0; i < m; ++i) {
        std::cin >> arm[i].t >> arm[i].f;
        // arm[i].t2 = arm[i].t + arm[i].f;
    }
    for (int i = 0; i < m; ++i) {
        while (coresize > 0 && cores[0].finish <= arm[i].t) {
            Core temp = cores[0];
            cores[0] = cores[coresize - 1];
            coresize--;
            if (coresize > 0) {
                minSiftDown2(cores, coresize, 0);
            }
            arn[freesize] = temp.rate;
            minSiftUp(arn, freesize);
            freesize++;
        }
        if (freesize > 0) {
            int rate = arn[0];
            arn[0] = arn[freesize - 1];
            freesize--;
            if (freesize > 0) {
                minSiftDown(arn, freesize, 0);
            }
            sum += 1LL * rate * arm[i].f;
            cores[coresize].finish = arm[i].t + arm[i].f;
            cores[coresize].rate = rate;
            minSiftUp2(cores, coresize);
            coresize++;
        }
    }
    std::cout << sum << '\n';
}