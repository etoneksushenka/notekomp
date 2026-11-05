#include <iostream>
// #include <cmath>

constexpr int MAXN = 1e5;

struct Name {
    int value;
    int id;
};

void maxSiftDown(Name* ar, int n, int index) {
    bool is_parent_greater = false;
    while (index * 2 + 1 < n && is_parent_greater == false) {
        int left = index * 2 + 1;
        int max_child = left;
        if (index * 2 + 2 < n && ar[index * 2 + 2].value > ar[left].value) {
            max_child = index * 2 + 2;
        } 
        if (ar[index].value < ar[max_child].value) {
            std::swap(ar[index], ar[max_child]);
            index = max_child;
        }
        else {
            is_parent_greater = true;
        }
    }
}

void minSiftDown(Name* ar, int n, int index) {
    bool is_parent_greater = false;
    while (index * 2 + 1 < n && is_parent_greater == false) {
        int left = index * 2 + 1;
        int max_child = left;
        if (index * 2 + 2 < n && ar[index * 2 + 2].value < ar[left].value) {
            max_child = index * 2 + 2;
        } 
        if (ar[index].value > ar[max_child].value) {
            std::swap(ar[index], ar[max_child]);
            index = max_child;
        }
        else {
            is_parent_greater = true;
        }
    }
}

void minSiftUp(Name* ar, int index) {
    bool is_child_lower = false;
    while (index > 0 && is_child_lower == false) {
        int parent = (index - 1) / 2;
        if (ar[index].value < ar[parent].value) {
            std::swap(ar[index], ar[parent]);
            index = parent;
        }
        else {
            is_child_lower = true;
        }
    }
}

void maxSiftUp(Name* ar, int index) {
    bool is_child_lower = false;
    while (index > 0 && is_child_lower == false) {
        int parent = (index - 1) / 2;
        if (ar[index].value > ar[parent].value) {
            std::swap(ar[index], ar[parent]);
            index = parent;
        }
        else {
            is_child_lower = true;
        }
    }
}

int ReadNumber(char* str) {
    int i = 7, sum = 0;
    bool is_negative = false;
    while (str[i] != ')') {
        if (str[i] == '-') {
            is_negative = true;
            i++;
        }
        sum = ((str[i] - '0') + 10 * sum);
        i++;
    }
    if (is_negative) {
        return -sum;
    }
    return sum;
}

int main() {
    Name minHeap[MAXN];
    Name maxHeap[MAXN];
    bool alive[MAXN] = {};
    int minSize = 0, maxSize = 0;
    int idCount = 0;
    // int ar[MAXN];
    // int size = 0;
    // for (int i = 0; i < 10; ++i) {
        // std::cout << alive[i] << ' ';
    // }
    int n;
    std::cin >> n;
    for (int j = 0; j < n; ++j) {
        char command[20];
        std::cin >> command;
        Name x;
        if (command[0] == 'I') {
            x.value = ReadNumber(command);
            x.id = idCount;
            idCount++;

            maxHeap[maxSize] = x;
            maxSiftUp(maxHeap, maxSize);
            maxSize++;

            minHeap[minSize] = x;
            minSiftUp(minHeap, minSize);
            minSize++;

            alive[x.id] = true;
        }
        else if (command[0] == 'G' && command[5] == 'n') {
            while (alive[minHeap[0].id] != true) {
                minHeap[0] = minHeap[minSize - 1];
                minSize--;
                minSiftDown(minHeap, minSize, 0);
            }
            std::cout << minHeap[0].value << '\n';
            alive[minHeap[0].id] = false;
            minHeap[0] = minHeap[minSize - 1];
            minSize--;
            minSiftDown(minHeap, minSize, 0);
        }
        else {
            while (alive[maxHeap[0].id] != true) {
                maxHeap[0] = maxHeap[maxSize - 1];
                maxSize--;
                maxSiftDown(maxHeap, maxSize, 0);
            }
            std::cout << maxHeap[0].value << '\n';
            alive[maxHeap[0].id] = false;
            maxHeap[0] = maxHeap[maxSize - 1];
            maxSize--;
            maxSiftDown(maxHeap, maxSize, 0);
        }
        // std::cout << x.value << ' ' << x.id << '\n';
    }
}