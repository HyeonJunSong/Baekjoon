#include <iostream>
#include <vector>

using namespace std;

void runTestCase();
bool ifOverTheLine(pair<int, int> lineStart, pair<int, int> lineEnd, int xStart, int xEnd);

int main(){
    int T;
    cin >> T;
    for(int t = 0; t < T; t++)
        runTestCase();

}

void runTestCase(){

    vector<pair<int, int>> line(2);
    cin >> line[0].first >> line[0].second >> line[1].first >> line[1].second;
    if(line[0].first > line[1].first){
        pair<int, int> temp = line[0];
        line[0] = line[1];
        line[1] = temp;
    }

    vector<int> square(4);   //left, top, right, bottom
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    if(x1 < x2){
        square[0] = x1;
        square[2] = x2;
    }
    else{
        square[0] = x2;
        square[2] = x1;
    }

    if(y1 < y2){
        square[1] = y2;
        square[3] = y1;
    }
    else{
        square[1] = y1;
        square[3] = y2;
    }

    if(!ifOverTheLine(
        pair<int, int>(line[0].first, line[0].second - square[3]),
        pair<int, int>(line[1].first, line[1].second - square[3]),
        square[0],
        square[2]
    )){
        cout << "F\n";
        return;
    }

    if(!ifOverTheLine(
        pair<int, int>(line[0].first, square[1] - line[0].second),
        pair<int, int>(line[1].first, square[1] - line[1].second),
        square[0],
        square[2]
    )){
        cout << "F\n";
        return;
    }


    if(line[0].second > line[1].second){
        pair<int, int> temp = line[0];
        line[0] = line[1];
        line[1] = temp;
    }

    if(!ifOverTheLine(
        pair<int, int>(line[0].second, line[0].first - square[0]),
        pair<int, int>(line[1].second, line[1].first - square[0]),
        square[3],
        square[1]
    )){
        cout << "F\n";
        return;
    }

    if(!ifOverTheLine(
        pair<int, int>(line[0].second, square[2] - line[0].first),
        pair<int, int>(line[1].second, square[2] - line[1].first),
        square[3],
        square[1]
    )){
        cout << "F\n";
        return;
    }

    cout << "T\n";
    return;
}

bool ifOverTheLine(pair<int, int> lineStart, pair<int, int> lineEnd, int xStart, int xEnd){

    if(lineEnd.first == lineStart.first){
        return (xStart <= lineStart.first && lineStart.first <= xEnd) && (lineStart.second >= 0 || lineEnd.second >= 0);
    }
    else{
        double slope = (double)(lineEnd.second - lineStart.second) / (lineEnd.first - lineStart.first);
        double K = lineStart.second - slope * lineStart.first;

        int left = xStart > lineStart.first ? xStart : lineStart.first;
        int right = xEnd > lineEnd.first ? lineEnd.first : xEnd;

        if(left > right) return false;

        return (left * slope + K >= 0) || (right * slope + K >= 0);
    }
}