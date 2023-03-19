#include <iostream>
#include <set>

using namespace std;

int main(){
    int N;
    cin >> N;
    int M;
    cin >> M;

    int inp;

    set<int> s;

    int cnt = 0;
    for(int i = 0; i < N; i++){
        cin >> inp;
        if(s.find(M - inp) != s.end())
            cnt++;
        else
            s.insert(inp);
    }

    cout << cnt;
    return 0;
}