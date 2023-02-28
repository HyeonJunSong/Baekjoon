////23.02.28
//25m 38s

#include <iostream>
#include <queue>
#include <string>

using namespace std;

int B;

class node{
public:
    int A;
    int calcCnt;
    node(int A, int calcCnt){
        this->A = A;
        this->calcCnt = calcCnt;
    }

    bool operator<(node B) const{
        if(calcCnt == B.calcCnt)
            return A < B.A;
        return calcCnt > B.calcCnt;
    }
};

int appand1(int a);
int digits(int a);

int main(){
    int A, B;
    cin >> A >> B;

    priority_queue<node> Q;

    Q.push(node(A, 1));
    
    int answer = -1;

    while(!Q.empty()){
        node curNode = Q.top();
        Q.pop();

        if(curNode.A == B){
            answer = curNode.calcCnt;
            break;
        }

        if(curNode.A * 2 <= B)
            Q.push(node(curNode.A * 2, curNode.calcCnt + 1));
        if(digits(curNode.A) < 9){
            int appand1result = appand1(curNode.A);
            if(appand1result <= B)
                Q.push(node(appand1result, curNode.calcCnt + 1));
        }
    }

    cout << answer;

    return 0;
}

int digits(int a){
    return to_string(a).size();
}

int appand1(int a){
    return stoi(to_string(a) + "1");
}