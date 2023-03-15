#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

vector<int> cache(13);

void printKantor(int N);
int main() {

    int n;

    for (int i = 0; i <= 12; i++)
        cache[i] = (int)(pow(3, i));

    while (true) {
        cin >> n;
        if (cin.eof() == true) break;
        printKantor(n);
    }
    printKantor(n);

    return 0;
}

void printKantor(int N) {

    for (int i = 0; i < cache[N]; i++) {
        bool ifBlank = false;
        int curN = i;
        for (int j = 11; j >= 0; j--) {
            if (cache[j] <= curN && curN < cache[j] * 2) {
                ifBlank = true;
                break;
            }
            curN %= cache[j];
        }
        if (ifBlank) cout << ' ';
        else cout << '-';
    }
    cout << endl;
}