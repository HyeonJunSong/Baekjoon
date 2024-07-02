#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int statinons[1000001][2];

    int N, M;
    cin >> N >> M;

    vector<int> curStations(N);
    for(int i = 0; i < N; i++)
        cin >> curStations[i];

    for(int i = 0; i < N; i++){
        statinons[curStations[i]][0] = curStations[(i - 1 + N) % N];
        statinons[curStations[i]][1] = curStations[(i + 1) % N];
    }

    string query;
    int i, j;

    for(int q = 0; q < M; q++){

        cin >> query;

        if(query[0] == 'B'){
            if(query[1] == 'N'){
                cin >> i >> j;
                cout << statinons[i][1] << "\n";
                statinons[j][0] = i;
                statinons[j][1] = statinons[i][1];
                statinons[i][1] = j;
                statinons[statinons[j][1]][0] = j;
            } else{
                cin >> i >> j;
                cout << statinons[i][0] << "\n";
                statinons[j][1] = i;
                statinons[j][0] = statinons[i][0];
                statinons[i][0] = j;
                statinons[statinons[j][0]][1] = j;
            }
        } else {
            if(query[1] == 'N'){
                cin >> i;
                cout << statinons[i][1] << "\n";
                statinons[i][1] = statinons[statinons[i][1]][1];
                statinons[statinons[i][1]][0] = i;
            } else {
                cin >> i;
                cout << statinons[i][0] << "\n";
                statinons[i][0] = statinons[statinons[i][0]][0];
                statinons[statinons[i][0]][1] = i;
            }
        }
    }

    return 0;
}