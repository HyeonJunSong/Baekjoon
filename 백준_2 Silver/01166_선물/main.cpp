//2021.11.06
//분석 및 설계 : 2m 23s
//입력 : 54s
//구현 :

#include <iostream>
#include <cmath>
#include <cstdio>

using namespace std;

int main()
{
	long double N, L, W, H;
	cin >> N >> L >> W >> H;

	
	//1. 제일 좁은 변 찾기
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
	//2. 나머지 두 곳에 얼마나 들어가는지 구하기
	long double elseTimes[2];
	for (int i = 0; i < 2; i++)	elseTimes[i] = elseSide[i] / min;


	//3. N / ab 의 세제곱근 구해서 올림. 한거를 최솟값에 나눠줌
	printf("%.15f", min / ceil(cbrt(N / elseTimes[0] / elseTimes[1])));

	return 0;
}