#include <iostream>
#include <vector>
#include <map>

using namespace std;

#define LL unsigned long long

LL ans = 0;
LL target = 0;

LL move(LL board, vector<int> command){

  if(command[0] == 1){
    //row
    for(int i = 0; i < 4 - command[2]; i++){
      LL temp = ((15LL << (((command[1] - 1) * 4 + 0) * 4)) & board) >> (((command[1] - 1) * 4 + 0) * 4);
      board &= ~(15LL << (((command[1] - 1) * 4 + 0) * 4));
      board |= ((board & (15LL << (((command[1] - 1) * 4 + 1) * 4))) >> (((command[1] - 1) * 4 + 1) * 4)) << (((command[1] - 1) * 4 + 0) * 4);
      board &= ~(15LL << (((command[1] - 1) * 4 + 1) * 4));
      board |= ((board & (15LL << (((command[1] - 1) * 4 + 2) * 4))) >> (((command[1] - 1) * 4 + 2) * 4)) << (((command[1] - 1) * 4 + 1) * 4);
      board &= ~(15LL << (((command[1] - 1) * 4 + 2) * 4));
      board |= ((board & (15LL << (((command[1] - 1) * 4 + 3) * 4))) >> (((command[1] - 1) * 4 + 3) * 4)) << (((command[1] - 1) * 4 + 2) * 4);
      board &= ~(15LL << (((command[1] - 1) * 4 + 3) * 4));
      board |= temp << (((command[1] - 1) * 4 + 3) * 4);
    }
  } else{
    //col
    for(int i = 0; i < 4 - command[2]; i++){
      LL temp = ((15LL << ((0 * 4 + (command[1] - 1)) * 4)) & board) >> ((0 * 4 + (command[1] - 1)) * 4);
      board &= ~(15LL << ((0 * 4 + (command[1] - 1)) * 4));
      board |= ((board & (15LL << ((1 * 4 + (command[1] - 1)) * 4))) >> ((1 * 4 + (command[1] - 1)) * 4)) << ((0 * 4 + (command[1] - 1)) * 4);
      board &= ~(15LL << ((1 * 4 + (command[1] - 1)) * 4));
      board |= ((board & (15LL << ((2 * 4 + (command[1] - 1)) * 4))) >> ((2 * 4 + (command[1] - 1)) * 4)) << ((1 * 4 + (command[1] - 1)) * 4);
      board &= ~(15LL << ((2 * 4 + (command[1] - 1)) * 4));
      board |= ((board & (15LL << ((3 * 4 + (command[1] - 1)) * 4))) >> ((3 * 4 + (command[1] - 1)) * 4)) << ((2 * 4 + (command[1] - 1)) * 4);
      board &= ~(15LL << ((3 * 4 + (command[1] - 1)) * 4));
      board |= temp << ((3 * 4 + (command[1] - 1)) * 4);
    }
  }

  return board;

}

int main(){

  for(LL i = 0; i < 4; i++){
    for(LL j = 0; j < 4; j++){
      LL val;
      cin >> val;
      val--;

      target |= (val << ((4 * i + j) * 4));
    }
  }

  for(LL i = 0; i < 4; i++)
    for(LL j = 0; j < 4; j++)
      ans |= ((4 * i + j) << ((4 * i + j) * 4));

  //ans로부터 역으로 가는 map 구축
  map<LL, vector<vector<int>>> ansMap;
  ansMap[ans] = {};

  map<LL, vector<vector<int>>> nextAnsMap;

  for(int t = 0; t < 3; t++){
    for(int i = 1; i < 3; i++){
      for(int j = 1; j < 5; j++){
        for(int k = 1; k < 4; k++){
          for(auto e: ansMap){
            LL curResult = move(e.first, {i, j, 4 - k});
            vector<vector<int>> commands = e.second;
            commands.push_back({i, j, k});

            nextAnsMap[curResult] = commands;

            if(curResult == target){
              cout << commands.size() << "\n";
              for(auto e = commands.rbegin(); e != commands.rend(); e++)
                cout << (*e)[0] << " " << (*e)[1] << " " << (*e)[2] << "\n";
              return 0;
            }
          }
        }
      }
    }
    ansMap = nextAnsMap;
    nextAnsMap.clear();
  }

  //target에서 ansMap
  map<LL, vector<vector<int>>> targetMap;
  targetMap[target] = {};

  map<LL, vector<vector<int>>> nextTargetMap;

  for(int t = 0; t < 4; t++){
    for(int i = 1; i < 3; i++){
      for(int j = 1; j < 5; j++){
        for(int k = 1; k < 4; k++){
          for(auto e: targetMap){
            LL curResult = move(e.first, {i, j, k});
            vector<vector<int>> commands = e.second;
            commands.push_back({i, j, k});

            nextTargetMap[curResult] = commands;
            
            if(ansMap.find(curResult) != ansMap.end()){
              vector<vector<int>> commandsToAns = ansMap[curResult];

              cout << commands.size() + commandsToAns.size() << "\n";
              for(auto e: commands)
                cout << e[0] << " " << e[1] << " " << e[2] << "\n";
              for(auto e = commandsToAns.rbegin(); e != commandsToAns.rend(); e++)
                cout << (*e)[0] << " " << (*e)[1] << " " << (*e)[2] << "\n";
              return 0;
            
            }
          }
        }
      }
    }
    targetMap = nextTargetMap;
    nextTargetMap.clear();
  }

  return 0;
}