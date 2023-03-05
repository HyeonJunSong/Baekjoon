////23.05.03
//이해 및 설계 : 1m 5s
//입력 : 42s
//구현 : 6m 26s
//tot : 8m 13s

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class node{
public:
    int coor;
    int cnt;

    node(int coor, int cnt){
        this->coor = coor;
        this->cnt = cnt;
    }

    bool operator< (node b) const{
        return cnt > b.cnt;
    }
};

int main(){
    int N, K;
    cin >> N >> K;

    priority_queue<node> PQ;
    PQ.push(node(N, 0));

    vector<bool> visited(100000, false);    

    while(!PQ.empty()){
        node curNode = PQ.top();
        PQ.pop();
        if(curNode.coor == K){
            cout << curNode.cnt;
            break;
        }
        if(visited[curNode.coor]) continue;
        visited[curNode.coor] = true;

        if(curNode.coor + 1 <= 100000) PQ.push(node(curNode.coor + 1, curNode.cnt + 1));
        if(curNode.coor - 1 >= 0) PQ.push(node(curNode.coor - 1, curNode.cnt + 1));
        if(curNode.coor * 2 <= 100000) PQ.push(node(curNode.coor * 2, curNode.cnt + 1));
    }

    return 0;
}