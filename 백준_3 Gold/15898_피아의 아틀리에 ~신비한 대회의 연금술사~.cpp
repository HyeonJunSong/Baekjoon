#include <iostream>
#include <vector>

using namespace std;

int clockwiseRotate[4][4][2] = {
    {{ 0,  3}, { 1,  2}, { 2,  1}, { 3,  0},},
    {{-1,  2}, { 0,  1}, { 1,  0}, { 2, -1},},
    {{-2,  1}, {-1,  0}, { 0, -1}, { 1, -2},},
    {{-3,  0}, {-2, -1}, {-1, -2}, { 0, -3},}
};

int n;

//재료 개수 X 회전된 4개 상태 X 열 개수 X 행 개수
vector<vector<vector<vector<pair<int, char>>>>> ingredients;
vector<bool> visited;

int maxQuality = 0;

void getMaxQuality(vector<vector<pair<int, char>>> kiln, int AddedIngredientNum);
vector<vector<pair<int, char>>> addIngredientToKiln(vector<vector<pair<int, char>>> kiln, int ind, pair<int, int> location, int rotate);
int calculateQuality(vector<vector<pair<int, char>>>& kiln);

int main(){
    cin >> n;

    ingredients = vector<vector<vector<vector<pair<int, char>>>>>(n, vector<vector<vector<pair<int, char>>>>(4, vector<vector<pair<int, char>>>(4, vector<pair<int, char>>(4))));
    
    vector<vector<pair<int, char>>> kiln;
    kiln = vector<vector<pair<int, char>>>(5, vector<pair<int, char>>(5, pair<int, char>(0, 'W')));
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < 4; j++)
            for(int k = 0; k < 4; k++)
                cin >> ingredients[i][0][j][k].first;
        for(int j = 0; j < 4; j++)
            for(int k = 0; k < 4; k++)
                cin >> ingredients[i][0][j][k].second;
        
        for(int r = 1; r < 4; r++){
            for(int j = 0; j < 4; j++)
                for(int k = 0; k < 4; k++)
                    ingredients[i][r][clockwiseRotate[j][k][0] + j][clockwiseRotate[j][k][1] + k] = ingredients[i][r - 1][j][k];
        }

    }

    visited = vector<bool>(n, false);

    getMaxQuality(kiln, 0);
    cout << maxQuality;

    return 0;
}

void getMaxQuality(vector<vector<pair<int, char>>> kiln, int AddedIngredientNum){

    if(AddedIngredientNum == 3){
        int curQuality = calculateQuality(kiln);
        if(curQuality > maxQuality)
            maxQuality = curQuality;
        return;
    }

    for(int i = 0; i < n; i++){
        if(visited[i])
            continue;
        visited[i] = true;
        for(int locI = 0; locI < 2; locI++) 
            for(int locJ = 0; locJ < 2; locJ++)
                for(int rotate = 0; rotate < 4; rotate++)
                    getMaxQuality(addIngredientToKiln(kiln, i, pair<int, int>(locI, locJ), rotate), AddedIngredientNum + 1);
        visited[i] = false;
    }
}

vector<vector<pair<int, char>>> addIngredientToKiln(vector<vector<pair<int, char>>> kiln, int ind, pair<int, int> location, int rotate){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            kiln[location.first + i][location.second + j].first += ingredients[ind][rotate][i][j].first;
            if(kiln[location.first + i][location.second + j].first < 0)
                kiln[location.first + i][location.second + j].first = 0;
            else if(kiln[location.first + i][location.second + j].first > 9)
                kiln[location.first + i][location.second + j].first = 9;

            if(ingredients[ind][rotate][i][j].second != 'W')
                kiln[location.first + i][location.second + j].second = ingredients[ind][rotate][i][j].second;
        }
    }

    return kiln;
}

int calculateQuality(vector<vector<pair<int, char>>>& kiln){
    int totQuality = 0;

    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            switch (kiln[i][j].second){
                case 'R':
                    totQuality += kiln[i][j].first * 7;
                break;
                case 'B':
                    totQuality += kiln[i][j].first * 5;
                break;
                case 'G':
                    totQuality += kiln[i][j].first * 3;
                break;
                case 'Y':
                    totQuality += kiln[i][j].first * 2;
                break;
            }
        }
    }

    return totQuality;
}