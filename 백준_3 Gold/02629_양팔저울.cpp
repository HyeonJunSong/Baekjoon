////230324
//이해 및 설계 : 13m 40s
//입력 : 7m 12s
//구현 : 10m 50s

//tot : 31m 42s

#include <iostream>
#include <set>
#include <vector>

using namespace std;

int main(){

    int w;
    cin >> w;
    vector<int> weights(w);
    for(int i = 0; i < w; i++)
        cin >> weights[i];
    
    int m;
    cin >> m;
    vector<int> marvels(m);
    for(int i = 0; i < m; i++)
        cin >> marvels[i];
    
    set<int> possible;
    possible.insert(0);

    for(int i = 0; i < w; i++){
        set<int> newPossible = possible;
        for(auto iter = possible.begin(); iter != possible.end(); iter++){
            newPossible.insert(*iter + weights[i]);
            newPossible.insert(*iter - weights[i]);
        }
        possible = newPossible;
    }

    for(int i = 0; i < m; i++){
        if(possible.find(marvels[i]) == possible.end())
            cout << "N" << ' ';
        else
            cout << "Y" << ' ';
    }

    return 0;
}

