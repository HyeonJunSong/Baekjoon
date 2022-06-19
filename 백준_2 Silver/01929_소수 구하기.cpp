#include <iostream>
#include <set>
#include <cmath>

using namespace std;

int main(){
    int M, N;
    cin >> M >> N;

    set<int> EratosthenesSieve;
    for(int i = 2; i <= N; i++){
        EratosthenesSieve.insert(i);
    }

    for(set<int>::iterator i = EratosthenesSieve.begin(); *i <= (int)(sqrt(N)); i++){
        for(int j = (*i) * 2; j <= N; j += *i){
            set<int>::iterator k = EratosthenesSieve.find(j);
            if(k != EratosthenesSieve.end())
                EratosthenesSieve.erase(k);
        }
    }

    for(set<int>::iterator i = EratosthenesSieve.begin(); i != EratosthenesSieve.end(); i++)
        if(M <= *i) cout << *i << '\n';

    
    return 0;
}