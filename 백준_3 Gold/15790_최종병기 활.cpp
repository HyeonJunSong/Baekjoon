#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N, M, K;
    cin >> N >> M >> K;
    
    vector<int> lengthOf;
    for(int point, i = 0; i < M; i++){
        cin >> point;
        lengthOf.push_back(point);
    }

    for(int i = M - 1; i > 0; i--) lengthOf[i] -= lengthOf[i - 1];
    lengthOf[0] = N;
    for(int i = 1; i < M; i++) lengthOf[0] -= lengthOf[i];
    
    int st = 1;
    int ed = N;

    while(st <= ed){
        int mid = (st + ed) >> 1;

        bool ifPossible = false;

        for(int i = 0; i < M; i++){
            int curLength = 0;
            int kCnt = K;
            for(int j = 0; j < M; j++){
                if(kCnt > 0 && curLength >= mid){
                    curLength = lengthOf[(i + j) % M];
                    kCnt--;
                } else {
                    curLength += lengthOf[(i + j) % M];
                }
            }
            if(kCnt == 0 || ( kCnt == 1 && curLength >= mid )){
                ifPossible = true;
            }
        }

        if(ifPossible) st = mid + 1;
        else ed = mid - 1;
    }

    cout << ed;

    return 0;
}