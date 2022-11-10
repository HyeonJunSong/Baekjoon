////20221110
//tot : 16m 18s

#include <iostream>
#include <queue>
#include <functional>

using namespace std;

int main(){

    int N;
    cin >> N;
    priority_queue<int, vector<int>, greater<int>> pq;

    for(int i = 0; i < N; i++){
        int pile;
        cin >> pile;
        pq.push(pile);
    }

    if(N == 1){
        cout << 0;
        return 0;
    }

    int tot = 0;
    while(pq.size() > 0){
        int n1 = pq.top();
        pq.pop();
        int n2 = pq.top();
        pq.pop();

        tot += n1 + n2;
        if(pq.size() == 0) break;

        pq.push(n1 + n2);
    }
    cout << tot;

    return 0;
}