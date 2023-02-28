#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main(){
    int N;
    cin >> N;
    vector<int> budgets(N);
    for(int i = 0; i < N; i++)
        cin >> budgets[i];
    sort(budgets.begin(), budgets.end());
    int M;
    cin >> M;

    //총 예산 구하기
    int totBudget = 0;
    for(int i = 0; i < N; i++)
        totBudget += budgets[i];
    
    if(totBudget <= M){
        cout << budgets.back();
        return 0;
    }

    //맨 뒤에서부터 상한선 정하면서 적정 상한선 구하기
    int curOver = totBudget - M;
    int accrue = 0;
    for(int i = (int)(budgets.size()) - 2; i >= 0; i--){
        accrue += budgets[i + 1] - budgets[i];
        if(curOver - accrue <= 0){
            cout << (int)((double)budgets[i + 1] - ((double)(curOver) / ((budgets.size()) - i - 1)));
            break;
        }
        curOver -= accrue;
    }

    return 0;
}