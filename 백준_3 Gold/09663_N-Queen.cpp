#include <iostream>
#include <vector>

using namespace std;

int n;

int numOfCases(int I, vector<int>& col);
bool promising(int i, int I, vector<int>& col);

int main() {
    cin >> n;
    vector<int> col(n, -1);
    cout << numOfCases(0, col);
}

int numOfCases(int I, vector<int>& col) {
    if (I == n) {
        return 1;
    }

    int tot = 0;

    for (int i = 0; i < n; i++) {
        if (promising(i, I, col)) {
            col[i] = I;
            tot += numOfCases(I + 1, col);
            col[i] = -1;
        }
    }

    return tot;
}

bool promising(int i, int I, vector<int>& col) {
    if (col[i] >= 0) return false;

    for (int j = 0; j < n; j++)
        if (col[j] != -1 && abs(i - j) == abs(I - col[j]))
            return false;

    return true;
}