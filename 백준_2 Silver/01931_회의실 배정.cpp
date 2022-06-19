#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

unsigned int N;
unsigned int** Meetings;

bool compare(unsigned int* a, unsigned int* b);
void MeetingsSort();

int main() {

	cin >> N;
	Meetings = new unsigned int* [N];
	for (int i = 0; i < N; i++) {
		Meetings[i] = new unsigned int[2];
		cin >> Meetings[i][0] >> Meetings[i][1];
	}

	vector<unsigned int*> stack;

	sort(Meetings, Meetings + N, compare);

	stack.push_back({Meetings[0]});
	for(int i = 1; i < N; i++){
		if(Meetings[i][0] < stack.back()[1])
			continue;
		stack.push_back(Meetings[i]);
	}


	cout << stack.size() << endl;
	for(int i = 0; i < (int)(stack.size()) - 1; i++)
		cout << stack[i][0] << ' ' << stack[i][1] << endl;
	cout << stack[(int)(stack.size()) - 1][0] << ' ' << stack[(int)(stack.size()) - 1][1];

    return 0;
}

bool compare(unsigned int* a, unsigned int* b){
	if(a[1] == b[1])
		return a[0] < b[0];
	return a[1] < b[1];
}