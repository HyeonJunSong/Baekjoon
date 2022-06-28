//2021.11.06
//�м� �� ���� : 2m 23s
//�Է� : 54s
//���� :

#include <iostream>
#include <cmath>
#include <cstdio>

using namespace std;

int main()
{
	long double N, L, W, H;
	cin >> N >> L >> W >> H;

	
	//1. ���� ���� �� ã��
	long double min = L;
	long double elseSide[2] = { W, H };
	if (min > W) 
	{
		min = W;
		elseSide[0] = L;
	}
	else if (min > H)
	{
		min = H;
		elseSide[1] = L;
	}
	//2. ������ �� ���� �󸶳� ������ ���ϱ�
	long double elseTimes[2];
	for (int i = 0; i < 2; i++)	elseTimes[i] = elseSide[i] / min;


	//3. N / ab �� �������� ���ؼ� �ø�. �ѰŸ� �ּڰ��� ������
	printf("%.15f", min / ceil(cbrt(N / elseTimes[0] / elseTimes[1])));

	return 0;
}