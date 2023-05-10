#include <iostream>
#include <vector>

using namespace std;

int N, K;
vector<pair<int, int>> items;
vector<vector<int>> cache;

int getLargestValue(int ind, int spaceLeft);

int main(){
    cin >> N >> K;
    items = vector<pair<int, int>>(N);
    for(int i = 0; i < N; i++)
        cin >> items[i].first >> items[i].second;
    
    cache = vector<vector<int>>(N + 1, vector<int>(K + 1, -1));

    cout << getLargestValue(0, K);

    return 0;
}

int getLargestValue(int ind, int spaceLeft){
    
    ////����
    if(ind == N || spaceLeft <= 0)
        return 0;

    ////���

    //�ȳ־��� ��
    if(cache[ind + 1][spaceLeft] == -1)
        cache[ind + 1][spaceLeft] = getLargestValue(ind + 1, spaceLeft);
    //�־��� ��
    if(spaceLeft - items[ind].first >= 0){
        if(cache[ind + 1][spaceLeft - items[ind].first] == -1)
            cache[ind + 1][spaceLeft - items[ind].first] = getLargestValue(ind + 1, spaceLeft - items[ind].first);
    }
    else
        return cache[ind + 1][spaceLeft];

    ////��ȯ
    if(cache[ind + 1][spaceLeft] > cache[ind + 1][spaceLeft - items[ind].first] + items[ind].second)
        return cache[ind + 1][spaceLeft];
    else
        return cache[ind + 1][spaceLeft - items[ind].first] + items[ind].second;
}