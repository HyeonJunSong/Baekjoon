#include <iostream>
#include <vector>

using namespace std;

int TC, N, T;
vector<int> A, B, C, D, E;

int arriveTime(int st);

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> TC;
    for (int tc = 0; tc < TC; tc++) {

        cin >> N >> T;
        A = vector<int>(N);
        B = vector<int>(N);
        C = vector<int>(N);
        D = vector<int>(N);
        for (int i = 0; i < N; i++)
            cin >> A[i] >> B[i] >> C[i] >> D[i];


        E = vector<int>(N + 1);
        for (int i = 0; i < N + 1; i++)
            cin >> E[i];

        int st = 0, mid, ed = T, curArriveTime;

        while (st <= ed) {
            mid = (st + ed) / 2;

            curArriveTime = arriveTime(mid);
            if (curArriveTime == T) {
                break;
            }
            else if (curArriveTime < T) {
                st = mid + 1;
            }
            else {
                ed = mid - 1;
            }
        }


        if (curArriveTime == T)
            cout << "YES" << "\n";
        else
            cout << "NO" << "\n";

    }

    return 0;
}

int arriveTime(int st) {

    for (int i = 0; i < N; i++) {
        st += E[i];

        if (st >= C[i]) {
            if (0 <= (st - C[i]) % A[i] && (st - C[i]) % A[i] + D[i] <= B[i]) {
                st += D[i];
            }
            else {
                st += A[i] - (st - C[i]) % A[i] + D[i];
            }
        }
        else {
            st = C[i] + D[i];
        }

        if(st > T) return st;
    }

    return st + E[N];
}