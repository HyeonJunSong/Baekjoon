#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int N, K;

int findNThatK(int K);
long long getKofN(int n);
long long getLowerNum(int i, int target);
int findAns(int NthatK);

int main(){
    cin >> N >> K;
    cout << findNThatK(K);

    return 0;
}

int findNThatK(int K){
    int st = 1;
    int ed = K;
    int mid;

    while(st <= ed){
        mid = (st + ed) / 2;

        long long curK = getKofN(mid);

        if(K == curK)
            return findAns(mid);
        
        if(K > curK)
            st = mid + 1;
        else
            ed = mid - 1;
    }

    if(K > getKofN(st))
        return findAns(st);
    else if(K > getKofN(ed))
        return findAns(ed);
    else
        return findAns(ed - 1);
}

int findAns(int NthatK){
    while(true){
        for(int i = ceil((double)(NthatK) / N); i <= sqrt(NthatK); i++)
            if(NthatK % i == 0 && NthatK / i <= N)
                return NthatK;

        NthatK += 1;
    }
}

long long getKofN(int n){

    long long tot = 0;
    for(int i = 1; i <= N; i++){
        tot += getLowerNum(i, n);
    }

    return tot + 1;
}

long long getLowerNum(int i, int target){

    long long st = 1;
    long long ed = N;
    long long mid;

    while(st <= ed){
        mid = (st + ed) / 2;

        if(target == mid * i)
            return mid - 1;
        
        if(target > mid * i)
            st = mid + 1;
        else
            ed = mid - 1;
    }

    if(st > N)
        return N;
    if(ed <= 0)
        return 0;

    if(target > st * i)
        return st;
    else if(target > ed * i)
        return ed;
    else
        return ed - 1;

}