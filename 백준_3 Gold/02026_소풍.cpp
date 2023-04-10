////230410
//이해 및 설계 : 14m 41s
//입력 : 2m 43s
//구현 : 29m 10s

//tot : 46m 34s

#include <iostream>
#include <vector>

using namespace std;

vector<vector<bool>> friends;
vector<int> ans;

bool matchFriends(int K, vector<int>& curGroup);

int main(){
    int K, N, F;
    cin >> K >> N >> F;
    friends = vector<vector<bool>>(N + 1, vector<bool>(N + 1, false));
    int f1, f2;
    for(int i = 0; i < F; i++){
        cin >> f1 >> f2;
        friends[f1][f2] = true;
        friends[f2][f1] = true;
    }

    vector<int> initGroup(N);
    for(int i = 0; i < N; i++)
        initGroup[i] = i + 1;

    if(matchFriends(K, initGroup)){
        for(auto iter = ans.rbegin(); iter != ans.rend(); iter++)
            cout << *iter << '\n';
    }
    else
        cout << -1;


    return 0;
}

bool matchFriends(int K, vector<int>& curGroup){

    if(K == 1){
        ans.push_back(curGroup.front());
        return true;
    }

    for(auto iter1 = curGroup.begin(); iter1 != curGroup.end() - 1 ; iter1++){
        vector<int> nextGroup;
        for(auto iter2 = iter1 + 1; iter2 != curGroup.end(); iter2++){
            if(friends[*iter1][*iter2])
                nextGroup.push_back(*iter2);
        }

        if(nextGroup.size() >= K - 1)
            if(matchFriends(K - 1, nextGroup)){
                ans.push_back(*iter1);
                return true;
            }
    }

    return false;
}