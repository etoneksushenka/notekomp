#include <iostream>

int MAXN = 1e5;

int main() {

    int ar[MAXN + 1];
    int n;
    std::cin >> n;
    for (int i = 1; i < n; ++i) {
        std::cin >> ar[i];
    }
    
    for (int i = 1; i < n / 2; ++i) {
        if (ar[i] > ar[2 * i] || ar[i] > ar[2 * i + 1]) {
            std::cout << "NO\n";
            return 0;
        }
    }
    std::cout << "YES\n";
    
    return 0;
}