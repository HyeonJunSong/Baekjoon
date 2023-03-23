////230323
//이해 및 설계 : 9m 47s
//입력 : 4m 17s
//구현 : 24m 57s

//tot : 39m 1s

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class inNode{
public:
    int counterNum;
    int waitingTime;
    
    inNode(int counterNum, int waitingTime){
        this->counterNum = counterNum;
        this->waitingTime = waitingTime;
    }

    bool operator< (inNode b) const{
        if(waitingTime == b.waitingTime)
            return counterNum > b.counterNum;
        return waitingTime > b.waitingTime;
    }
};

class outNode{
public:
    int counterNum;
    int checkoutTime;
    
    outNode(int counterNum, int checkoutTime){
        this->counterNum = counterNum;
        this->checkoutTime = checkoutTime;
    }

    bool operator< (outNode b) const{
        if(checkoutTime == b.checkoutTime)
            return counterNum < b.counterNum;
        return checkoutTime > b.checkoutTime;
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N, k;
    cin >> N >> k;

    vector<pair<int, int>> carts(N, pair<int, int>(0, 0));
    for(int i = 0; i < N; i++)
        cin >> carts[i].first >> carts[i].second;

    //계산대 큐 생성
    vector<queue<int>> counter(k, queue<int>());

    //계산대 큐에 사람들 집어넣기
    priority_queue<inNode> inPQ;
    for(int i = 0; i < k; i++){
        inPQ.push(inNode(i, 0));
    }
    
    inNode curInNode = inNode(0, 0);
    for(int i = 0; i < N; i++){
        curInNode = inPQ.top();
        inPQ.pop();
        counter[curInNode.counterNum].push(i);
        inPQ.push(inNode(curInNode.counterNum, curInNode.waitingTime + carts[i].second));
    }


    //계산대 큐에서 사람들 빼기
    queue<int> result;

    priority_queue<outNode> outPQ;
    for(int i = 0; i < k; i++){
        if(counter[i].size() != 0)
            outPQ.push(outNode(i, carts[counter[i].front()].second));
    }

    outNode curOutNode = outNode(0, 0);
    for(int i = 0; i < N; i++){
        curOutNode = outPQ.top();
        outPQ.pop();

        result.push(counter[curOutNode.counterNum].front());
        counter[curOutNode.counterNum].pop();

        if(counter[curOutNode.counterNum].size() != 0){
            outPQ.push(outNode(curOutNode.counterNum, curOutNode.checkoutTime + carts[counter[curOutNode.counterNum].front()].second));
        }
    }

    long long tot = 0;
    for(int i = 0; i < N; i++){
        tot += (i + 1) * (long long)(carts[result.front()].first);
        result.pop();
    }

    cout << tot;

    return 0;
}