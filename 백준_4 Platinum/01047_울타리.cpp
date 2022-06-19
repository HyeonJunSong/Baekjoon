#include <iostream>
#include <deque>
#include <algorithm>

#define INF 987654321

using namespace std;

class node{
public:
    deque<int*> fences;
    int curTimber;
    int level;
    int timberNeeded;
    
    node(deque<int*> fences, int curTimber, int level, int timberNeeded): fences(fences), curTimber(curTimber), level(level), timberNeeded(timberNeeded){};
};

bool comp_I(int* a, int* b){
    return a[0] < b[0];
}

bool comp_J(int* a, int* b){
    return a[1] < b[1];
}

bool comp_T(int* a, int* b){
    return a[2] < b[2];
}

int* savingSpace(deque<int*> fences);
int* gainingTree(deque<int*> fences);
deque<int*> popInd(deque<int*> fence, int ind);

int main(){

    int N;
    cin >> N;
    
    deque<int*> fences;
    for(int i = 0; i < N; i++){
        int* newFence = new int[4];
        cin >> newFence[0] >> newFence[1] >> newFence[2];
        newFence[3] = i;
        fences.push_back(newFence);
    }

    deque<node> Q;

    while(!Q.empty()){
        node curNode = Q.front();
        Q.pop_front();

        if(curNode.curTimber >= curNode.timberNeeded){
            cout << curNode.level;
            break;
        }


        int* res = gainingTree(curNode.fences);
        node newNode = node(popInd(curNode.fences, res[0]), popInd(curNode.fences, res[0]) + curNode.curTimber, curNode.level + 1, res[1]);
        Q.push_back(newNode);

        if(curNode.curTimber > 0){
            res = savingSpace(curNode.fences);
            newNode = node(popInd(curNode.fences, res[0]), popInd(curNode.fences, res[0]) + curNode.curTimber, curNode.level + 1, res[1]);
            Q.push_back(newNode);
        }

    }

    return 0;

}

//공간을 줄이는데 가장 효과적인 나무 -> 인덱스, 총 필요 나무
int* savingSpace(deque<int*> fences){
    int* result = new int[2];
    result[1] = INF;
    
    int height, width;

    sort(fences.begin(), fences.end(), comp_I);

    //i 제일 위쪽
    deque<int*> temp = deque<int*>(fences.begin() + 1, fences.end());
    height = temp.back()[0] - temp.front()[0] + 1;
    sort(temp.begin(), temp.end(), comp_J);
    width = temp.back()[1] - temp.front()[1] + 1;

    if(result[1] > (width + height) * 2){
        result[1] = (width + height) * 2;
        result[0] = fences.front()[3];
    }

    //i 제일 아래쪽
    temp = deque<int*>(fences.rbegin() + 1, fences.rend());
    sort(temp.begin(), temp.end(), comp_I);
    height = temp.back()[0] - temp.front()[0] + 1;
    sort(temp.begin(), temp.end(), comp_J);
    width = temp.back()[1] - temp.front()[1] + 1;

    if(result[1] > (width + height) * 2){
        result[1] = (width + height) * 2;
        result[0] = fences.back()[3];
    }

    //
    sort(fences.begin(), fences.end(), comp_J);
    //j 제일 위쪽
    temp = deque<int*>(fences.begin() + 1, fences.end());
    width = temp.back()[1] - temp.front()[1] + 1;
    sort(temp.begin(), temp.end(), comp_J);
    height = temp.back()[0] - temp.front()[0] + 1;

    if(result[1] > (width + height) * 2){
        result[1] = (width + height) * 2;
        result[0] = fences.front()[3];
    }

    //j 제일 아래쪽
    temp = deque<int*>(fences.rbegin() + 1, fences.rend());
    sort(temp.begin(), temp.end(), comp_I);
    height = temp.back()[0] - temp.front()[0] + 1;
    sort(temp.begin(), temp.end(), comp_J);
    width = temp.back()[1] - temp.front()[1] + 1;

    if(result[1] > (width + height) * 2){
        result[1] = (width + height) * 2;
        result[0] = fences.back()[3];
    }

    return result;
}

//벴을 때 가장 이득인 나무 -> 인덱스, 총 필요나무
int* gainingTree(deque<int*> fences){
    int* result = new int[2];

    sort(fences.begin(), fences.end(), comp_T);
    result[0] = fences.back()[3];

    deque<int*> temp = deque<int*>(fences.rbegin() + 1, fences.rend());
    sort(temp.begin(), temp.end(), comp_I);
    int width = temp.back()[1] - temp.front()[1] + 1;
    sort(temp.begin(), temp.end(), comp_J);
    int height = temp.back()[0] - temp.front()[0] + 1;

    result[1] = (width + height) * 2;

    return result;
}

deque<int*> popInd(deque<int*> fence, int ind){
    deque<int*> result;
    for(int i = 0; i < fence.size(); i++){
        if(fence[i][3] == ind)
            continue;
        result.push_back(fence[i]);
    }
    return result;
}

int indTimber(deque<int*> fence, int ind){
    for(int i = 0; i < fence.size(); i++){
        if(fence[i][3] == ind)
            return fence[i][2];
    }
}