////2022.02.03
//���� �� ���� : 33m 11s
//�Է� : 2m 11s
//���� :3�ð� ���٤���


//tot : 

#include <iostream>
#include <string>
#include <list>

using namespace std;
int mostFarPerson(int standard, string* friendship, int N);

typedef struct Node {
	bool ifPassed;
	int num;
	int max;
}node;

int main() {
	int N;
	cin >> N;
	
	int d;
	cin >> d;

	string* friendship = new string[N];
	for (int i = 0; i < N; i++) cin >> friendship[i];

	
	int totMax = 0;
	bool ifInf = false;
	for (int i = 0; i < N; i++) {
		int res = mostFarPerson(i, friendship, N);
		if (res == -1) {
			ifInf = true;
			break;
		}

		if (res > totMax) totMax = res;
	}

	if (ifInf) cout << -1;
	else cout << totMax * d;

	return 0;
}

int mostFarPerson(int standard, string* friendship, int N) {
	////ģ����� ��ȸ�ϸ� ��� ���� �� ���Ѿƴ��� Ȯ��

	node* person = new node[N];
	for (int i = 0; i < N; i++) {
		person[i].num = i;
		person[i].ifPassed = false;
	}

	person[standard].max = 0;
	person[standard].ifPassed = true;
	list<node*> queue;
	queue.push_back(&person[standard]);

	bool* ifFirst = new bool[N];
	for (int i = 0; i < N; i++) ifFirst[i] = true;

	while (!queue.empty()) {
		node* cur = queue.front();
		queue.pop_front();

		if (!ifFirst[cur->num]) continue;
		ifFirst[cur->num] = false;

		for (int i = 0; i < N; i++) {
			if (friendship[cur->num][i] == 'Y') {
				if (person[i].ifPassed) continue;

				person[i].max = cur->max + 1;
				person[i].ifPassed = true;
				queue.push_back(&person[i]);
			}
		}

	}


	//�������� Ȯ��
	bool ifInf = false;
	for (int i = 0; i < N; i++) {
		if (!person[i].ifPassed) {
			ifInf = true;
			break;
		}
	}

	////������ ������� �ִ� ���� �� ���� ���ϱ�

	if (!ifInf) {
		int totMax = 0;

		for (int i = 1; i < N; i++) {
			if (person[i].max > totMax) totMax = person[i].max;
		}

		return totMax;
	}
	else {
		return -1;
	}
}