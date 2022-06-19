#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    int I;
    cin >> I;

    vector<int> items(n, 0);
    for (int i = 0; i < n; i++)
        cin >> items[i];
    sort(items.begin(), items.end());

    int answer = 0;
    while (items.size() != 0) {

        int st = 0;
        int ed = items.size() - 2;
        int target = I - items.back();
        int mid = (st + ed) / 2;

        while (st < ed) {
            if (items[mid] > target)
                ed = mid - 1;
            else if (items[mid] < target)
                st = mid + 1;
            else
                break;
            mid = (st + ed) / 2;
        }

        if (items.size() != 1) {
            if (target < items[mid] && mid != 0)
                items.erase(items.begin() + mid - 1);
            else if (target >= items[mid])
                items.erase(items.begin() + mid);
        }
        items.pop_back();
        answer++;
    }
    cout << answer;

    return 0;
}