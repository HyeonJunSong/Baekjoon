#include <iostream>
#include <string>
#include <set>
#include <vector>

using namespace std;

int main(){
    string numStr;
    int K;
    cin >> numStr;
    cin >> K;

    //문자열 숫자벡터로 변환
    vector<int> num;
    for(int i = 0; i < numStr.size(); i++)
        num.push_back(numStr[i] - '0');

    //처음부터 set의 사이즈가 K가 될때까지 넣기
    set<int> s;
    int I = 0;
    for(; I < num.size(); I++){
        s.insert(num[I]);
        if(s.size() == K + 1){
            s.erase(num[I]);
            break;
        }
    }

    //끝까지 갔는지 여부
    if(I == num.size()){
        if(s.size() != K){

            if(K > num.size()){

            }
            else{
                //set의 각 원소별로 몇개씩 있는지 확인
                vector<int> numOfElements(10, 0);
                for(int i = 0; i < num.size(); i++)
                    numOfElements[num[i]]++;
                
                //시작할 J알아내기
                vector<int> copyNOE = numOfElements;
                int J = num.size() - 1;
                int numLeft = K - s.size();
                for(; J >= 0; J--){

                    if(copyNOE[num[J]] <= 1 || num[J] == 9) continue;
                    copyNOE[num[J]]--;

                    numLeft--;
                    if(numLeft == 0) break;
                }

                if(J == -1){

                }
                else{
                    for(int j = J; j < num.size(); j++){
                        int minNum = 0;
                        
                    }
                }
            }
        }
    }
    else{

        //현재 I를 변경해서 K자리를 맞출 수 있는지
        bool ifCurDigitAble = false;
        for(int i = num[I] + 1; i < 10; i++){
            if(s.find(i) != s.end()){
                ifCurDigitAble = true;
                num[I] = i;
                break;
            }
        }

        if(ifCurDigitAble){
            for(int i = I + 1; i < num.size(); i++)
                num[i] = *(s.begin());
        }
        else{
            //맨뒤 숫자 바꾸기

            //맨뒤가 9일때

            s.erase(num[I - 1]);
            s.insert(num[I - 1] + 1);

            for(int i = 0; i < I; i++)
                if(num[i] == num[I - 1]) num[i]++;

            if(s.size() < K){
                int newNum;
                for(int i = 0; i < 10; i++){
                    if(s.find(i) == s.end()){
                        newNum = i;
                        break;
                    }
                }

                if(*(s.begin()) < newNum){
                    for(int i = I; i < num.size() - 1; i++)
                        num[i] = *(s.begin());
                    num[num.size() - 1] = newNum;
                }
                else{
                    for(int i = I; i < num.size(); i++)
                        num[i] = newNum;
                }
            }
            else{
                for(int i = I; i < num.size(); i++)
                    num[i] = *(s.begin());
            }
        }
    }

    return 0;
}