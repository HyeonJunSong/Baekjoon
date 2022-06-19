#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool comp(int* a, int* b);

int main(){
    int T;
    cin >> T;
    for(int t = 0; t < T; t++){

        int n;
        cin >> n;

        int** applicant = new int*[n];
        for(int i = 0; i < n; i++){
            applicant[i] = new int[2];
            cin >> applicant[i][0];
            cin >> applicant[i][1];
        }

        sort(applicant, applicant + n, comp);

        int maxMeetGrade = applicant[0][1];
        int cnt = 1;
        for(int i = 1; i < n; i++){
            if(applicant[i][1] < maxMeetGrade){
                cnt++;
                maxMeetGrade = applicant[i][1];
            }
        }
        cout << cnt << endl;
    }

    return 0;
}

bool comp(int* a, int* b){
    return a[0] < b[0];
}