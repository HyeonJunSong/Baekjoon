//2021.11.04
//�м� �� ���� : 2m 18s
//�Է� : 48s
//���� : 34m 24s ���� ����
// �ð��ʰ� ��
//���� : 20m 58s

//�� : 58m 128s


#include <iostream>

using namespace std;

int main()
{
	long double X, Y;
	cin >> X >> Y;

	int Z = (int)((Y / X) * 100);
	if (Z == 99 || Z == 100)
		cout << -1;
	else
	{
		long double st = 0;
		long double ed = X;
		long double mid = 0;
		while (st < ed)
		{
			mid = (long double)((int)((st + ed) / 2));

			int tempZ = (int)(((Y + mid) / (X + mid)) * 100);
			if (Z == (int)tempZ)
			{
				if ((int)(((Y + mid + (long double)1) / (X + mid + (long double)1)) * 100) != Z)
				{
					mid++;
					break;
				}
				st = mid + 1;
			}
			else
			{
				if ((int)(((Y + mid - (long double)1) / (X + mid - (long double)1)) * 100) == Z)
					break;

				ed = mid - 1;
			}
		}

		cout << (int)mid;
	}

	return 0;
}