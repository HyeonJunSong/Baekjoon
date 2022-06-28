//2021.11.06
//분석 및 설계 : 2m 15s
//입력 : 2m 48s 
//구현 : 20m 16s

//총 : 25m 19s

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	int nA, nB;
	cin >> nA >> nB;

	vector<int> A, B;

	for (int i = 0; i < nA; i++) 
	{
		int inp;
		cin >> inp;
		A.push_back(inp);
	}

	for (int i = 0; i < nB; i++) 
	{
		int inp;
		cin >> inp;
		B.push_back(inp);
	}

	sort(A.begin(), A.end());
	sort(B.begin(), B.end());


	int tot = 0;

	int i = 0, j = 0;
	while (i < nA && j < nB)
	{
		if (A[i] == B[j])
		{
			while (i + 1 < nA && A[i] == A[i + 1]) i++;
			while (i + 1 < nB && B[j] == B[j + 1]) j++;
			i++;
			j++;
		}
		else
		{
			if (A[i] < B[j]) i++;
			else j++;

			tot++;
		}
	}

	if (i < nA) tot += nA - i;
	else tot += nB - j;

	cout << tot;

	return 0;
}