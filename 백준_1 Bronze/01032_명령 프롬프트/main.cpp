#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
	int N;
	cin >> N;
	string* str = new string[N];
	for (int i = 0; i < N; i++) cin >> str[i];

	vector<char> res;
	
	for (int i = 0; i < str[0].length(); i++)
	{
		char c = str[0][i];

		bool ifSame = true;
		for(int j = 0; j < N; j++)
			if (c != str[j][i])
			{
				ifSame = false;
				break;
			}

		if (ifSame) res.push_back(c);
		else res.push_back('?');
	}

	for (vector<char>::size_type i = 0; i < res.size(); i++)
		cout << res[i];

	return 0;
}