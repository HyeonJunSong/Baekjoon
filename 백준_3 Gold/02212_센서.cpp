#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N;
    cin >> N;
    int K;
    cin >> K;
    vector<int> sensors(N);

    for (int i = 0; i < N; i++)
        cin >> sensors[i];


    //센서 정렬
    sort(sensors.begin(), sensors.end());

    //센서들사이의 거리 측정
    vector<int> distance;
    for (vector<int>::size_type i = 0; i < sensors.size() - 1; i++)
        distance.push_back(sensors[i + 1] - sensors[i]);

    //센서들사아의 거리 정렬
    sort(distance.begin(), distance.end());


    //K-1개 남을때까지 누적
    int tot = 0;
    for (int i = 0; i < ((int)(distance.size()) - K + 1); i++)
        tot += distance[i];

    cout << tot;

    return 0;
}