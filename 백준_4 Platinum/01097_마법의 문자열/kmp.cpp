/*
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void KMP(string str_original, string str_find);

int main()
{
	string str_original = "ABCABCDABF";
	string str_find = "ABACAABAC";
	KMP(str_original, str_find);
}

void KMP(string str_original, string str_find)
{
	int j = 0;
	vector<int> failVector;
	failVector.push_back(0);

	//실패 벡터 생성
	for (string::size_type i = 1; i < str_find.size(); i++)
	{
		if (str_find[i] == str_find[j])
		{
			j++;
			failVector.push_back(j);
		}
		else
		{
			if (!j)
				failVector.push_back(j);
			else
			{
				j = failVector[j - 1];
				i--;
			}
		}
	}


	for (vector<int>::size_type i = 0; i < failVector.size(); i++)
		cout << failVector[i] << ' ';
}
*/