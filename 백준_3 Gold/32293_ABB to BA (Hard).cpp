#include <iostream>
#include <vector>
#include <string>

using namespace std;

void testCase(){
    int n;
    cin >> n;
    vector<char> s(n);
    for(int i = 0; i < n; i++)
        cin >> s[i];
    
    vector<char> res;
    int idx = 0;
    vector<char> buff;
    while(true){
        int resSize = res.size();
        if(resSize > 2 && res[resSize - 3] == 'A' && res[resSize - 2] == 'B' && res[resSize - 1] == 'B'){
            res.pop_back();
            res.pop_back();
            res.pop_back();
            res.push_back('B');
            buff.push_back('A');
        } else if(buff.size() > 0){
            res.push_back(buff.back());
            buff.pop_back();
        } else if(idx < n) {
            res.push_back(s[idx++]);
        } else {
            break;
        }
    }

    for(auto c: res) cout << c;
    cout << '\n';
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t;
    cin >> t;
    for(; t > 0; t--) testCase();

    return 0;
}