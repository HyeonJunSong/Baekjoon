//2021.11.03
//입력 : 2m 29s
//해결 : 54m 47s

//총 : 57m 16s

#include <iostream>
#include <string>

using namespace std;

//pattern : (100+1+ | 01)+
bool ifPattern(string message);

int main()
{
	int T;
	cin >> T;
	
	string* message = new string[T];

	for (int i = 0; i < T; i++)
		cin >> message[i];

	for (int i = 0; i < T; i++)
	{
		if (ifPattern(message[i]))
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}

	return 0;
}

bool ifPattern(string message)
{
	int i = 0;
	int length = message.length();


	while (i < length)
	{
		if (length - i == 1)
			break;
		else if (length - i == 2)
		{
			if (message[i] == '0' && message[i + 1] == '1')
			{
				i += 2;
				break;
			}

			break;
		}
		else if (length - i == 3)
			break;



		if (message[i] == '0' && message[i + 1] == '1')
		{
			i += 2;
			continue;
		}
		else if (message[i] == '1' && message[i + 1] == '0' && message[i + 2] == '0') 
		{
			i += 3;

			while (length - i != 0 && message[i] == '0')
				i++;
			if (length - i == 0)
			{
				i--;
				break;
			}

			i++;
			bool ifOnlyOne = true;
			while (length - i != 0 && message[i] == '1')
			{
				ifOnlyOne = false;
				i++;
			}
			if (length - i == 0)
				break;



			if (length - i == 1)
				break;

			if (message[i + 1] == '1')
			{
				i += 2;
				continue;
			}
			else if(!ifOnlyOne)
			{
				i -= 1;
				continue;
			}
			else
				break;
		}
		
		break;
	}

	return length == i;
}