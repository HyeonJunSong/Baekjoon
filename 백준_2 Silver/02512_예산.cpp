#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int M, N;
vector<int> budgets;    //예산을 저장하는 배열
vector<int> budgetSum;  //예산누적 값을 저장하는 배열

bool ifCanBeCeiling(int n);

int main(){
    cin >> N;
    budgets = vector<int>(N);
    budgetSum = vector<int>(N);
    for(int i = 0; i < N; i++)
        cin >> budgets[i];
    sort(budgets.begin(), budgets.end());
    budgetSum[0] = budgets[0];
    for(int i = 1; i < N; i++)
        budgetSum[i] = budgetSum[i-1] + budgets[i];
    cin >> M;


    if(budgetSum[N - 1] <= M){
        cout << budgets[N - 1];
        return 0;
    }

    int st = 1, md, ed = budgets[N - 1];
    while(st <= ed){
        md = (ed + st) / 2;
        if(ifCanBeCeiling(md)){
            st = md + 1;
        }
        else{
            ed = md - 1;
        }
    }

    if(ifCanBeCeiling(st))
        cout << st;
    else if(ifCanBeCeiling(ed))
        cout << ed;
    else
        cout << ed - 1;

    return 0;
}

bool ifCanBeCeiling(int n){
    //n보다 크지 않은 최대 인덱스 찾기
    int st = 0, md, ed = N - 1;
    while(st <= ed){
        md = (st + ed) / 2;
        if(n < budgets[md]){
            ed = md - 1;
        }
        else if(n > budgets[md]){
            st = md + 1;
        }
        else{
            ed = md;
            break;
        }
    }

    int ind;
    if(n > budgets[st])
        ind = st;
    else if(st == 0)
        ind = -1;
    else if(n > budgets[ed])
        ind = ed;
    else
        ind = ed - 1;

    //해당 인덱스가 상한선이 돼도 되는지 리턴
    if(ind == -1){
        return n * N <= M;
    }
    else{
        return budgetSum[ind] + (N - 1 - ind) * n <= M;
    }
}