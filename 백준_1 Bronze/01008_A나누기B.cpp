#include <iostream>
#include <vector>

int main()
{
	int A = 1, B = 1;
	std::cin >> A >> B;


	std::vector<int> stack;
	for (int i = 0; i < 20; i++)
	{
		stack.push_back((int)(A / B));
		A %= B;
		A *= 10;

		if (!A)
			break;
	}

	std::vector<int>::iterator iter = stack.begin();
	std::cout << *iter;
	iter++;

	if (iter != stack.end() && (*iter))
	{
		std::cout << '.';
		for (; iter < stack.end(); iter++)
		{
			if (!(*iter))
				break;
			std::cout << *iter;
		}
	}

	return 0;
}