#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;


class Karatsuba{
    //vector내 숫자는 거꾸로 돼있다고 가정합니다.
    //앞에서부터 1의자리, 10의자리, 100의 자리, 쭉쭉

public:
    static const int basis = 4;

    //A * B
    static vector<int> multiply(vector<int> A, vector<int> B){
        vector<int> result(A.size() + B.size() - 1);
        for(int i = 0; i < A.size(); i++){
            for(int j = 0; j < B.size(); j++){
                result[i + j] += A[i] * B[j];
            }
        }
    }

    //A + B
    static vector<int> add(vector<int> A, vector<int> B){
        vector<int> result = A;
        for(int i = 0; i < B.size(); i++){
            if(i >= result.size()){
                result.push_back(B[i]);
            }
            else{
                result[i] += B[i];
            }
        }

        return result;
    }

    //A - B
    static vector<int> sub(vector<int> A, vector<int> B){
        vector<int> result = A;
        for(int i = 0; i < B.size(); i++){
            if(i >= result.size()){
                result.push_back(-1 * B[i]);
            }
            else{
                result[i] = result[i] - B[i];
            }
        }

        return result;
    }

    //카라츠바 분할정복부분
    static vector<int> DC(vector<int> A, vector<int> B){

        //분할
        int half = A.size() / 2 < B.size() / 2 ?  (int)(A.size() / 2) : (int)(B.size() / 2);

        if(half <= basis)
            return multiply(A, B);

        //계산
        vector<int> z0 = DC(vector<int>(A.begin(), A.begin() + half), vector<int>(B.begin(), B.begin() + half));
        vector<int> z2 = DC(vector<int>(A.begin() + half, A.end()), vector<int>(B.begin() + half, B.end()));
        vector<int> z1 = sub(sub( DC(
                            add(vector<int>(A.begin(), A.begin() + half), vector<int>(A.begin() + half, A.end())),
                             add(vector<int>(B.begin(), B.begin() + half), vector<int>(B.begin() + half, B.end())))
                             , z0), z2);

        //병합
        vector<int> result(2 * half + z2.size());
        for(int i = 0; i < z0.size(); i++)
            result[i] = z0[i];
        for(int i = 0; i < z1.size(); i++)
            result[half + i] = z1[i];
        for(int i = 0; i < z2.size(); i++)
            result[half * 2 + i] = z2[i];
        
        return result;
    }

    //자릿수 올려서 똑바로 만드는 과정
    static vector<int> toNormalNumb(vector<int> num){
        int i = 0;
        for(; i < num.size() - 1; i++){
            if(num[i] / 10 >= 1){
                num[i + 1] += (int)(num[i] / 10);
                num[i] %= 10;
            }
        }

        while(num[i] / 10 >= 1){
            num.push_back((int)(num[i] / 10));
            num[i] %= 10;
            i++;
        }

        return num;
    }

    //최종버전
    static vector<int> karatsuba(vector<int> A, vector<int> B){
        vector<int> result = DC(A, B);
        return toNormalNumb(result);
    }
};

void printReverse(vector<int> num){
    for(auto iter = num.rbegin(); iter != num.rend(); iter++){
        cout << *iter;
    }
}

int main(){
    string A, B;
    cin >> A >> B;
    
    vector<int> numA, numB;
    for(int i = 0; i < A.size(); i++)
        numA.push_back(A[i]-'0');
    for(int i = 0; i < B.size(); i++)
        numB.push_back(B[i]-'0');
    
    reverse(numA.begin(), numA.end());
    reverse(numB.begin(), numB.end());

    printReverse(Karatsuba::karatsuba(numA, numB));
}