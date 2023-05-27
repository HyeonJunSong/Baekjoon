#include <iostream>
#include <vector>

using namespace std;

vector<int> lights;

class node {
public:
    int val;
    pair<int, int> leftRange;
    pair<int, int> rightRange;
    node* left;
    node* right;

    node(pair<int, int> range) {
        if (range.first == range.second) {
            leftRange = pair<int, int>(range.first, range.second);
            rightRange = pair<int, int>(range.first, range.second);
            left = nullptr;
            right = nullptr;
            val = lights[range.first];
        }
        else {
            leftRange = pair<int, int>(range.first, (range.first + range.second) / 2);
            rightRange = pair<int, int>((range.first + range.second) / 2 + 1, range.second);

            left = new node(leftRange);
            right = new node(rightRange);

            val = left->val > right->val ? left->val : right->val;
        }
    }

    int getVal(pair<int, int> range) {
        if (range.first == leftRange.first && range.second == rightRange.second)
            return val;

        if (rightRange.first <= range.first)
            return right->getVal(range);
        if (leftRange.second >= range.second)
            return left->getVal(range);

        int leftVal = left->getVal(pair<int, int>(range.first, leftRange.second));
        int rightVal = right->getVal(pair<int, int>(rightRange.first, range.second));
        return leftVal > rightVal ? leftVal : rightVal;
    }
};

int main() {
    int N, M;
    cin >> N >> M;

    lights = vector<int>(N);

    for (int i = 0; i < N; i++)
        cin >> lights[i];

    node root(pair<int, int>(0, N - 1));

    for (int i = M - 1; i < N - M + 1; i++)
        cout << root.getVal(pair<int, int>(i - (M - 1), i + (M - 1))) << ' ';

    return 0;
}