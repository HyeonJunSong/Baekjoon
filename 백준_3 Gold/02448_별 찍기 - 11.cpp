////230514
//30m 49s

#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> triangle = {
    "  *  ",
    " * * ",
    "*****",
};

void writeTriangle(int N, int stInd);
void printTriangle();
vector<string> totTriangle;

int main(){
    int N;
    cin >> N;

    totTriangle = vector<string>(N, "");

    writeTriangle(N, 0);
    printTriangle();

    return 0;
}

void writeTriangle(int N, int stInd){

    if(N == 3){
        for(int i = 0; i < 3; i++)
            totTriangle[stInd + i] += triangle[i];
        return;
    }

    ////위 삼각형
    //좌측공간
    for(int i = 0; i < N / 6; i++)
        for(int j = 0; j < 3; j++)
            for(int k = 0; k < N / 6; k++)
                totTriangle[stInd + i * 3 + j] += "   ";
    
    //삼각형
    writeTriangle(N / 2, stInd);
    
    //우측공간
    for(int i = 0; i < N / 6; i++)
        for(int j = 0; j < 3; j++)
            for(int k = 0; k < N / 6; k++)
                totTriangle[stInd + i * 3 + j] += "   ";


    ////아래 삼각형
    //삼각형
    writeTriangle(N / 2, stInd + N / 2);
    //공백
    for(int i = 0; i < N / 6; i++)
        for(int j = 0; j < 3; j++)
            totTriangle[stInd + N / 2 + i * 3 + j] += " ";
    //삼각형
    writeTriangle(N / 2, stInd + N / 2);
    return;
}

void printTriangle(){
    for(auto iter = totTriangle.begin(); iter != totTriangle.end(); iter++)
        cout << *iter << '\n';
}