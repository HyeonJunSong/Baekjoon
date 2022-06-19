#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

int ask(char arrName, int index);

int cnt = 0;
vector<int>* arr;

int main(){

    int N;
    cin >> N;

    srand(time(NULL));
    arr = new vector<int>[2];

    for(int i = 0; i < 2; i++)
        for(int j = 0; j < N; j++)
            arr[i].push_back(rand());
    
    sort(arr[0].begin(), arr[0].end());
    sort(arr[1].begin(), arr[1].end());
    
    vector<int> C;
    for(int i = 0; i < N; i++){
        C.push_back(arr[0][i]);
        C.push_back(arr[1][i]);
    }
    sort(C.begin(), C.end());

    for(int i = 0; i < arr[0].size(); i++)
        cout << arr[0][i] << ' ';
    cout << endl;
    for(int i = 0; i < arr[1].size(); i++)
        cout << arr[1][i] << ' ';
    cout << endl;
    for(int i = 0; i < C.size(); i++)
        cout << C[i] << ' ';
    cout << endl;


    //rear값 미포함
    int Acur = (int)(N / 2);
    int Afron = 0;
    int Arear = N;

    int Bcur = (int)(N / 2);
    int Bfron = 0;
    int Brear = N;

    int Adata = ask('A', Acur);
    int Bdata = ask('B', Bcur);

    while(Arear - Afron > 1 && Brear - Bfron > 1){
        if(Acur + Bcur < N - 2){
            if(Adata < Bdata){
                Afron = Acur + 1;
                Acur = (int)((Afron + Arear) / 2);
                Adata = ask('A', Acur);
            }
            else if(Adata > Bdata){
                Bfron = Bcur + 1;
                Bcur = (int)((Bfron + Brear) / 2);
                Bdata = ask('B', Bcur);
            }
            else{
                Afron = Acur + 1;
                Acur = (int)((Afron + Arear) / 2);
                Adata = ask('A', Acur);

                Bfron = Bcur + 1;
                Bcur = (int)((Bfron + Brear) / 2);
                Bdata = ask('B', Bcur);
            }
        }
        else if(Acur + Bcur > N - 2){
            if(Adata < Bdata){
                Brear = Bcur;
                Bcur = (int)((Bfron + Brear) / 2);
                Bdata = ask('B', Bcur);
            }
            else if(Adata > Bdata){
                Arear = Acur;
                Acur = (int)((Afron + Arear) / 2);
                Adata = ask('A', Acur);
            }
            else{
                Arear = Acur;
                Acur = (int)((Afron + Arear) / 2);
                Adata = ask('A', Acur);

                Brear = Bcur;
                Bcur = (int)((Bfron + Brear) / 2);
                Bdata = ask('B', Bcur);
            }
        }
        else{
            if(Adata < Bdata){
                Afron = Acur;
                Acur = (int)((Afron + Arear) / 2);                
                Adata = ask('A', Acur);

                Brear = Bcur + 1;
                Bcur = (int)((Bfron + Brear) / 2);
                Bdata = ask('B', Bcur);
            }
            else if(Adata > Bdata){
                Bfron = Bcur;
                Bcur = (int)((Bfron + Brear) / 2);
                Bdata = ask('B', Bcur);

                Arear = Acur + 1;
                Acur = (int)((Afron + Arear) / 2);
                Adata = ask('A', Acur);
            }
            else{
                break;
            }
        }
    }


    if(Acur + Bcur != N - 2){
        if(Arear - Afron > 1){
            Acur = N - 2 - Bcur;
            Adata = ask('A', Acur);
        }
        else if(Brear - Bfron > 1){
            Bcur = N - 2 - Acur;
            Bdata = ask('B', Bcur);
        }
    }

    Adata > Bdata ? cout << "! " << Adata : cout << "! " << Bdata;

    cout << endl << cnt;
    cout << endl << C[N - 1] << endl;

    if(Adata > Bdata){
        if(Adata == C[N - 1] && cnt <= 40)
            cout << "correct!";
        else
            cout << "wrongㅜㅠㅜ";
    }
    else{
        if(Bdata == C[N - 1] && cnt <= 40)
            cout << "correct!";
        else
            cout << "wrongㅜㅠㅜ";
    }
    return 0;
}


int ask(char arrName, int index){
    cout << arrName << ' ' << index << endl;

    cnt++;
    if(arrName == 'A')
        return arr[0][index];
    else
        return arr[1][index];
}


/*
int ask(char arrName, int index){
    cnt++;
    cout << arrName << " ? " << index;
    cout << flush;
    
    int result;
    cin >> result;
    return result;
}
*/