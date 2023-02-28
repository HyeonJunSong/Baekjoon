#include <iostream>
#include <vector>
#include <map>

using namespace std;

vector<map<int, int>> graph;
int N, M, W;

bool isNegativeCyclePossible(vector<int> wormWholeStart);
bool findCycleDFS(int curNode, int weightByCur);

#define INF 987654321

int main(){
    int TC;
    cin >> TC;

    int S, E, T;

    for(int tc = 0; tc < TC; tc++){
        cin >> N >> M >> W;
        graph = vector<map<int, int>>(N + 1, map<int, int>());


        for(int i = 0; i < M; i++){
            cin >> S >> E >> T;
            if(graph[S].find(E) == graph[S].end()) graph[S][E] = T;
            else if(graph[S][E] > T) graph[S][E] = T;

            if(graph[E].find(S) == graph[E].end()) graph[E][S] = T;
            else if(graph[E][S] > T) graph[E][S] = T;
        }

        vector<int> wormHoleStart;
        for(int i = 0; i < W; i++){
            cin >> S >> E >> T;
            if(graph[S].find(E) == graph[S].end()){
                graph[S][E] = -1 * T;
                wormHoleStart.push_back(S);
            }
            else if(graph[S][E] > -1 * T){
                if(graph[S][E] > 0) wormHoleStart.push_back(S);
                graph[S][E] = -1 * T;
            }
        }

        if(isNegativeCyclePossible(wormHoleStart))
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }

    return 0;
}

int st;
vector<int> cache;

bool isNegativeCyclePossible(vector<int> wormHoleStart){
    for(auto i = 0; i < wormHoleStart.size(); i++){
        st = wormHoleStart[i];
        cache = vector<int>(N + 1, INF);
        if(findCycleDFS(wormHoleStart[i], 0))
            return true;
    }
    return false;
}

bool findCycleDFS(int curNode, int weightByCur){

    if(curNode == st){
        if(weightByCur < 0)
            return true;
        return false;
    }

    for(auto iter = graph[curNode].begin(); iter != graph[curNode].end(); iter++){
        if(cache[iter->first] > weightByCur + iter->second){
            cache[iter->first] = weightByCur + iter->second;
            if(findCycleDFS(iter->first, weightByCur + iter->second))
                return true;
        }
    }

    return false;
}