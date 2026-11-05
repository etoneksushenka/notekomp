#include <iostream>

constexpr int MAXN = 8e4;
constexpr int MAXB = 3e4;
constexpr int L = 10 * 60;

struct Node {
    int id;
    int time;
};

void minSiftDown(Node* ar, int n, int index, int* pos) {
    bool is_parent_greater = false;
    while (index * 2 + 1 < n && is_parent_greater == false) {
        int left = index * 2 + 1;
        int max_child = left;
        if (index * 2 + 2 < n && (ar[index * 2 + 2].time < ar[left].time 
        || (ar[index * 2 + 2].time == ar[left].time && ar[index * 2 + 2].id < ar[left].id))) {
            max_child = index * 2 + 2;
        } 
        if (ar[index].time > ar[max_child].time) {
            std::swap(ar[index], ar[max_child]);
            pos[ar[index].id] = index;
            pos[ar[max_child].id] = max_child;
            index = max_child;
        }
        else if (ar[index].time == ar[max_child].time && ar[index].id > ar[max_child].id) {
            std::swap(ar[index], ar[max_child]);
            pos[ar[index].id] = index;
            pos[ar[max_child].id] = max_child;
            index = max_child;
        }
        else {
            is_parent_greater = true;
        }
    }
}

void minSiftUp(Node* ar, int index, int* pos) {
    bool is_child_lower = false;
    while (index > 0 && is_child_lower == false) {
        int parent = (index - 1) / 2;
        if (ar[index].time < ar[parent].time) {
            std::swap(ar[index], ar[parent]);
            pos[ar[index].id] = index;
            index = parent;
        }
        else if (ar[index].time == ar[parent].time && ar[index].id < ar[parent].id) {
            std::swap(ar[index], ar[parent]);
            pos[ar[index].id] = index;
            index = parent;
        }
        else {
            is_child_lower = true;
        }
    }
}

void minSiftDownInt(int* ar, int n, int index) {
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

void minSiftUpInt(int* ar, int index) {
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

int len(char* str) {
    int k = 0;
    int i = 0;
    while (str[i] != '\0') {
        k++;
        i++;
    }
    return k;
}

int main() {
    Node ar[MAXN];
    int pos[MAXB] = {};
    int freeheap[MAXB];
    for (int i = 0; i < MAXB; ++i) {
        freeheap[i] = i;
        pos[i] = -1;
    }
    int freesize = MAXB;
    char command[50];
    // int i = 0;
    int heapsize = 0;
    while (std::cin.getline(command, sizeof(command))) {
        int j = 0, time = 0;
        while (command[j] != ' ') {
            time = time * 10 + (command[j] - '0');
            j++;
        }
        while (heapsize > 0 && ar[0].time <= time) {
            Node temp = ar[0];
            pos[temp.id] = -1;
            ar[0] = ar[heapsize - 1];
            heapsize--;
            if (heapsize > 0) {
                minSiftDown(ar, heapsize, 0, pos);
            }
            freeheap[freesize] = temp.id;
            freesize++;
            minSiftUpInt(freeheap, freesize - 1);
        }
        if (command[len(command) - 1] == '+') {
            int id = freeheap[0];
            freeheap[0] = freeheap[freesize - 1];
            freesize--;
            if (freesize > 0) {
                minSiftDownInt(freeheap, freesize, 0);
            }
            ar[heapsize].id = id;
            ar[heapsize].time = time + L;
            pos[id] = heapsize;
            heapsize++;
            minSiftUp(ar, heapsize - 1, pos);
            std::cout << id + 1 << '\n';
        }
        else {
            int nom = 0;
            j += 3;
            while (command[j] != '\0') {
                nom = nom * 10 + (command[j] - '0');
                j++;
            }
            nom--;
            if (pos[nom] == -1) {
                std::cout << '-' << '\n';
            }
            else {
                std::cout << '+' << '\n';
                ar[pos[nom]].time = time + L;
                minSiftDown(ar, heapsize, pos[nom], pos);
            }
        }
    } 

}