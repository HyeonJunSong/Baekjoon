#include <iostream>
#include <vector>

using namespace std;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, M;
	cin >> N >> M;
	vector<vector<int>> dis(N, vector<int>(N, 987654321));
	for(int i = 0; i < M; i++){
		int f1,f2;
		cin >> f1 >> f2;
		f1--; f2--;
		dis[f1][f2] = 1;
		dis[f2][f1] = 1;
	}

	for(int i = 0; i < N; i++) dis[i][i] = 0;

	for(int k = 0; k < N; k++)
		for(int i = 0; i < N; i++)
			for(int j = 0; j < N; j++)
				dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
	
	
	int ans = -1;
	int ansDis = 987654321;
	for(int i = 0; i < N; i++){

		int curDisSum = 0;
		for(int j = 0; j < N; j++)
			curDisSum += dis[i][j];
		

		if(ansDis > curDisSum){
			ans = i;
			ansDis = curDisSum;
		}
	}

	cout << ans + 1;

	return 0;
}