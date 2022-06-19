#include <iostream>

using namespace std;


typedef struct Grab{
	int st;
	int ed;
	int sum;
}grab;

int* jewels;
grab*** Memo;

grab* LargestGrab(int st, int ed);

int main(){
	int N, M;
	cin >> N >> M;
	jewels = new int[N];
	for(int i = 0; i < N; i++)
		cin >> jewels[i];


	Memo = new grab**[N];
	for(int i = 0; i < N; i++){
		Memo[i] = new grab*[N];
		for(int j = 0; j < N; j++)
			Memo[i][j] = nullptr;
	}

	grab* result = LargestGrab(0, N - 1);

	int max = result[0].sum;
	if(result[1].sum > max)
		max = result[1].sum;
	if(result[2].sum > max)
		max = result[2].sum;
	
	cout << max;

	return 0;
}


grab* LargestGrab(int st, int ed){
	grab* ret = new grab[3];
	
	if(st == ed){
		ret[0].st = st;
		ret[0].ed = ed;
		ret[0].sum = jewels[st];
		ret[1].st = st;
		ret[1].ed = ed;
		ret[1].sum = jewels[st];
		ret[2].st = st;
		ret[2].ed = ed;
		ret[2].sum = jewels[st];

		return ret;
	}


	int mid = (int)((st + ed) / 2);

	if(Memo[st][mid] == nullptr)
		Memo[st][mid] = LargestGrab(st, mid);
	
	if(Memo[mid + 1][ed] == nullptr)
		Memo[mid + 1][ed] = LargestGrab(mid + 1, ed);
	
	grab* left = Memo[st][mid];
	grab* right = Memo[mid + 1][ed];

	ret[1] = left[0];

	if(left[1].sum > ret[1].sum)
		ret[1] = left[1];
	
	if(left[2].sum + right[0].sum > ret[1].sum){
		ret[1].st = left[2].st;
		ret[1].ed = right[0].ed;
		ret[1].sum = left[2].sum + right[0].sum;
	}
	
	if(right[1].sum > ret[1].sum)
		ret[1] = right[1];
	
	if(right[2].sum > ret[1].sum)
		ret[1] = right[2];
	
	ret[0] = left[0];
	ret[2] = right[2];
	
	return ret;
}