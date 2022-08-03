#include <iostream>
#include <deque>

using namespace std;

int main(){
    int N, K; 
    cin >> N >> K;
    deque<int> num;
    while(N != 0){
        num.push_front(N % 10);
        N /= 10;
    }
}

void minSwapSortResult(deque<int> arr, int curSortNum, deque<int>& res, int& minSortNum){
    //맨 앞에올 숫자 -> 가장 큰 숫자 구하기
    int largest = arr[0];
    for(int i = 1; i < arr.size(); i++){
        if(largest < arr[i]) largest = arr[i];
    }


    //맨앞 숫자일 경우
    minSwapSortResult

    //그 숫자랑 같은 숫자 모두 재귀 돌며 최소 정렬횟수 구하기
    for(int i = 1; i < arr.size(); i++){
        if(largest == arr[i]){
            //swap

            //재귀

            //swap 원상복구

        }
    }

}