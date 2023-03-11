////23.03.11
//이해 및 설계 : 10m 23s
//입력 : 12m 22s
//구현 : 44m 21s

//tot : 1h 7m 6s

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// NUM X: X를 스택의 가장 위에 저장한다. (0 ≤ X ≤ 109)
// POP: 스택 가장 위의 숫자를 제거한다.
// INV: 첫 번째 수의 부호를 바꾼다. (42 -> -42)
// DUP: 첫 번째 숫자를 하나 더 스택의 가장 위에 저장한다.
// SWP: 첫 번째 숫자와 두 번째 숫자의 위치를 서로 바꾼다.
// ADD: 첫 번째 숫자와 두 번째 숫자를 더한다.
// SUB: 첫 번째 숫자와 두 번째 숫자를 뺀다. (두 번째 - 첫 번째)
// MUL: 첫 번째 숫자와 두 번째 숫자를 곱한다.
// DIV: 첫 번째 숫자로 두 번째 숫자를 나눈 몫을 저장한다. 두 번째 숫자가 피제수, 첫 번째 숫자가 제수이다.
// MOD: 첫 번째 숫자로 두 번째 숫자를 나눈 나머지를 저장한다. 두 번째 숫자가 피제수, 첫 번째 숫자가 제수이다.

int main() {

    vector<pair<int, int>> command;
    string commandInp;
    int inp, N;
    int temp;
    int stackSize;
    bool ifError;
    int dividend, divisor;
    long long multTemp;

    while (true) {

        command = vector<pair<int, int>>();

        //명령어 입력
        while (true) {
            cin >> commandInp;
            if (commandInp == "QUIT") return 0;
            if (commandInp == "END") break;

            if (commandInp == "NUM") {
                cin >> inp;
                command.push_back(pair<int, int>(0, inp));
            }
            else if (commandInp == "POP") command.push_back(pair<int, int>(1, 0));
            else if (commandInp == "INV") command.push_back(pair<int, int>(2, 0));
            else if (commandInp == "DUP") command.push_back(pair<int, int>(3, 0));
            else if (commandInp == "SWP") command.push_back(pair<int, int>(4, 0));
            else if (commandInp == "ADD") command.push_back(pair<int, int>(5, 0));
            else if (commandInp == "SUB") command.push_back(pair<int, int>(6, 0));
            else if (commandInp == "MUL") command.push_back(pair<int, int>(7, 0));
            else if (commandInp == "DIV") command.push_back(pair<int, int>(8, 0));
            else if (commandInp == "MOD") command.push_back(pair<int, int>(9, 0));
        }

        //프로그램 입력 및 실행
        cin >> N;
        for (int i = 0; i < N; i++) {
            cin >> inp;
            vector<int> stack(1, inp);
            stackSize = 1;

            ifError = false;
            for (auto iter = command.begin(); iter != command.end(); iter++) {
                switch (iter->first) {
                case 0:
                    stack.push_back(iter->second);
                    stackSize++;
                    break;
                case 1:
                    if (stackSize == 0) {
                        ifError = true;
                        break;
                    }
                    stack.pop_back();
                    stackSize--;
                    break;
                case 2:
                    if (stackSize == 0) {
                        ifError = true;
                        break;
                    }
                    stack.back() *= -1;
                    break;
                case 3:
                    stack.push_back(stack.back());
                    stackSize++;
                    break;
                case 4:
                    if (stackSize <= 1) {
                        ifError = true;
                        break;
                    }
                    temp = stack[stackSize - 1];
                    stack[stackSize - 1] = stack[stackSize - 2];
                    stack[stackSize - 2] = temp;
                    break;
                case 5:
                    if (stackSize <= 1) {
                        ifError = true;
                        break;
                    }
                    if(stack[stackSize - 2] + stack[stackSize - 1] > 1000000000){
                        ifError = true;
                        break;   
                    }

                    stack[stackSize - 2] += stack[stackSize - 1];
                    stack.pop_back();
                    stackSize--;
                    break;
                case 6:
                    if (stackSize <= 1) {
                        ifError = true;
                        break;
                    }
                    if(stack[stackSize - 2] - stack[stackSize - 1] < -1000000000){
                        ifError = true;
                        break;   
                    }

                    stack[stackSize - 2] -= stack[stackSize - 1];
                    stack.pop_back();
                    stackSize--;
                    break;
                case 7:
                    if (stackSize <= 1) {
                        ifError = true;
                        break;
                    }

                    multTemp = (long long)(stack[stackSize - 2]) * (long long)(stack[stackSize - 1]);
                    if (multTemp > 1000000000) {
                        ifError = true;
                        break;
                    }

                    stack[stackSize - 2] *= stack[stackSize - 1];
                    stack.pop_back();
                    stackSize--;
                    break;
                case 8:
                    if (stackSize <= 1) {
                        ifError = true;
                        break;
                    }
                    dividend = abs(stack[stackSize - 2]);
                    divisor = abs(stack[stackSize - 1]);
                    if (divisor == 0) {
                        ifError = true;
                        break;
                    }

                    if ((stack[stackSize - 2] < 0 && stack[stackSize - 1] < 0)
                        || (stack[stackSize - 2] > 0 && stack[stackSize - 1] > 0)) {
                        stack[stackSize - 2] = dividend / divisor;
                    }
                    else {
                        stack[stackSize - 2] = -1 * (dividend / divisor);
                    }

                    stack.pop_back();
                    stackSize--;
                    break;
                case 9:
                    if (stackSize <= 1) {
                        ifError = true;
                        break;
                    }

                    dividend = abs(stack[stackSize - 2]);
                    divisor = abs(stack[stackSize - 1]);
                    if (divisor == 0) {
                        ifError = true;
                        break;
                    }

                    if (stack[stackSize - 2] > 0) {
                        stack[stackSize - 2] = dividend % divisor;
                    }
                    else {
                        stack[stackSize - 2] = -1 * (dividend % divisor);
                    }

                    stack.pop_back();
                    stackSize--;
                    break;
                }
                if (ifError) break;
            }

            if(ifError || stack.size() != 1)
                cout << "ERROR" << endl;
            else
                cout << stack[0] << endl;
            
        }
        cout << endl;
    }
}