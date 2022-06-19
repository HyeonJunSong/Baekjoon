#include <iostream>
#include <vector>

int main()
{
	int A = 1, B = 1;
	std::cin >> A >> B;

	int res[1010] = { 0 };
	int size = 0;

	for (int i = 0; i < 1010; i++)
	{
		res[i] = (int)(A / B);
		A %= B;
		A *= 10;

		size++;

		if (!A)
			break;
	}

	std::cout << res[0];
	int i = 1;

	std::cout << '.';
	for (; i < size; i++)
	{
		std::cout << res[i];
	}

	return 0;
}