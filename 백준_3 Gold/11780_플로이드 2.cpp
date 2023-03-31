#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define INF 10000000001

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n;
    cin >> m;

    int st, ed, w;
    vector<vector<pair<long long, string>>> map(n + 1, vector<pair<long long, string>>(n + 1, pair<long long, string>(INF, "")));
    for(int i = 0; i < m; i++){
        cin >> st >> ed >> w;
        if(map[st][ed].first > w)
            map[st][ed].first = w;
    }

    //플로이드
    for(int k = 1; k <= n; k++){
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                if(i == j) continue;
                if(map[i][j].first > map[i][k].first + map[k][j].first){
                    map[i][j].first = map[i][k].first + map[k][j].first;
                    map[i][j].second = map[i][k].second + ' ' + to_string(k) + ' ' + map[k][j].second;
                }
            }
        }
    }

    //출력
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            if(map[i][j].first == INF){
                cout << '0';
            }
            else{
                cout << map[i][j].first;
            }
            cout << ' ';
        }
        cout << '\n';
    }

    //하나씩 출력
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            if(map[i][j].first == INF){
                cout << '0';
            }
            else{
                vector<int> ans;
                ans.push_back(i);

                if(map[i][j].second.length() != 0){
                    string num = "";
                    for(int l = 1; l < map[i][j].second.length() - 1; l++){
                        if(map[i][j].second[l] == ' ') continue;
                        num += map[i][j].second[l];
                        if(map[i][j].second[l + 1] == ' '){
                            ans.push_back(stoi(num));
                            num = "";
                        }
                    }
                }

                ans.push_back(j);

                cout << ans.size();
                for(auto iter = ans.begin(); iter != ans.end(); iter++)
                    cout << ' ' << *iter;
            }
            cout << '\n';
        }
    }

    return 0;
}