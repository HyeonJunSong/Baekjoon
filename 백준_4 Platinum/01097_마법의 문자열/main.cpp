/*
#include <iostream>
#include <vector>
#include <string>

using namespace std;

string* sList;
int N, K;


int Combination(int n, int r, vector<int>& indexStack, bool* ifIndexUsed);
bool deformedKMP(string totString);


int main()
{
	//입력
	cin >> N;

	sList = new string[N];
	for (int i = 0; i < N; i++)
	{
		cin >> sList[i];
	}
	cin >> K;


	//순열 & kmp
	vector<int> v;
	bool* ifIndexUsed = new bool[N];
	for (int i = 0; i < N; i++)
		ifIndexUsed[i] = false;

	cout << Combination(N, N, v, ifIndexUsed);

	return 0;
}

int Combination(int n, int r, vector<int>& indexStack, bool* ifIndexUsed)
{
	int tot = 0;
	//기저
	if (indexStack.size() == (vector<int>::size_type)(r))
	{
		string totString = "";

		for (vector<int>::size_type i = 0; i < indexStack.size(); i++)
			totString += sList[(int)indexStack[i]];

		if (deformedKMP(totString))
			return 1;
		return 0;
	}

	//재귀호출
	for (int i = 0; i < n; i++)
	{
		if(ifIndexUsed[i])
			continue;

		indexStack.push_back(i);
		ifIndexUsed[i] = true;
		tot += Combination(n, r, indexStack, ifIndexUsed);
		indexStack.pop_back();
		ifIndexUsed[i] = false;
	}

	return tot;
}

bool deformedKMP(string totString)
{

	int j = 0;
	int failVector[160];
	failVector[0] = 0;

	//vector<int> failVector;
	//failVector.push_back(0);

	//실패 벡터 생성
	for (string::size_type i = 1; i < totString.size(); i++)
	{
		if (totString[i] == totString[j])
		{
			j++;
			failVector[i] = j;
		}
		else
		{
			if (!j)
				failVector[i] = j;
			else
			{
				j = failVector[j - 1];
				i--;
			}
		}
	}

	string::size_type lastIndex = (string::size_type)(j);
	//int lastIndex = failVector.back();

	if (!lastIndex || totString.size() % (totString.size() - (string::size_type)(lastIndex)))
	{
		if (K == 1)
			return true;
		return false;
	}

	if (K == (int)(totString.size() / (totString.size() - (string::size_type)(lastIndex))))
		return true;
	return false;
}
*/