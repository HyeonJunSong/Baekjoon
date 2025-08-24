#include <string>
#include <vector>
#include <iostream>
#include <map>

using namespace std;

// vector<int> gNumOf;

// int getGNum(int i){
//     if(gNumOf[i] != gNumOf[gNumOf[i]]) gNumOf[i] = getGNum(gNumOf[i]);
//     return gNumOf[i];
// }

// void setGNum(int a, int b){
//     int aGNum = getGNum(a);
//     int bGNum = getGNum(b);

//     if(aGNum < bGNum) gNumOf[bGNum] = aGNum;
//     else gNumOf[aGNum] = bGNum;
// }

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;

    vector<vector<int>> familyOf;
    map<string, int> numbOf;

    while(n-- > 0){
        string p1, c, p2;
        cin >> p1 >> c >> p2;
        if(numbOf.find(p1) == numbOf.end()){
            numbOf[p1] = numbOf.size();
            familyOf.push_back({});
        }
        if(numbOf.find(p2) == numbOf.end()){
            numbOf[p2] = numbOf.size();
            familyOf.push_back({});
        }

        familyOf[numbOf[p1]].push_back(numbOf[p2]);
        familyOf[numbOf[p2]].push_back(numbOf[p1]);
    }

    int cnt = 0;
    vector<int> gNumOf(numbOf.size(), -1);
    for(int i = 0; i < gNumOf.size(); i++){
        if(gNumOf[i] != -1) continue;

        vector<int> s(1, i);
        while(s.size() > 0){
            int cur = s.back();
            s.pop_back();
            gNumOf[cur] = cnt;

            for(int j = 0; j < familyOf[cur].size(); j++){
                if(gNumOf[familyOf[cur][j]] != -1) continue;
                s.push_back(familyOf[cur][j]);
            }
        }

        cnt++;
    }

    int m;
    cin >> m;

    while(m-- > 0){
        string p1, p2;
        cin >> p1 >> p2;
        if(gNumOf[numbOf[p1]] == gNumOf[numbOf[p2]])
            cout << "Related\n";
        else
            cout << "Not Related\n";
    }


    return 0;
}