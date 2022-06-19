//2021.11.06
//분석 및 설계 : 8m 24s
//입력 및 구현: 59m 28s 에서 포기

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct Node
{
	long int soldierNum;
	int cnt;
}node;
int main()
{
	int N;
	cin >> N;
	vector<long int>* soldiers = new vector<long int>[N];

	for (int i = 0; i < N; i++)
	{
		int T;
		cin >> T;
		for (int j = 0; j < T; j++)
		{
			long int inp;
			cin >> inp;
			soldiers[i].push_back(inp);
		}
		sort(soldiers[i].begin(), soldiers[i].end());
	}

	for (int i = 0; i < N; i++)
	{
		vector<node> numOfSoldiers;

		numOfSoldiers.push_back({ soldiers[i][0], 1 });

		for (vector<long int>::size_type j = 1; j < soldiers[i].size(); j++)
		{
			if (numOfSoldiers.back().soldierNum == soldiers[i][j]) numOfSoldiers.back().cnt++;
			else 
			{
				numOfSoldiers.push_back({soldiers[i][j], 1});
			}
		}

		int max = 0;
		int maxI = -1;
		for (vector<int>::size_type j = 0; j < numOfSoldiers.size(); j++)
			if (numOfSoldiers[j].cnt > max) 
			{ 
				max = numOfSoldiers[j].cnt;
				maxI = j;
			};
		
		if ((double)max / (double)(soldiers[i].size()) > 0.5) cout << numOfSoldiers[maxI].soldierNum << endl;
		else cout << "SYJKGW" << endl;
	}


	return 0;
}