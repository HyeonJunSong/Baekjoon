#include <iostream>
#include <vector>

using namespace std;

int main(){
    int N;
    cin >> N;

    vector<int> smaSet;
    vector<int> bigSet;

    for(int i = 0; i < N / 2; i++){
        int inp1, inp2;
        cin >> inp1 >> inp2;
        if(inp1 > inp2){
            smaSet.push_back(inp2);
            bigSet.push_back(inp1);
        }
        else{
            smaSet.push_back(inp1);
            bigSet.push_back(inp2);
        }
    }

    int lastNum = -1;
    if(N % 2){
        cin >> lastNum;
    }



    if(bigSet.size() == 0)
        cout << lastNum * lastNum;
    else{
        int min = smaSet[0];
        int max = bigSet[0];
        for(int i = 1; i < smaSet.size(); i++){
            if(min > smaSet[i])
                min = smaSet[i];
        }
        for(int i = 1; i < bigSet.size(); i++){
            if(max < bigSet[i])
                max= bigSet[i];
        }

        if(lastNum != -1){
            if(min > lastNum)
                min = lastNum;
            if(max < lastNum)
                max = lastNum;
        }
        cout << min * max;
    }
    return 0;
}