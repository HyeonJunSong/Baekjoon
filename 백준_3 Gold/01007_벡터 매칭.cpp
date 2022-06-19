#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<pair<int, int>> points;
vector<bool> remains;

double retSmallestVector(int totX, int totY, int prv, int N, int n);

int main(){
    int T;
    cin >> T;
    for(int t = 0; t < T; t++){
        int N;
        cin >> N;

        points.clear();
        remains.clear();
        cout.precision(7);
        cout << fixed; 
        for(int i = 0; i < N; i++){
            int X, Y;
            cin >> X >> Y;
            points.push_back(make_pair(X, Y));
            remains.push_back(true);
        }

        cout << retSmallestVector(0, 0, -1, N, N / 2) << endl;
    }

    cout.unsetf(ios::fixed);
    return 0;
}

double retSmallestVector(int totX, int totY, int prv, int N, int n){

    if(n == 0){
        for(int i = 0; i < N; i++){
            if(!remains[i]) continue;
            totX -= points[i].first;
            totY -= points[i].second;
        }
        return sqrt((double)(totX)*totX + (double)(totY)*totY);
    }

    double tot = 987654321;

    for(int i = prv + 1; i <= N - n; i++){
        remains[i] = false;

        double res = retSmallestVector(totX + points[i].first, totY + points[i].second, i, N, n - 1);
        if(tot > res)
            tot = res;

        remains[i] = true;
    }

    return tot;
}