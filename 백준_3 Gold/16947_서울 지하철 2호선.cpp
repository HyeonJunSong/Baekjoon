#include <iostream>
#include <vector>
#include <stack>
#include <set>

using namespace std;

int main(){

    int N;
    cin >> N;

    vector<vector<int>> graph(N, vector<int>());
    for(int i = 0; i < N; i++){
        int st, ed;
        cin >> st >> ed;
        st--, ed--;

        graph[st].push_back(ed);
        graph[ed].push_back(st);
    }

    //순환 set 찾기
    stack<int> S;
    vector<void> check(N, false);

    S.push(0);

    while(!S.empty()){
        int cur = S.top();
        S.pop();
        check[cur] = true;

        for(auto iter = graph[cur].begin(); iter != graph[cur].end(); iter++){
            S.push(*iter);
        }
    }

    //DFS로 답찾기

    return 0;
}