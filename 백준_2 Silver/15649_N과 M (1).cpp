#include <iostream>
#include <vector>
#include <string>

using namespace std;

int N, M;
void findNumArr(vector<bool>& visited, int M, string result);
int main(){
    cin >> N >> M;
    vector<bool> visited(N + 1, false);
    findNumArr(visited, M, "");

    return 0;
}

void findNumArr(vector<bool>& visited, int M, string result){

    if(M == 0){
        cout << result << '\n';
    }

    for(int i = 1; i <= N; i++){
        if(visited[i]) continue;
        visited[i] = true;
        findNumArr(visited, M - 1, result + to_string(i) + " ");
        visited[i] = false;
    }
}