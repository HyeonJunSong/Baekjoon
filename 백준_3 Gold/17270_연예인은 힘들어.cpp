////230323
//이해 및 설계 : 6m 38s
//입력 : 4m 43s
//구현 : 39m 06s

//tot : 50m 37s

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class dijNode{
public:
    int cur;
    int weight;

    dijNode(int cur, int weight){
        this->cur = cur;
        this->weight = weight;
    }

    bool operator< (dijNode b) const {
        return weight > b.weight;
    }
};

int main(){

    int V, M;
    cin >> V >> M;

    vector<vector<pair<int, int>>> graph(V + 1);
    int a, b, c;
    for(int i = 0; i < M; i++){
        cin >> a >> b >> c;
        graph[a].push_back(pair<int, int>(b, c));
        graph[b].push_back(pair<int, int>(a, c));
    }
    int J, S;
    cin >> J >> S;

    vector<int> shortestFromJ(V + 1, -1);
    vector<int> shortestFromS(V + 1, -1);
    priority_queue<dijNode> PQ;
    //지헌 다익스트라
    shortestFromJ[0] = 0;
    PQ.push(dijNode(J, 0));
    
    while(!PQ.empty()){
        dijNode curNode = PQ.top();
        PQ.pop();

        if(shortestFromJ[curNode.cur] != -1) continue;
        shortestFromJ[curNode.cur] = curNode.weight;

        for(auto iter = graph[curNode.cur].begin(); iter != graph[curNode.cur].end(); iter++){
            if(shortestFromJ[iter->first] == -1)
                PQ.push(dijNode(iter->first, curNode.weight + iter->second));
        }
    }    

    //성하 다익스트라
    shortestFromS[0] = 0;
    PQ.push(dijNode(S, 0));
    
    while(!PQ.empty()){
        dijNode curNode = PQ.top();
        PQ.pop();

        if(shortestFromS[curNode.cur] != -1) continue;
        shortestFromS[curNode.cur] = curNode.weight;

        for(auto iter = graph[curNode.cur].begin(); iter != graph[curNode.cur].end(); iter++){
            if(shortestFromS[iter->first] == -1)
                PQ.push(dijNode(iter->first, curNode.weight + iter->second));
        }
    }    

    //둘의 합 구하고, 합의 최솟값 찾기
    int minSumInd = 0;
    int minSum = 987654321;

    for(int i = 1; i <= V; i++){
        if(i == J || i == S) continue;

        if(shortestFromJ[i] + shortestFromS[i] < minSum){
            minSum = shortestFromJ[i] + shortestFromS[i];
            minSumInd = i;
        }
        else if(shortestFromJ[i] + shortestFromS[i] == minSum){
            if(shortestFromJ[minSumInd] > shortestFromJ[i]){
                minSumInd = i;
            }
        }
    }

    if(minSumInd == 0 || shortestFromJ[minSumInd] > shortestFromS[minSumInd])
        cout << -1;
    else
        cout << minSumInd;

    return 0;
}