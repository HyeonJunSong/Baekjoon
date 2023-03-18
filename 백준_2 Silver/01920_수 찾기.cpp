#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N;
vector<int> arr;

bool findNum(int num);

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;

    arr = vector<int>(N);
    for(int i = 0; i < N; i++){
        cin >> arr[i];
    }

    sort(arr.begin(), arr.end());

    int M, inp;
    cin >> M;
    for(int i = 0; i < M; i++){
        cin >> inp;
        if(findNum(inp)) cout << 1 << '\n';
        else cout << 0 << '\n';       
    }

}

bool findNum(int num){

    int st = 0;
    int ed = N - 1;
    int mid;
    while(st <= ed){
        mid = (st + ed) / 2;
        if(arr[mid] == num){
            return true;
        }
        else if(arr[mid] < num){
            st = mid + 1;
        }
        else{
            ed = mid - 1;
        }
    }

    return false;
}