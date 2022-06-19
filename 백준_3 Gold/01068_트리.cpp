#include <iostream>
#include <vector>

using namespace std;

int main(){

	int N;
	cin >> N;

	vector<vector<int>> tree(N, vector<int>());

	int root;
	for(int i = 0; i < N; i++){
		int inp;
		cin >> inp;

		if(inp == -1){
			root = i;
			continue;
		}
		tree[inp].push_back(i);
	}	

	int del;
	cin >> del;

	int cnt = 0;
	vector<int> stack(1, root);
	while(!(stack.empty())){
		int curNode = stack.back();
		stack.pop_back();

		if(curNode == del) continue;

		if(tree[curNode].empty() || (tree[curNode].size() == 1 && tree[curNode][0] == del)){
			cnt++;
			continue;
		}

		for(int j = 0; j < tree[curNode].size(); j++){
			stack.push_back(tree[curNode][j]);
		}
	}

	cout << cnt;

	return 0;

}