//2021.11.03
//�Է� : 4m 16s
//��� : 1h 43m 23s

//�� : 1h 47m 39s

#include <iostream>
#include <string>

using namespace std;

int R, C;
string* mine;
int** rd;
int** ld;

void numOfMaxlength();
int findMaxDiamond();


int main()
{
	cin >> R >> C;

	mine = new string [R];
	rd = new int* [R];
	ld = new int* [R];
	for (int i = 0; i < R; i++)
	{
		cin >> mine[i];
		rd[i] = new int[C] {0};
		ld[i] = new int[C] {0};
	}

	numOfMaxlength();

	cout << findMaxDiamond();


	return 0;
}

//�� ��ǥ���� ���ϴ�, ���ϴ����� ���� �� �ִ� �ִ����� ���� ���ϱ�.
void numOfMaxlength()
{
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			if (mine[i][j] == '0')
				continue;

			int min, maxLength;

			//���ϴ�

			//���� ��ǥ���� ���� ���� n ã��
			if (C - j < R - i)
				min = C - j;
			else
				min = R - i;

			maxLength = 1;
			for (int k = 1; k < min; k++)
			{
				if (mine[i + k][j + k] == '0')
					break;
				maxLength++;
			}
			rd[i][j] = maxLength;




			//���ϴ�
			if (j + 1 < R - i)
				min = j + 1;
			else
				min = R - i;

			maxLength = 1;
			for (int k = 1; k < min; k++)
			{
				if (mine[i + k][j - k] == '0')
					break;
				maxLength++;
			}
			ld[i][j] = maxLength;
		}
	}
}

int findMaxDiamond()
{
	int maxSize = 0;
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			int maxN;
			if (rd[i][j] > ld[i][j])
				maxN = ld[i][j];
			else
				maxN = rd[i][j];

			//j + 1, C - j, R - i, (int)((R - i - 1) / 2) + 1
			if (maxN > j + 1)
				maxN = j + 1;
			if (maxN > C - j)
				maxN = C - j;
			if (maxN > R - i)
				maxN = R - i;
			if (maxN > (int)((R - i - 1) / 2) + 1)
				maxN = (int)((R - i - 1) / 2) + 1;


			if (maxN == 0)
				continue;
			else if (maxN == 1)
			{
				if(!maxSize)
					maxSize = 1;
				continue;
			}

			for (int k = 1; k < maxN; k++)
			{
				if (rd[i + k][j - k] >= k + 1)
					if (ld[i + k][j + k] >= k + 1)
						if(maxSize < k + 1)
							maxSize = k + 1;
			}
		}
	}

	return maxSize;
}