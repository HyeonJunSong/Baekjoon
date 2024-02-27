#include <iostream>
#include <vector>

using namespace std;

#define LL long long
#define INF 5005000001

int N;
vector<LL> notes;
vector<vector<LL>> memo;

LL getAns(LL idx, LL curCombo){

	if(idx >= N) return 0;

	if(memo[idx][curCombo] != INF)
		return memo[idx][curCombo];

	int after = max(max(getAns(idx + 1, curCombo + 1), getAns(idx + 2, 1)), getAns(idx + 3, 1));

	memo[idx][curCombo] = notes[idx] * curCombo + after;

	return memo[idx][curCombo];
}

int main() {

	cin >> N;
	notes = vector<LL>(N);

	for (int i = 0; i < N; i++) cin >> notes[i];
	memo = vector<vector<LL>>(N + 1, vector<LL>(N + 1, INF));

	LL ans = 0;
	if(ans < getAns(0, 1))
		ans = getAns(0, 1);
	if(ans < getAns(1, 1))
		ans = getAns(1, 1);
	if(ans < getAns(2, 1))
		ans = getAns(2, 1);
	

	cout << ans;

	return 0;
}