#include <iostream>
#include <cmath>

using namespace std;

int** coor;
int*** planet;
int* pN;


int numOfMinPath(int i);


int main()
{
	int T;
	cin >> T;
	coor = new int* [T];
	planet = new int** [T];
	pN = new int[T];


	for (int i = 0; i < T; i++)
	{
		coor[i] = new int[4];
		for (int j = 0; j < 4; j++) cin >> coor[i][j];

		cin >> pN[i];
		planet[i] = new int* [pN[i]];
		for (int j = 0; j < pN[i]; j++)
		{
			planet[i][j] = new int[3];
			for (int k = 0; k < 3; k++) cin >> planet[i][j][k];
		}
	}

	for (int i = 0; i < T; i++) cout << numOfMinPath(i) << endl;

	return 0;
}

int numOfMinPath(int i)
{
	int cnt = 0;
	for (int j = 0; j < pN[i]; j++)
	{
		bool ifaIn = false;
		bool ifbIn = false;

		if (pow((coor[i][0] - planet[i][j][0]), 2) + pow((coor[i][1] - planet[i][j][1]), 2) < pow(planet[i][j][2], 2)) ifaIn = true;
		if (pow((coor[i][2] - planet[i][j][0]), 2) + pow((coor[i][3] - planet[i][j][1]), 2) < pow(planet[i][j][2], 2)) ifbIn = true;

		if (ifaIn && ifbIn)
			continue;

		if (ifaIn) cnt++;
		else if (ifbIn) cnt++;
	}

	return cnt;
}