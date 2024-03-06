#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int ccw(pair<int, int> base, pair<int, int> standard, pair<int, int> object) {
    int res = (standard.first - base.first) * (object.second - base.second) - (standard.second - base.second) * (object.first - base.first);

    if (res > 0)
        res = 1;
    else if (res < 0)
        res = -1;

    return res;
}


void testCase() {

    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> black(n);
    vector<pair<int, int>> white(m);
    for (int i = 0; i < n; i++)
        cin >> black[i].first >> black[i].second;
    for (int i = 0; i < m; i++)
        cin >> white[i].first >> white[i].second;
    
    if(n == 1 && m == 1){
        cout << "YES\n";
        return;
    }


    for(int w = 0; w < m; w++){
        for(int b = 0; b < n; b++){

            int whiteCCWSide = -2;   //-2 : 미정, -1, 1 : 해당 방향, 2 : 안됨            
            int whiteSameLineMinX = white[w].first;
            int whiteSameLineMaxX = white[w].first;
            int whiteSameLineMinY = white[w].second;
            int whiteSameLineMaxY = white[w].second;
            for(int w1 = 0; w1 < m; w1++){
                if(w1 == w) continue;

                int curCCW = ccw(white[w], black[b], white[w1]);

                if(curCCW == 0){
                    whiteSameLineMinX = min(whiteSameLineMinX, white[w1].first);
                    whiteSameLineMaxX = max(whiteSameLineMaxX, white[w1].first);
                    whiteSameLineMinY = min(whiteSameLineMinY, white[w1].second);
                    whiteSameLineMaxY = max(whiteSameLineMaxY, white[w1].second);
                } else{
                    if(whiteCCWSide == -2){
                        whiteCCWSide = curCCW;
                    }
                    else{
                        if(whiteCCWSide != curCCW){
                            whiteCCWSide = 2;
                            break;
                        }
                    }
                }
            }
            if(whiteCCWSide == 2) continue;

            int blackCCWSide = -2;   //-2 : 미정, -1, 1 : 해당 방향, 2 : 안됨
            int blackSameLineMinX = black[b].first;
            int blackSameLineMaxX = black[b].first;
            int blackSameLineMinY = black[b].second;
            int blackSameLineMaxY = black[b].second;
            for(int b1 = 0; b1 < n; b1++){
                if(b1 == b) continue;

                int curCCW = ccw(white[w], black[b], black[b1]);

                if(curCCW == 0){
                    blackSameLineMinX = min(blackSameLineMinX, black[b1].first);
                    blackSameLineMaxX = max(blackSameLineMaxX, black[b1].first);
                    blackSameLineMinY = min(blackSameLineMinY, black[b1].second);
                    blackSameLineMaxY = max(blackSameLineMaxY, black[b1].second);
                } else{
                    if(blackCCWSide == -2){
                        blackCCWSide = curCCW;
                    }
                    else{
                        if(blackCCWSide != curCCW){
                            blackCCWSide = 2;
                            break;
                        }
                    }
                }
            }
            if(blackCCWSide == 2) continue;

            if(whiteCCWSide != -2 && whiteCCWSide == blackCCWSide) continue;
            if(whiteSameLineMaxX > blackSameLineMinX && blackSameLineMaxX > whiteSameLineMinX) continue;
            if(whiteSameLineMaxY > blackSameLineMinY && blackSameLineMaxY > whiteSameLineMinY) continue;

            cout << "YES\n";
            return;
        }
    }

    cout << "NO\n";
    return;
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int T;
    cin >> T;
    for (int i = 0; i < T; i++)
        testCase();

    return 0;
}
