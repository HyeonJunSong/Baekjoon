////230325
//이해 및 설계 : 5m 23s
//입력 : 3m 13s
//구현 : 39m 36s

//tot : 48m 12s

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N, M;
vector<queue<int>> PD;
vector<vector<bool>> ifLeft;

int pickOne();
bool ifMySingerPossible(int singer);
void popSinger(int singer);

int main(){
    cin >> N >> M;

    int mySingerNum;
    int mySinger;

    PD = vector<queue<int>>(M, queue<int>());
    ifLeft = vector<vector<bool>>(M, vector<bool>(N + 1, false));

    for(int i = 0; i < M; i++){
        cin >> mySingerNum;
        for(int j = 0; j < mySingerNum; j++){
            cin >> mySinger;
            PD[i].push(mySinger);
            ifLeft[i][mySinger] = true;
        }
    }

    vector<int> ans;
    bool ifNotPossible = false;
    for(int i = 0; i < N; i++){
        mySinger = pickOne();
        if(mySinger == -1)
            break;
        if(mySinger == 0){
            ifNotPossible = true;
            break;
        }
        popSinger(mySinger);
        ans.push_back(mySinger);
    }

    if(ifNotPossible){
        cout << 0;
    }
    else{
        vector<bool> SingerCheck(N + 1, false);
        for(auto iter = ans.begin(); iter != ans.end(); iter++){
            SingerCheck[*iter] = true;
            cout << *iter << '\n';
        }
        for(int i = 1; i <= N; i++)
            if(!SingerCheck[i])
                cout << i << '\n';
    }
    return 0;
}

int pickOne(){
    bool isPDEmpty = true;
    for(int i = 0; i < M; i++){
        if(!PD[i].empty()){
            isPDEmpty = false;
            if(ifMySingerPossible(PD[i].front())){
                return PD[i].front();
            }
        }
    }
    if(isPDEmpty) return -1;
    return 0;
}

bool ifMySingerPossible(int singer){
    for(int i = 0; i < M; i++)
        if(PD[i].front() != singer && ifLeft[i][singer])
            return false;
    return true;
}

void popSinger(int singer){
    for(int i = 0; i < M; i++){
        if(PD[i].front() == singer){
            PD[i].pop();
            ifLeft[i][singer] = false;
        }
    }
}