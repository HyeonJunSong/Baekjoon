#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

string qrData;
int ind;

vector<string> decodeQR();
vector<string> decodeBlock();
vector<string> decode_number();
vector<string> decode_alpha();
vector<string> decode_8bit();
vector<string> decode_kanji();
string hexaToDigit();
int digitStrToInt(string digitStr);

string alphaMap = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ $%*+-./:";

map<char, string> hexaDigitMap = {
    {'0', "0000"},
    {'1', "0001"},
    {'2', "0010"},
    {'3', "0011"},
    {'4', "0100"},
    {'5', "0101"},
    {'6', "0110"},
    {'7', "0111"},
    {'8', "1000"},
    {'9', "1001"},
    {'A', "1010"},
    {'B', "1011"},
    {'C', "1100"},
    {'D', "1101"},
    {'E', "1110"},
    {'F', "1111"}
};

vector<string> intHexaMap = {
    "0",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "A",
    "B",
    "C",
    "D",
    "E",
    "F"
};

int main() {

    int P;
    cin >> P;

    for (int i = 0; i < P; i++) {
        cin >> qrData;
        vector<string> result = decodeQR();
        cout << result.size() << ' ';
        for (auto iter = result.begin(); iter != result.end(); iter++) {
            cout << *iter;
        }
        cout << '\n';
    }

    return 0;
}

vector<string> decodeQR() {

    //16진수를 2진수로 변환
    qrData = hexaToDigit();

    ind = 0;
    //모드비트가 터미네이션 비트일때까지 디코딩

    vector<string> result;
    while (true) {
        vector<string> ret = decodeBlock();
        if (!ret.empty() && ret[0] == "Termination")
            break;
        result.insert(result.end(), ret.begin(), ret.end());
    }

    return result;
}

vector<string> decodeBlock() {
    if(qrData.size() - ind < 4)
        return vector<string>(1, "Termination");

    string modeBit = qrData.substr(ind, 4);
    ind += 4;

    if (modeBit == "0001")
        return decode_number();
    else if (modeBit == "0010")
        return decode_alpha();
    else if (modeBit == "0100")
        return decode_8bit();
    else if (modeBit == "1000")
        return decode_kanji();
    else if (modeBit == "0000")
        return vector<string>(1, "Termination");
}

vector<string> decode_number() {
    string countBit = qrData.substr(ind, 10);
    ind += 10;
    int cnt = digitStrToInt(countBit);

    vector<string> result;  

    for (int i = 0; i < cnt; i += 3) {
        string curStr;
        switch (cnt - i) {
        case 1:
            curStr = to_string(digitStrToInt(qrData.substr(ind, 4)));
            ind += 4;
            break;

        case 2:
            curStr = to_string(digitStrToInt(qrData.substr(ind, 7)));
            curStr = string(2 - curStr.length(), '0') + curStr;
            ind += 7;
            break;

        default:
            curStr = to_string(digitStrToInt(qrData.substr(ind, 10)));
            curStr = string(3 - curStr.length(), '0') + curStr;
            ind += 10;
            break;
        }
        for (auto iter = curStr.begin(); iter != curStr.end(); iter++)
            result.push_back(string(1, *iter));
    }

    return result;
}

vector<string> decode_alpha() {
    string countBit = qrData.substr(ind, 9);
    ind += 9;
    int cnt = digitStrToInt(countBit);

    vector<string> result;
    string curStr;
    int curAlphaInt;

    for (int i = 0; i < cnt; i += 2) {
        switch (cnt - i) {
        case 1:
            curAlphaInt = digitStrToInt(qrData.substr(ind, 6));
            ind += 6;
            result.push_back(string(1, alphaMap[curAlphaInt]));
            break;

        default:
            curAlphaInt = digitStrToInt(qrData.substr(ind, 11));
            ind += 11;
            result.push_back(string(1, alphaMap[curAlphaInt / 45]));
            result.push_back(string(1, alphaMap[curAlphaInt % 45]));
            break;
        }
    }

    return result;
}

vector<string> decode_8bit() {
    string countBit = qrData.substr(ind, 8);
    ind += 8;
    int cnt = digitStrToInt(countBit);

    vector<string> result;

    for (int i = 0; i < cnt; i += 1) {
        int cur8bitCode = digitStrToInt(qrData.substr(ind, 8));
        ind += 8;
        if (32 <= cur8bitCode && cur8bitCode <= 126) {
            if (cur8bitCode == 35)
                result.push_back("\\#");
            else
                result.push_back(string(1, char(cur8bitCode)));
        }
        else {
            result.push_back("\\" + intHexaMap[cur8bitCode / 16] + intHexaMap[cur8bitCode % 16]);
        }
    }

    return result;
}

vector<string> decode_kanji() {
    string countBit = qrData.substr(ind, 8);
    ind += 8;
    int cnt = digitStrToInt(countBit);

    vector<string> result;

    for (int i = 0; i < cnt; i += 1) {
        int curkanjiCode = digitStrToInt(qrData.substr(ind, 13));
        ind += 13;
        result.push_back("#" + to_string(curkanjiCode / 4096) + intHexaMap[(curkanjiCode % 4096) / 256] + intHexaMap[(curkanjiCode % 256) / 16] + intHexaMap[curkanjiCode % 16]);
    }

    return result;
}


string hexaToDigit() {
    string result = "";
    for (auto iter = qrData.begin(); iter != qrData.end(); iter++)
        result += hexaDigitMap[*iter];
    return result;
}

int digitStrToInt(string digitStr) {
    int result = 0;
    int curDigit = 1;
    for (auto iter = digitStr.rbegin(); iter != digitStr.rend(); iter++) {
        if (*iter == '1')
            result += curDigit;
        curDigit *= 2;
    }
    return result;
}