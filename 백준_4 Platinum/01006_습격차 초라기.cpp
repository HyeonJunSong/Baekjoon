#include <iostream>
#include <vector>

using namespace std;

#define MAX 987654321

void runCase();
int getSmallestUnitNum(int, int, int);

int main(){
    int T;
    cin >> T;

    for(int t = 0; t < T; t++)
        runCase();
    
    return 0;
}

int N, W;
vector<pair<int, int>> enemies;
vector<vector<vector<int>>> cache;

void runCase(){
    cin >> N >> W;

    enemies = vector<pair<int, int>>(N, pair<int, int>());
    cache = vector<vector<vector<int>>>(4, vector<vector<int>>(N, vector<int>(4, -1)));

    int ans;

    for(int i = 0; i < N; i++)
        cin >> enemies[i].first;
    for(int i = 0; i < N; i++)
        cin >> enemies[i].second;
    
    if(N == 1){
        if(enemies[0].first + enemies[0].second <= W)
            ans = 1;
        else
            ans = 2;
    }
    else{

        //마지막 두놈 이어질 수 있는지
        bool ifLastTwoConnectable = enemies.back().first + enemies.back().second <= W;

        //둘 다 안잇기
        if(cache[0][0][0] == -1)
            cache[0][0][0] = getSmallestUnitNum(0, 0, 0);

        ans = cache[0][0][0];

        //위에거만 잇기
        if(enemies[0].first + enemies.back().first <= W){
            if(cache[1][0][1] == -1)
                cache[1][0][1] = getSmallestUnitNum(1, 0, 1);
            if(ans > cache[1][0][1])
                ans = cache[1][0][1];
        }

        //밑에거만 잇기
        if(enemies[0].second + enemies.back().second <= W){
            if(cache[2][0][2] == -1)
                cache[2][0][2] = getSmallestUnitNum(2, 0, 2);
            if(ans > cache[2][0][2])
                ans = cache[2][0][2];
        }

        //둘 다 잇기
        if(enemies[0].first + enemies.back().first <= W
        && enemies[0].second + enemies.back().second <= W){
            if(cache[3][0][3] == -1)
                cache[3][0][3] = getSmallestUnitNum(3, 0, 3);
            if(ans > cache[3][0][3])
                ans = cache[3][0][3];
        }
    }

    cout << ans << '\n';
}

//case:
//0 -> 위에거 밑에거 둘다 가능
//1 -> 밑에거만 가능
//2 -> 위에거만 가능
//3 -> 둘다 불가능
int getSmallestUnitNum(int firstCase, int i, int curCase){

    //기저
    if(i == N - 1){
        switch(curCase){
        case 0:
            switch (firstCase){
            case 0:
                if(enemies[i].first + enemies[i].second <= W)
                    return 1;
                else
                    return 2;

            case 1:
            case 2:
            case 3:
                return 2;
            }
        
        case 1:
            switch (firstCase){
            case 0:
            case 2:
                return 1;
            case 1:
            case 3:
                return MAX;
            }

        case 2:
            switch (firstCase){
            case 0:
            case 1:
                return 1;
            case 2:
            case 3:
                return MAX;
            }

        case 3:
            switch (firstCase){
            case 0:
                return 0;
            case 1:
            case 2:
            case 3:
                return MAX;
            }
        }
    }
    
    int ans;
    switch(curCase){
        case 0:

            ////둘 다 안 잇기
            //아래 위 이을 수 있으면 잇기
            if(cache[firstCase][i + 1][0] == -1)
                cache[firstCase][i + 1][0] = getSmallestUnitNum(firstCase, i + 1, 0);

            if(enemies[i].first + enemies[i].second <= W)
                ans = cache[firstCase][i + 1][0] + 1;
            else
                ans = cache[firstCase][i + 1][0] + 2;

            ////위에거만 옆에 구역과 이어서 배치
            if(enemies[i].first + enemies[i + 1].first <= W){
                if(cache[firstCase][i + 1][1] == -1)
                    cache[firstCase][i + 1][1] = getSmallestUnitNum(firstCase, i + 1, 1);
                if(ans > cache[firstCase][i + 1][1] + 2)
                    ans = cache[firstCase][i + 1][1] + 2;
            }
            
            ////밑에거만 옆에 구역과 이어서 배치
            if(enemies[i].second + enemies[i + 1].second <= W){
                if(cache[firstCase][i + 1][2] == -1)
                    cache[firstCase][i + 1][2] = getSmallestUnitNum(firstCase, i + 1, 2);
                if(ans > cache[firstCase][i + 1][2] + 2)
                    ans = cache[firstCase][i + 1][2] + 2;
            }

            ////둘 다 잇기
            if(enemies[i].first + enemies[i + 1].first <= W
            && enemies[i].second + enemies[i + 1].second <= W){
                if(cache[firstCase][i + 1][3] == -1)
                    cache[firstCase][i + 1][3] = getSmallestUnitNum(firstCase, i + 1, 3);
                if(ans > cache[firstCase][i + 1][3] + 2)
                    ans = cache[firstCase][i + 1][3] + 2;
            }
            
            break;

        case 1:
            ////밑에 구역 혼자 배치
            if(cache[firstCase][i + 1][0] == -1)
                cache[firstCase][i + 1][0] = getSmallestUnitNum(firstCase, i + 1, 0);
            ans = cache[firstCase][i + 1][0] + 1;

            ////밑에 구역 우측이랑 이어서 배치
            if(enemies[i].second + enemies[i + 1].second <= W){
                if(cache[firstCase][i + 1][2] == -1)
                    cache[firstCase][i + 1][2] = getSmallestUnitNum(firstCase, i + 1, 2);
                if(ans > cache[firstCase][i + 1][2] + 1)
                    ans = cache[firstCase][i + 1][2] + 1;
            }

            break;
        
        case 2:
            ////위에 구역 혼자 배치
            if(cache[firstCase][i + 1][0] == -1)
                cache[firstCase][i + 1][0] = getSmallestUnitNum(firstCase, i + 1, 0);
            ans = cache[firstCase][i + 1][0] + 1;

            ////위에 구역 우측이랑 이어서 배치
            if(enemies[i].first + enemies[i + 1].first <= W){
                if(cache[firstCase][i + 1][1] == -1)
                    cache[firstCase][i + 1][1] = getSmallestUnitNum(firstCase, i + 1, 1);
                if(ans > cache[firstCase][i + 1][1] + 1)
                    ans = cache[firstCase][i + 1][1] + 1;
            }

            break;

        case 3:
            if(cache[firstCase][i + 1][0] == -1)
                cache[firstCase][i + 1][0] = getSmallestUnitNum(firstCase, i + 1, 0);
            ans = cache[firstCase][i + 1][0];
    }

    return ans;
}