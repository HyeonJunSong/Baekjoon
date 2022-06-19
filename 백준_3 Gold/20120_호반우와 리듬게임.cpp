#include <iostream>

using namespace std;

typedef struct Node {
	int sc;
	int combo;
}node;


int main() {

	int N;
	cin >> N;
	int* notes = new int[N];

	for (int i = 0; i < N; i++) cin >> notes[i];

	node* score = new node[N];

	//첫번째 노드
	score[0].sc = notes[0];
	score[0].combo = 1;

	//두번째 노드
	if (N >= 2) {
		score[1].combo = score[0].combo + 1;
		score[1].sc = score[0].sc + score[1].combo * notes[1];
	}

	//세번째 노드
	if (N >= 3) {
		score[2].combo = score[1].combo + 1;
		score[2].sc = score[1].sc + score[2].combo * notes[2];

		int secScore = score[0].sc + notes[2];
		if (secScore > score[2].sc) {
			score[2].combo = 1;
			score[2].sc = secScore;
		}

	}

	//네번째 이상
	if (N >= 4) {
		int i = 3;

		while (i < N) {
			score[i].combo = score[i - 1].combo + 1;
			score[i].sc = score[i - 1].sc + score[i].combo * notes[i];

			int secScore = score[i - 2].sc + notes[i];
			if (secScore > score[i].sc) {
				score[i].combo = 1;
				score[i].sc = secScore;
			}

			int trdScore = score[i - 3].sc + notes[i];
			if (trdScore > score[i].sc) {
				score[i].combo = 1;
				score[i].sc = trdScore;
			}


			i++;
		}
	}

	if (score[N - 1].sc < 0) {
		cout << 0;
	}
	else {
		cout << score[N - 1].sc;
	}

	return 0;
}