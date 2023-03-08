#include <iostream>
#include <set>
#include <string>

using namespace std;

int main(){
    int N, M;
    cin >> N >> M;
    set<string> noListen;
    for(int i = 0; i < N; i++){
        string inp;
        cin >> inp;
        noListen.insert(inp);
    }
    set<string> noListenAndSee;
    for(int i = 0; i < M; i++){
        string inp;
        cin >> inp;
        if(noListen.find(inp) != noListen.end())
            noListenAndSee.insert(inp);
    }

    cout << noListenAndSee.size() << endl;
    for(auto iter = noListenAndSee.begin(); iter != noListenAndSee.end(); iter++)
        cout << *iter << endl;

    return 0;
}