#include <iostream>
#include <vector>

using namespace std;

int main() {

  cout << "1 0 0\n";
  cout << "0 2 0\n";
  cout << "0 0 3\n";
  cout << "1 2 3\n";
  cout << "1 1 1\n";

  vector<int> reply(5);
  for(int i = 0; i < 5; i++)
    cin >> reply[i];

  //1번이 거짓말
  if(6 * (reply[3] - reply[1] - reply[2]) == 6 * reply[4] - 3 * reply[1] - 2 * reply[2])
    cout << (reply[3] - reply[1] - reply[2]) << ' ' << reply[1] / 2 << ' ' << reply[2] / 3;

  //2번이 거짓말
  else if(3 * (reply[3] - reply[0] - reply[2]) == 6 * reply[4] - 6 * reply[0] - 2 * reply[2])
    cout << reply[0] << ' ' << (reply[3] - reply[0] - reply[2]) / 2 << ' ' << reply[2] / 3;

  //3번이 거짓말
  else if(2 * (reply[3] - reply[0] - reply[1]) == 6 * reply[4] - 6 * reply[0] - 3 * reply[1])
    cout << reply[0] << ' ' << reply[1] / 2 << ' ' << (reply[3] - reply[0] - reply[1]) / 3;
  
  //4번이 거짓말
  else if(6 * reply[0] + 3 * reply[1] + 2 * reply[2] == 6 * reply[4])
    cout << reply[0] << ' ' << reply[1] / 2 << ' ' << reply[2] / 3;

  //5번이 거짓말
  else if(reply[0] + reply[1] + reply[2] == reply[3])
    cout << reply[0] << ' ' << reply[1] / 2 << ' ' << reply[2] / 3;

  return 0;
}