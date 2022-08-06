////22.08.06
//47m 7s

#include <iostream>
#include <set>
#include <vector>

using namespace std;

int main() {
    int N, M;
    cin >> N >> M;
    int nTruth;
    cin >> nTruth;
    vector<int> truth(nTruth);
    for (int i = 0; i < nTruth; i++) cin >> truth[i];

    vector<vector<int>> parties;
    for (int i = 0; i < M; i++) {
        int nParty;
        cin >> nParty;
        vector<int> party(nParty);
        for (int j = 0; j < nParty; j++) cin >> party[j];
        parties.push_back(party);
    }
    
    set<int> truthSet;
    for (int i = 0; i < nTruth; i++) truthSet.insert(truth[i]);

    vector<bool> ifAdded(M, false);

    while (true) {
        bool ifChanged = false;

        for (int i = 0; i < M; i++) {
            if (ifAdded[i]) continue;
            for (int j = 0; j < parties[i].size(); j++) {
                if (truthSet.find(parties[i][j]) != truthSet.end()) {
                    ifChanged = true;
                    for (int k = 0; k < parties[i].size(); k++)
                        truthSet.insert(parties[i][k]);
                    ifAdded[i] = true;
                    break;
                }
            }
        }

        if (!ifChanged) break;
    }

    int ans = 0;
    for (int i = 0; i < M; i++) {
        bool ifTruthSet = false;
        for (int j = 0; j < parties[i].size(); j++) {
            if (truthSet.find(parties[i][j]) != truthSet.end()) {
                ifTruthSet = true;
                break;
            }
        }
        if (!ifTruthSet) ans++;
    }
    cout << ans;

    return 0;
}