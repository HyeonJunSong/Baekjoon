#include<iostream>
#define N 10
#define SZ 205
using namespace std;
int n, m;
string dt[N];
int vst[N];
int ord[N];

int isAvail(string obj) {
	int pi[SZ] = { 0 };
	int j = 0;
	int len = obj.size();
	for (int i = 1; i != len; i++) {
		while (j != 0 && obj[i] != obj[j]) {
			j = pi[j - 1];
		}
		if (obj[i] == obj[j]) {
			j++;
		}
		pi[i] = j;
	}
	int chunkSz = len - pi[len - 1];
	if (len % chunkSz == 0) {
		return len / chunkSz == m;
	}
	else {
		return m == 1;
	}
	return 0;
}

int perm(int curr) {
	if (curr == n) {
		string obj;
		for (int i = 0; i != n; i++) {
			obj += dt[ord[i]];
		}
		return isAvail(obj);
	}
	int ret = 0;
	for (int i = 0; i != n; i++) {
		if (!vst[i]) {
			vst[i] = 1;
			ord[curr] = i;
			ret += perm(curr + 1);
			vst[i] = 0;
		}
	}
	return ret;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for (int i = 0; i != n; i++) {
		cin >> dt[i];
	}
	cin >> m;
	vst[0] = 1;
	cout << perm(1) * n;
}