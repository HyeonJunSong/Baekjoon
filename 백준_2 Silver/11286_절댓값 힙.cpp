#include <iostream>
#include <queue>
#include <cmath>

using namespace std;

class node{
public:
    int num;
    node(int num){
        this->num = num;
    }

    bool operator< (node b) const{
        if(abs(num) == abs(b.num))
            return num > b.num;
        return abs(num) > abs(b.num);
    }

};

int main(){
    int N;
    cin >> N;

    int inp;
    priority_queue<node> PQ;
    for(int i = 0; i < N; i++){
        cin >> inp;
        if(inp == 0){
            if(PQ.empty()){
                cout << 0 << endl;
            }
            else{
                cout << PQ.top().num << endl;
                PQ.pop();
            }
        }
        else{
            PQ.push(inp);
        }
    }

    return 0;
}