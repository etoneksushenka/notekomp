#include <iostream>

const int constmax = 101;
int rating[constmax];

int main() {
    int n;
    std::cin >> n;
    int value;
    // int kvo = 0;
    // int ar[n];
    // int ind = 0;
    for (int i = 0; i < n; ++i) {
        // std::cin >> ar[i];
        int kvo = 0;
        std::cin >> value;

        for (int j = 1; j <= value; ++j) {
            kvo += rating[j];
        }
        std::cout << kvo << ' ';

        rating[value]++;
    }
}